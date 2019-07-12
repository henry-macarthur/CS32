#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
#include <cmath>
class StudentWorld;
using namespace std;
class Actor : public GraphObject
{
    //can maybe just do a isblockableObject
public:
    Actor(int x, int y, int id, int depth, Direction d, StudentWorld* s);
    virtual ~Actor();
    virtual void doSomething() = 0;
    virtual bool isBlockable() const {return false;}
    virtual bool isCollidableWithFire() const {return true;}
    virtual bool isCollidableWithVomit() const {return false;}
    virtual bool isCollidableWithGoodies() const {return false;}
    virtual bool willBlockFire() const {return false;}
    virtual bool willExplodeMines() const {return false;}
    bool tryMove(int startX, int startY, int destX, int destY, int d);
    StudentWorld* worldPtr() {return world;}
    bool isInfected() const;
    void setInfectionStatus(bool infection)
    {
        if(isInfected() && !infection)
        {
            m_infectionCount = 0;
            m_infected = false;
        }
        else if(infection)
        {
            m_infected = true;
        }
    }
    void incrementInfection()
    {
        m_infectionCount++;
    }
    int getInfectionCount() const
    {
        return m_infectionCount;
    }

    int right() const  {return 0;}
    int left() const {return 180;}
    int up()  const {return 90;};
    int down()  const {return 270;}
    bool isAlive() const;
    void incTick() {tickCount++;}
    int getTicks() const {return tickCount;}
    virtual void onDead() {};
    virtual void setDead() {alive = false; onDead();}
private:
    
    int tickCount;
    StudentWorld* world;
    bool alive;
    int m_infectionCount;
    bool m_infected;
};

class Person : public Actor
{
public:
    Person(int x, int y, int id, int depth, StudentWorld* s): Actor(x,y, id, depth, right(), s) {};
    virtual ~Person() {};
    void dealWithInfection();
    virtual bool isBlockable() const {return true;}
    bool isCollidableWithVomit() const {return true;}
};

class Penelope : public Person//: public Actor
{
public:
    Penelope(int x, int y, StudentWorld* s);
    ~Penelope();
    bool isCollidableWithGoodies() const {return true;}
    void doSomething();
    int numMines() const {return numLandMines;}
    int numCharges() const {return numFlameCharges;}
    void increaseMine() {numLandMines += 2;}
    void decreaseMines() { numLandMines--;}
    int getVaccineCount() const {return numVaccines;}
    void increaseVaccineCount() {numVaccines++;}
    void decreaseFlameCharges() {numFlameCharges--;}
    void increaseFlameCharges() {numFlameCharges+=5;}
    
private:
    int numVaccines;
    int numLandMines;
    int numFlameCharges;
};

class Citizen: public Person
{
public:
    Citizen(int x, int y, StudentWorld* s) : Person(x, y, IID_CITIZEN, 0, s){};
    void onDead();
    ~Citizen();
    void doSomething();
private:

};

class Wall : public Actor
{
public:
    Wall(int x, int y, StudentWorld* s);
    void doSomething();
    virtual bool isBlockable() const {return true;}
    virtual bool willBlockFire() const {return true;}
private:
};

class Exit : public Actor
{
public:
    Exit(int x, int y, StudentWorld* s);
    void doSomething();
    virtual bool isCollidableWithFire() const {return false;}
    virtual bool willBlockFire() const {return true;}
private:
};

class Goodie : public Actor
{
public:
    Goodie(int x, int y, int id, StudentWorld* s): Actor(x,y,id, 1, right(), s) {};
    void doSomething();
    //virtual bool canBeSteppedOn()  {return true;}
    virtual void effectPlayer() = 0;
    //virtual void generateSound();
private:
    StudentWorld* SWPtr;
};

class Vaccine : public Goodie
{
public:
    Vaccine(int x, int y, StudentWorld* s): Goodie(x,y, IID_VACCINE_GOODIE, s){};
    void effectPlayer();
    
private:
};

class GasCan : public Goodie //check the naming convention
{
public:
    GasCan(int x, int y, StudentWorld* s): Goodie(x,y, IID_GAS_CAN_GOODIE, s) {}
    void effectPlayer();
private:
    StudentWorld* SWPtr;
};

class LandmineGoodie : public Goodie
{
public:
    LandmineGoodie(int x, int y, StudentWorld* s): Goodie(x,y, IID_LANDMINE_GOODIE, s){}
    void effectPlayer();
private:
    StudentWorld* SWPtr;
};

class LandMine : public Actor
{
public:
    LandMine(int x, int y, StudentWorld* s): Actor(x,y,IID_LANDMINE, 1, right(), s){};

    //bool isCollidableWithPlayer() const {return false;}
    void onDead();
    void doSomething();
private:
    bool canBeSteppedOn()
    {
        incTick();
        return getTicks() >= 30;
        
    }
    //int ticksTillActive;
};


class Flame : public Actor
{
public:
    Flame(int x, int y, Direction d, StudentWorld* s): Actor(x, y, IID_FLAME, 0, d, s){}
    virtual bool willExplodeMines() const {return true;}
    bool isCollidableWithFire() const {return false;}
    void doSomething();
private:
};

class Zombie : public Actor
{
public:
    Zombie(int x, int y, StudentWorld* s) : Actor(x, y, IID_ZOMBIE, 0, right(),s), movementPlanDistance(0) {}
    virtual void doSomething() = 0;
    virtual ~Zombie();
    bool isBlockable() const {return true;}
    void setRandomDirection();
    void setMovementDistance();
    int getDistance() const {return movementPlanDistance;}
    void clearMovement() {movementPlanDistance = 0;}
    void decreaseDistance() {movementPlanDistance--;}
    void moveZombieRandomly();
    bool produceVomit();
private:
    bool shouldVomint(int i) {return i == 2;}
    int movementPlanDistance;
};

class DumbZombie : public Zombie
{
public: 
    DumbZombie(int x, int y, StudentWorld* s) : Zombie(x, y, s), goodie(randInt(1, 10)){}
    ~DumbZombie();
    void doSomething();
    void onDead();
private:
    bool hasVaccineGoodie() {return goodie == 5;}
    int goodie;

};

class SmartZombie : public Zombie
{
public:
    SmartZombie(int x, int y, StudentWorld* s) : Zombie(x, y, s){}
    void onDead();
    void doSomething();
private:
    
};

class Vomit : public Actor
{
public:
    Vomit(int x, int y, Direction d, StudentWorld* s): Actor(x, y, IID_VOMIT,0, d, s){}
    bool isCollidableWithFire() const { return false;}
    void doSomething();
private:
};

class Pit: public Actor
{
public:
    Pit(int x, int y, StudentWorld* s): Actor(x, y, IID_PIT, 0, right(), s){}
    bool isCollidableWithFire() const {return false;}
    void doSomething();
private:
};

#endif // ACTOR_H_
