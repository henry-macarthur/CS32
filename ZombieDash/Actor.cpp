#include <iostream>
#include "Actor.h"
#include "StudentWorld.h"
using namespace std;


int verticalDirection(int y, int y2)
{
    int yD = y - y2;
    if(yD > 0)
        return 90;
    else
        return 270;
}
int horizontalDirection(int x, int x2)
{
    int xD = x - x2;
    if(xD > 0)
        return 0;
    else
        return 180;
}

Actor::Actor(int x, int y, int id, int depth, Direction d, StudentWorld* s)
:GraphObject(id, x, y, d, depth)
{
    world = s;
    alive = true;
    m_infected = false;
    m_infectionCount = 0;
    tickCount = 0;
}

bool Actor::isInfected() const
{
    
    return m_infected;
}
bool Actor::isAlive() const
{
    return alive;
}
bool Actor::tryMove(int startX, int startY, int destX, int destY, int d)
{
    if(worldPtr()->beingBlocked(this, destX, destY))
    {
        return false;
    }
    setDirection(d);
    moveTo(destX, destY);
    return true;
}

void Person::dealWithInfection()
{
    if(isInfected())
    {
        incrementInfection();
    }
}

void Citizen::onDead()
{
    worldPtr()->increaseScore(-1000);
}

Citizen::~Citizen()
{
    worldPtr()->changeNumCitizens(-1);
    //worldPtr()->decreaseNumCitizens();
}

void Citizen::doSomething()
{
    incTick();
    if(isAlive())
    {
        dealWithInfection();
        
        if(getInfectionCount() == 1)
        {
            worldPtr()->playSound(SOUND_CITIZEN_INFECTED);
        }
        if(getInfectionCount() >= 500)
        {
            setDead();
            worldPtr()->playSound(SOUND_ZOMBIE_BORN);
            int x = randInt(1, 10);
            switch (x) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    worldPtr()->insertActor(new DumbZombie(getX(), getY(), worldPtr()));
                    break;
                case 8:
                case 9:
                case 10:
                    worldPtr()->insertActor(new SmartZombie(getX(), getY(), worldPtr()));
                    break;
                default:
                    break;
            }

        }
        else
        {
            if(getTicks()%2 != 0)
            {
                double dist;
                int distToPenelope = worldPtr()->distanceToPlayer(this);
                Actor* closestZombie = worldPtr()->distanceToClosestZombie(getX(), getY(), dist);
                int pX, pY;
                worldPtr()->getPlayerCoordinates(pX, pY);
                int currentRow = getY();;
                int currentCol = getX();
                if((closestZombie == nullptr || distToPenelope < dist) && distToPenelope <= 80)
                {
                    
                    bool goAgain = true;
                    if(currentRow == pY)
                    {
                        int direction = (horizontalDirection(pX, getX()));
                        if(direction == right())
                        {
                            if(!tryMove(getX(), getY(), getX()+2, getY(), right()))
                                ;
                            else
                                goAgain = false;
                        }
                        else
                        {
                            if(!tryMove(getX(), getY(), getX()-2, getY(), left()))
                                ;
                            else
                                goAgain = false;
                        }
                    }
                    else if(currentCol == pX)
                    {
                        int direction  = (verticalDirection(pY, getY()));
                        if(direction == up())
                        {
                            if(!tryMove(getX(), getY(), getX(), getY()+2, up()))
                                ;
                            else
                                goAgain = false;
                        }
                        else
                        {
                            if(!tryMove(getX(), getY(), getX(), getY()-2, down()))
                                ;
                            else
                                goAgain = false;
                        }
                    }
                    else
                    {
                        int tryDirection;
                        int r = randInt(1,2);
                        switch (r) {
                            case 1:
                                tryDirection = horizontalDirection(pX, getX());
                                break;
                                
                            default:
                                tryDirection = verticalDirection(pY, getY());
                                break;
                        }
                        for(int i = 0; i <= 1; i++)
                        {
                            switch (tryDirection)
                            {
                                case 0:
                                    if(!tryMove(getX(), getY(), getX()+2, getY(), right()))
                                    {
                                        break;
                                    }
                                    return;
                                case 90:
                                    if(!tryMove(getX(), getY(), getX(), getY()+2, up()))
                                    {
                                        break;
                                    }
                                    return;
                                case 180:
                                    if(!tryMove(getX(), getY(), getX()-2, getY(), left()))
                                        break;
                                    return;
                                case 270:
                                    if(!tryMove(getX(), getY(), getX(), getY()-2, down()))
                                        break;
                                    return;
                            }
                            if(i ==0 &&(getDirection() == right() || getDirection() == left()))
                            {
                                tryDirection = verticalDirection(pY, getY());
                            }
                            else if(i == 0 && (getDirection() == up() || getDirection() == down()))
                            {
                                tryDirection = horizontalDirection(pX, getX());
                            }
                            
                        }
                        return;
                    }
                }
                else if(dist <= 80)
                {
                    int startD  = getDirection();
                    int furthest = 360;// = dist;
                    for(int i = 0; i < 4; i++)
                    {
                        double dist2;
                        Actor* closestZombie;
                        switch (i*90)
                        {
                            case 0:
                                if(!worldPtr()->beingBlocked(this, getX()+2, getY()))
                                {
                                    closestZombie = worldPtr()->distanceToClosestZombie(getX()+2, getY(), dist2);
                                    if(dist2 > dist)
                                    {
                                        dist = dist2;
                                        furthest = right();
                                    }
                                }
                                break;
                            case 90:
                                if(!worldPtr()->beingBlocked(this, getX(), getY()+2))
                                {
                                    closestZombie = worldPtr()->distanceToClosestZombie(getX(), getY()+2, dist2);
                                    if(dist2 > dist)
                                    {
                                        dist = dist2;
                                        furthest = up();
                                    }
                                }
                                break;
                            case 180:
                                if(!worldPtr()->beingBlocked(this, getX()-2, getY()))
                                {
                                    closestZombie = worldPtr()->distanceToClosestZombie(getX()-2, getY(), dist2);
                                    if(dist2 >= dist)
                                    {
                                        dist = dist2;
                                        furthest = left();
                                    }
                                }
                                break;
                            case 270:
                                if(!worldPtr()->beingBlocked(this, getX(), getY()-2))
                                {
                                    closestZombie = worldPtr()->distanceToClosestZombie(getX(), getY()-2, dist2);
                                    if(dist2 > dist)
                                    {
                                        dist = dist2;
                                        furthest = down();
                                    }
                                }
                                break;
                        }
                    }
                    if(furthest != startD && (furthest != 360))
                        setDirection(furthest);
                    switch (getDirection())
                    {
                        case 0:
                            if(!tryMove(getX(), getY(), getX()+2, getY(), right()))
                                break;
                            return;
                        case 90:
                            if(!tryMove(getX(), getY(), getX(), getY()+2, up()))
                                break;
                            return;
                        case 180:
                            if(!tryMove(getX(), getY(), getX()-2, getY(),left()))
                                break;
                            return;
                        case 270:
                            if(!tryMove(getX(), getY(), getX(), getY()-2, down()))
                                break;
                            return;
                    }
                }
            }
        }
    }
    else
    {
        return;
    }
}

Actor::~Actor()
{
    
}


Penelope::Penelope(int x, int y, StudentWorld* s)
:Person(x, y, IID_PLAYER, 0, s)
{
    numVaccines = 0;
    numLandMines = 0;
    numFlameCharges = 0;
}



void Penelope::doSomething()
{
    if(isAlive())
    {
        dealWithInfection();
        if(getInfectionCount() >= 500)
        {
            setDead();
            return;
        }
        int ch;
        if(worldPtr() -> getKey(ch))
        {
            switch(ch)
            {
                case KEY_PRESS_LEFT:
                    setDirection(left());
                    tryMove(getX(), getY(), getX()-4, getY(), left());
                    break;
                case KEY_PRESS_RIGHT:
                    setDirection(right());
                    tryMove(getX(), getY(), getX()+4, getY(), right());
                    break;
                case KEY_PRESS_DOWN:
                    setDirection(down());
                    tryMove(getX(), getY(), getX(), getY()-4, down());
                    break;
                case KEY_PRESS_UP:
                    setDirection(up());
                    tryMove(getX(), getY(), getX(), getY()+4, up());
                    break;
                case KEY_PRESS_SPACE:
                    
                    if(numCharges() > 0)
                    {
                        worldPtr()->playSound(SOUND_PLAYER_FIRE);
                        for(int i = 1; i < 4; i++)
                        {

                            switch(getDirection())
                            {
                                case 0:
                                    if(!(worldPtr()->shootFlame(getX()+ (i*SPRITE_WIDTH), getY(), getDirection())))
                                        i = 4;
                                    break;
                                case 180:
                                    if(!worldPtr()->shootFlame(getX()- (i*SPRITE_WIDTH), getY(), getDirection()))
                                        i = 4;
                                    break;
                                case 90:
                                    if(!worldPtr()->shootFlame(getX(), getY() + (i*SPRITE_HEIGHT), getDirection()))
                                        i = 4;
                                    break;
                                case 270:
                                    if(!worldPtr()->shootFlame(getX(), getY() - (i*SPRITE_HEIGHT), getDirection()))
                                        i = 4;
                                    break;
                            }
                        }
                        decreaseFlameCharges();
                    }
                    break;
                case KEY_PRESS_TAB:
                    if(numLandMines > 0)
                    {
                        worldPtr()->insertActor(new LandMine(getX(), getY(), worldPtr()));//addMines(getX(), getY());
                        numLandMines--;
                    }
                    break;
                case KEY_PRESS_ENTER:
                    if(numVaccines > 0)
                    {
                        setInfectionStatus(false);
                        numVaccines--;
                    }
                    break;
            }
        }
    }
    
}

Penelope::~Penelope()
{
}

Wall::Wall(int x, int y, StudentWorld* s)
:Actor(x,y,IID_WALL, 0, right(), s)
{
}

void Wall::doSomething()
{

}


Exit::Exit(int x, int y, StudentWorld* s)
:Actor(x,y,IID_EXIT, 1, right(), s)
{
}

void Exit::doSomething()
{
    int dist;
    Actor* p = worldPtr()->distanceToClosestPerson(this, dist, false);
    if(p != nullptr && dist <= 10)
    {
        worldPtr()->playSound(SOUND_CITIZEN_SAVED);
        worldPtr()->increaseScore(1500);
        p->setDead();
    }
    if(worldPtr()->collideWithPlayer(this) && worldPtr()->numCitizensAlive() == 0)
    {
        //worldPtr()->increaseScore(1000);
        worldPtr()->completeLevel();
        
    }
}

//void Goodie::generateSound()
//{
//    worldPtr()->playSound(SOUND_GOT_GOODIE);
//}

void Goodie::doSomething()
{
    if(isAlive() && worldPtr()->collideWithPlayer(this)) //&& canBeSteppedOn())
    {
        worldPtr()->playSound(SOUND_GOT_GOODIE);
        //generateSound();
        worldPtr()->increaseScore(50);
        effectPlayer();
        setDead();
    }
    return;
}

void GasCan::effectPlayer()
{
    worldPtr()->increaseFlameCharges();
}

void Vaccine::effectPlayer()
{
    worldPtr()->increaseVaccineCount();
}

void LandmineGoodie::effectPlayer()
{
        worldPtr()->increaseMines();
}

void LandMine::onDead()
{
    
    //Actor::setDead();
    worldPtr()->insertActor(new Pit(getX(), getY(), worldPtr()));
    worldPtr()->shootFlame(getX() + SPRITE_WIDTH, getY(), up());
    worldPtr()->shootFlame(getX() - SPRITE_WIDTH, getY(), up());
    worldPtr()->shootFlame(getX(), getY() + SPRITE_HEIGHT, up());
    worldPtr()->shootFlame(getX(), getY() - SPRITE_HEIGHT, up());
    worldPtr()->shootFlame(getX() + SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up());
    worldPtr()->shootFlame(getX() + SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up());
    worldPtr()->shootFlame(getX() - SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up());
    worldPtr()->shootFlame(getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up());
}
void LandMine::doSomething()
{
    
    if(isAlive() && canBeSteppedOn() && worldPtr()->collisionWithLandObject(this, false) )
    {
        worldPtr()->playSound(SOUND_LANDMINE_EXPLODE);
        //generateSound();
        setDead();
    }
    return;
}
//void LandMine::generateSound()
//{
//    worldPtr()->playSound(SOUND_LANDMINE_EXPLODE);
//    
//}
//bool s (Actor*p) {return true;}
void Flame::doSomething()
{
    if(isAlive() == true)
    {
        incTick();
        if(getTicks() < 2)
        {
            bool isBlocked = false;
            worldPtr()->collideWithFire(this, isBlocked);
            
            if(!isBlocked)
            switch(getDirection())
            {
                case 0:
                    moveTo(getX()+4, getY());
                    break;
                case 180:
                    moveTo(getX()-4, getY());
                    break;
                case 270:
                    moveTo(getX(), getY()-4);
                    break;
                case 90:
                    moveTo(getX(), getY()+4);
                    break;
            }
        }
        else
        {
            setDead();
        }
    }
    else
    {
        return;
    }
}

void Zombie::setRandomDirection()
{
    int d = randInt(1, 4);
    switch(d)
    {
        case 1:
            setDirection(right());
            break;
        case 2:
            setDirection(left());
            break;
        case 3:
            setDirection(up());
            break;
        case 4:
            setDirection(down());
            break;
    }
}

void Zombie::setMovementDistance()
{
    movementPlanDistance = randInt(3, 10);
}

void Zombie::moveZombieRandomly()
{
    switch(getDirection())
    {
        case 0:
            if(!tryMove(getX(), getY(), getX()+1, getY(), right()))
            {
                clearMovement();
            }
            else
            decreaseDistance();
            break;
        case 180:
            if(!tryMove(getX(), getY(), getX()-1, getY(), left()))
            {
                clearMovement();
            }
            else
            decreaseDistance();
            break;
        case 270:
            if(!tryMove(getX(), getY(), getX(), getY()-1, down()))
            {
                clearMovement();
            }
            else
            decreaseDistance();
            break;
        case 90:
            if(!tryMove(getX(), getY(), getX(), getY()+1, up()))
            {
                clearMovement();
            }
            else
            decreaseDistance();
            break;
    }
}

bool Zombie::produceVomit()
{
    Actor* v;
    int r = randInt(1, 3);

    switch (getDirection()) {
        case 0:
            v = new Vomit(getX() + SPRITE_WIDTH, getY(), getDirection(), worldPtr());
            break;
        case 180:
            v = new Vomit(getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT, getDirection(), worldPtr());
            break;
        case 270:
            v = new Vomit(getX(), getY() - SPRITE_HEIGHT, getDirection(), worldPtr());
            break;
        case 90:
            v = new Vomit(getX(), getY() + SPRITE_HEIGHT, getDirection(), worldPtr());
            break;
        default:
            break;
    }
    int distance;
    Actor* closestPerson = worldPtr()->distanceToClosestPerson(v, distance, true);
    if(shouldVomint(r) && distance <= 10) //or isColliding??
    {
        worldPtr()->playSound(SOUND_ZOMBIE_VOMIT);
        worldPtr()->insertActor(v);
        closestPerson->setInfectionStatus(true);
        //worldPtr()->infectPerson(closestPerson); //infectActor
        return true;
    }
    else
        delete v;
    
    return false;
}
Zombie::~Zombie()
{
}

void SmartZombie::onDead()
{
    worldPtr()->playSound(SOUND_ZOMBIE_DIE);
    worldPtr()->increaseScore(2000);
}

void DumbZombie::onDead()
{
    worldPtr()->playSound(SOUND_ZOMBIE_DIE);
    worldPtr()->increaseScore(1000);
    if(hasVaccineGoodie())
    {
    int direction = randInt(0,3);
    switch (direction * 90)
    {
        case 0:
            worldPtr()->insertActor(new Vaccine(getX()+SPRITE_WIDTH, getY(), worldPtr()), true);
            break;
        case 90:
            worldPtr()->insertActor(new Vaccine(getX(), getY()+SPRITE_WIDTH, worldPtr()), true);
            break;
        case 180:
            worldPtr()->insertActor(new Vaccine(getX()-SPRITE_WIDTH, getY(), worldPtr()), true);
            break;
        case 270:
            worldPtr()->insertActor(new Vaccine(getX(), getY()-SPRITE_WIDTH, worldPtr()), true);
            break;
    }
    }
}

DumbZombie::~DumbZombie()
{}
void DumbZombie::doSomething()
{

    if(isAlive())
    {
        incTick();
        
        if(getTicks()%2 != 0)
        {
            if(produceVomit())
                return;
            if(getDistance() <= 0)
            {
                setRandomDirection();
                setMovementDistance();
            }
            else
            {
                moveZombieRandomly();
            }
        }
        else
            return;
    }
    else
        return;
}

void SmartZombie::doSomething()
{
    if(isAlive())
    {
        incTick();
        if(getTicks()%2 != 0)
        {
            if(produceVomit())
                return;
            if(getDistance() <= 0)
            {
                setMovementDistance();
            
                //setMovementDistance();
                int distance;
                Actor* closestPerson = worldPtr()->distanceToClosestPerson(this, distance, true);
                if(distance <= 80)
                {
                    if((int(closestPerson->getX())) == int(getX()))
                    {
                        setDirection(verticalDirection(closestPerson->getY(), getY()));
                    }
                    else if(int(closestPerson->getY()) == int(getY()))
                    {
                        setDirection(horizontalDirection(closestPerson->getX(), getX()));
                    }
                    else
                    {
                        int r = randInt(1, 2);
                        switch (r) {
                            case 1:
                                setDirection(horizontalDirection(closestPerson->getX(), getX()));
                                break;
                            case 2:
                                setDirection(verticalDirection(closestPerson->getY(), getY()));
                                break;
                            default:
                                break;
                        }
                    }
                }
                else
                {
                    setRandomDirection();
                }
            }
            moveZombieRandomly();
        }
        
    }
}


void Vomit::doSomething()
{
    incTick();
    if(isAlive())
    {
       if(getTicks() > 2)
       {
           setDead();
       }
    }
    else
        return;
}

void Pit::doSomething()
{
    worldPtr()->collisionWithLandObject(this, true);
}

