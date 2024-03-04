#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <list>
using namespace std;

class Actor;
class Agent;
class Player;

// Note:  A convention used in a number of interfaces is to represent a
// direction with the adjustments to x and y needed to move one step in
// that direction:
// left:   dx is -1, dy is  0
// right:  dx is  1, dy is  0
// up:     dx is  0, dy is  1
// down:   dx is  0, dy is -1

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();

    virtual int init();
    virtual int move();
    virtual void cleanUp();

    // Can agent move to x,y?  (dx and dy indicate the direction of motion)
    bool canAgentMoveTo(Agent* agent, int x, int y, int dx, int dy);

    // Can a marble move to x,y?
    bool canMarbleMoveTo(int x, int y);

    // Is the player on the same square as an Actor?
    bool isPlayerColocatedWith(int x, int y);

    // Try to cause damage to something at a's location.  (a is only ever
    // going to be a pea.)  Return true if something stops a -- something
    // at this location prevents a pea from continuing.
    bool damageSomething(Actor* a, int damageAmt);

    // Swallow any swallowable object at a's location.  (a is only ever
    // going to be a pit.)
    bool swallowSwallowable(Actor* a);

        // If a pea were at x,y moving in direction dx,dy, could it hit the
        // player without encountering any obstructions?
    bool existsClearShotToPlayer(int x, int y, int dx, int dy); //for robot

    // If a factory is at x,y, how many items of the type that should be
    // counted are in the rectangle bounded by x-distance,y-distance and
    // x+distance,y+distance?  Set count to that number and return true,
    // unless an item is on the factory itself, in which case return false
    // and don't care about count.  (The items counted are only ever going
    // ThiefBots.)
    bool doFactoryCensus(int x, int y, int distance, int& count);

    // If an item that can be stolen is at x,y, return a pointer to it;
    // otherwise, return a null pointer.  (Stealable items are only ever
    // going be goodies.)
    Actor* getColocatedStealable(int x, int y);

    // Restore player's health to the full amount.
    void restorePlayerHealth();

    // Increase the amount of ammunition the player has
    void increaseAmmo();

    // Are there any crystals left on this level?
    bool anyCrystals() const;

    // Reduce the count of crystals on this level by 1.
    bool decCrystals();

    // Indicate that the player has finished the level.
    void setLevelFinished();

    // Add an actor to the world
    void addActor(Actor* a);

    Actor* getActor(int x, int y);
    
    //Player* getPlayer();

    void setFinished() {
        finished = true;
    }
private:
    list<Actor*> actors;
    Player* player;
    bool finished = false;

    int crystals;
    int bonus = 1000;
};

#endif // STUDENTWORLD_H_
