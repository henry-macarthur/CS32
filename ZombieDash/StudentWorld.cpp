#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::~StudentWorld()
{

    cleanUp();
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{

}



int StudentWorld::init()
{
    Level lev(assetPath());
    numCitizens = 0;
    advanceLevel = false;
    player = nullptr;
    if(getLevel() > 99)
        return GWSTATUS_PLAYER_WON;
    
    string levelFile = "level";
    int lvl = getLevel();
    if(lvl < 10)
        levelFile += '0';
    levelFile += to_string(lvl);
   // string levelFile = "level0";//01.txt";
    levelFile += ".txt";

    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_PLAYER_WON;
        //cerr << "Cannot find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
           // cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
                cerr << "Successfully loaded level" << endl;
        for(int i = 0; i < 16; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                Level::MazeEntry ge = lev.getContentsOf(i,j); // level_x=5, level_y=10 switch (ge) // so x=80 and y=160
                switch (ge)
                {
                    case Level::empty:

                        break;
                    case Level::smart_zombie:
                        actors.push_back(new SmartZombie(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        break;
                    case Level::dumb_zombie:
                        actors.push_back(new DumbZombie(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        //cout << "Location 80,160 starts with a dumb zombie" << endl;
                        break;
                    case Level::player:
                        player = new Penelope(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                        break;
                    case Level::exit:
                        actors.push_back(new Exit(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        break;
                    case Level::wall:
                        actors.push_back(new Wall(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        break;
                    case Level::pit:
                        actors.push_back(new Pit(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        //cout << "Location 80,160 has a pit in the ground" << endl;
                        break;
                    case Level::citizen:
                        actors.push_back(new Citizen(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        changeNumCitizens(1);
                        //increaseNumCitizens();
                        break;
                    case Level::vaccine_goodie:
                        actors.push_back(new Vaccine(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        break;
                    case Level::gas_can_goodie:
                        actors.push_back(new GasCan(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        //cout << "Location 80,160 holds a Wall" << endl;
                        break;
                    case Level::landmine_goodie:
                        actors.push_back(new LandmineGoodie(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        //cout << "Location 80,160 has a pit in the ground" << endl;
                        break;
                    default:
                        break;
                }
            }
        }
        //actors.push_back(new Flame(10, 10,0, this));
        return GWSTATUS_CONTINUE_GAME;
    }
    return GWSTATUS_PLAYER_WON;

}

void StudentWorld::insertActor(Actor *p, bool lookForOverlap)
{
    //cout << lookForOverlap << endl;
    if(lookForOverlap)
    {
        for(int i = 0; i < actors.size(); i++)
            {
                if(p != actors[i] && objectOverlap(actors[i], p))
                {
                    delete p;
                    return;
                }
            }
    }
    actors.push_back(p);
}
bool StudentWorld::collideWithFire(Actor* fire, bool& isBeingBlocked)
{
    if(objectOverlap(fire, player))
    {
        this->playSound(SOUND_PLAYER_DIE);
        player->setDead();
        return true;
    }
    for(int i = 0; i < actors.size(); i++)
    {
        if(fire != actors[i] && actors[i]->willBlockFire())
        {
            isBeingBlocked = true;
        }
        
        if(fire != actors[i] && actors[i]->isAlive() && actors[i]->isCollidableWithFire() && objectOverlap(actors[i], fire))
        {
            if(actors[i]->isCollidableWithVomit())
                this->playSound(SOUND_CITIZEN_DIE);
            actors[i]->setDead();

        }
    }
    return true;
}
//void StudentWorld::addMines(int x, int y)
//{
//    LandMine* l = new LandMine(x, y, this);
//
//    actors.push_back(l);
//
//}
bool StudentWorld::shootFlame(int x, int y, Direction d)
{
    Flame* f = new Flame(x, y, d, this);
    for(int i = 0; i < actors.size(); i++)
    {
        if((actors[i]->willBlockFire() && objectOverlap(f, actors[i]))) //|| (f->getX() < 0 || f->getX() > VIEW_WIDTH || f->getY() < 0 || f->getX() > VIEW_HEIGHT))
        {
            delete f;
            return false;
        }
    }
    actors.push_back(f);
    return true;
}
int StudentWorld::distanceToPlayer(Actor *p) const
{
    return distance(player->getX(), player->getY(), p->getX(), p->getY());
}

bool isZombie(Actor* p)
{
    return (p->isAlive() && !p->isCollidableWithVomit() && p->isBlockable() && !p->willBlockFire());
}
double StudentWorld::distance(int x1, int y1, int x2, int y2) const
{
    return(sqrt(pow(((x1) - (x2)), 2) + pow(((y1) - (y2)), 2)));
}


Actor* StudentWorld::distanceToClosestZombie(int x, int y, double& dist) const
{
    double closestDistance = 1000;
    
    Actor* closestPerson = nullptr;
    for(int i = 0; i < actors.size(); i++)
    {
        if(isZombie(actors[i]))
        {
            double d = distance(x, y, actors[i]->getX(), actors[i]->getY());
            if(d < closestDistance)
            {
                closestDistance = d;
                closestPerson = actors[i];
            }
        }
    }
    dist = closestDistance;
    return closestPerson;
}
Actor* StudentWorld::distanceToClosestPerson(Actor *p, int& dist, const bool considerPlayer) const
{
    double closestDistance = 500;
    Actor* closestPerson = nullptr;
    
    if(considerPlayer && player->isAlive())
    {
        closestDistance = distanceToPlayer(p);
        closestPerson = player;
    }
    for(int i = 0; i < actors.size(); i++)
    {
        if(actors[i]->isAlive() && actors[i]->isCollidableWithVomit())
        {
            int d = distance(p->getX(), p->getY(), actors[i]->getX(), actors[i]->getY());
            if(d < closestDistance)
            {
                closestDistance = d;
                closestPerson = actors[i];
            }
        }
    }
    
    dist = closestDistance;
    return closestPerson;
}
bool StudentWorld::objectOverlap(Actor *p, Actor *p2) const
{
    if(distance(p->getX(), p->getY(), p2->getX(), p2->getY()) <= 10)
        return true;
    return false;
}

bool StudentWorld::beingBlocked(Actor *p, int x, int y) const //zombieObjectCollision
{
    if(p != player && isBlockingMovement(x, y, player))
        return true;
    for(int i = 0; i < actors.size();i++)
    {
        //cout << actors[i]->isCollidableWithPlayer() << endl;
        if(actors[i] != p && actors[i]->isAlive() && isBlockingMovement(x, y, actors[i]) && actors[i]->isBlockable())
        {
            return true;
        }
    }
    return false;
}


bool StudentWorld::isBlockingMovement(int x, int y, Actor* p2) const //fix this!!!
{
    //cout << ".." << endl;
    if(abs((x - (p2->getX()))) < SPRITE_WIDTH &&
       abs(y - (p2->getY())) < SPRITE_HEIGHT &&
       abs(y+SPRITE_HEIGHT - (p2->getY()+SPRITE_HEIGHT)) < SPRITE_HEIGHT &&
       abs(x+SPRITE_WIDTH - (p2->getX()+SPRITE_WIDTH)) < SPRITE_WIDTH)
    {
        return true;
    }
    return false;
    
}


bool StudentWorld::collideWithPlayer(Actor *p) const
{
    return (objectOverlap(player, p));
}

int StudentWorld::move()
{
    ostringstream oss;
    if(getScore() >= 0)
    {
        oss << "Score: " ;//ß<< endl;
        oss.fill('0');
        oss << setw(6) << abs(getScore()) ;//<< endl;
        oss.fill(' ');
    }
    else
    {
        oss <<  "Score: -";
        oss.fill('0');
        oss << setw(5) << abs(getScore()) ;//<< endl;
        oss.fill(' ');
    }
//    oss << setw(6) << abs(getScore()) ;//<< endl;
//    oss.fill(' ');
    oss << setw(9) << "Level: ";// <<endl;
    oss << getLevel() ;//<< endl;
    oss.fill(' ');
    
    oss << setw(9) << "Lives: ";
    oss.fill(' ');
    oss << setw(1) << getLives();
    //oss.fill(' ');
    
    oss << setw(12) << "Vaccines: ";// << endl;
    oss << player->getVaccineCount();// << endl;
    oss.fill(' ');
    oss << setw(10) << "Flames: ";// << endl;
    oss << player->numCharges();//<< endl;
    oss.fill(' ');
    oss << setw(9) << "Mines: ";//<< endl;
    oss << player->numMines();// << endl;
    oss.fill(' ');
    oss << setw(12) << "Infected: "; //<< endl;
    oss << player->getInfectionCount();// << endl;
    string s = oss.str();
    setGameStatText(s);
    
    player->doSomething();
    for(int i = 0; i < actors.size(); i++)
    {
        actors[i]->doSomething();
    }
    
    if(!player->isAlive())
    {
        decLives();
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
    
    for(vector<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
    {
        if(!(*p)->isAlive())
        {
            vector<Actor*>::iterator temp = p;
            delete *temp;
            *temp = nullptr;
            p = actors.erase(p);
            p--;

        }
    }
    if(advanceLevel)
    {
        playSound(SOUND_LEVEL_FINISHED);
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;//GWSTATUS_PLAYER_DIED;
}

bool StudentWorld::collisionBetweenLand(Actor *p, Actor* p2) const
{
    
    if(p != p2 && p2->isCollidableWithFire() && objectOverlap(p, p2))
    {
        return  true;
    }
    
    return false;
}

bool StudentWorld::collisionWithLandObject(Actor *p, bool willKill)
{
    bool collide = false;
    if(objectOverlap(p, player))
    {
       player->setDead();
        collide = true;
        playSound(SOUND_PLAYER_DIE);
    }
       
    for(int i = 0; i < actors.size(); i++)
    {
        if(actors[i]->isAlive() && collisionBetweenLand(p, actors[i]))
        {
            if(willKill)
            {
                playSound(SOUND_CITIZEN_DIE);
                actors[i]->setDead();
            }
            collide = true;
        }
    }
    
    return collide;
}

void StudentWorld::cleanUp()
{
    delete player;
    player = nullptr;
    for(int i = 0; i < actors.size();i++)
    {
        delete actors[i];
    }
    actors.clear();
}
