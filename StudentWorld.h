#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	bool runOver(double x, double y);
	bool takesDamage(double x, double y);
	void damage(double x, double y, int damage);
	Avatar* getAvatar();

	Actor* getActor(int x, int y);

	void addActor(Actor* actor);

private:
	list<Actor*> actors;
	Avatar* _avatar;

	int crystals;
};

#endif // STUDENTWORLD_H_
