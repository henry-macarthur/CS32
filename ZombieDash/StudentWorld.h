#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

using namespace std;
class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    int distanceToPlayer(Actor *p) const;
    Actor* distanceToClosestZombie(int x, int y, double& distance) const;
    Actor* distanceToClosestPerson(Actor *p, int& distance, const bool considerPlayer) const;
    bool objectOverlap(Actor *p, Actor *p2) const;
    bool collisionWithLandObject(Actor *p, bool willKill);
    bool beingBlocked(Actor *p, int x, int y) const;
    void insertActor(Actor *p, bool lookForOverlap = false);
    //void infectPerson(Actor *p) {p->setInfectionStatus(true);}
    void increaseMines () {player->increaseMine();}
    //void addMines(int x, int y);
    bool collideWithPlayer(Actor *p) const;
    void getPlayerCoordinates(int& x, int& y) const { x = player->getX(); y = player->getY();}
    bool collideWithFire(Actor* fire, bool& isBeingBlocked);
    void completeLevel()  {advanceLevel = true;}
    void increaseVaccineCount() {player->increaseVaccineCount();}
    void increaseFlameCharges() {player->increaseFlameCharges();}
    bool shootFlame(int x, int y, Direction d);
    void changeNumCitizens(int increment){ numCitizens += increment;}
    int numCitizensAlive() const { return numCitizens;}
//    void decreaseNumCitizens() {numCitizens--;}
//    void increaseNumCitizens() {numCitizens++;}

private:
    bool collisionBetweenLand(Actor *p, Actor * p2) const;
    double distance(int x1, int y1, int x2, int y2) const;
    bool isBlockingMovement(int x, int y, Actor* p2) const;
    int numCitizens;
    bool advanceLevel;
    Penelope* player;
    vector<Actor*> actors;
};

#endif // STUDENTWORLD_H_
