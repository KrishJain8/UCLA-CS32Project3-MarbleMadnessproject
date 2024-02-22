#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(int imageID, double startX, double startY, int dir, double size, StudentWorld* world)
		: GraphObject(imageID, startX, startY, dir, size) {
			_world = world;
	}
	virtual void doSomething() = 0;
	bool isAlive();
	int getHealth();
	void updateHealth(int health);
	StudentWorld* getStudentWorld();

private:
	StudentWorld* _world;
	int _health;
};
class Avatar : public Actor {
public:
	Avatar(StudentWorld* world);
	void doSomething();
	void firePea();
private:
	int peaCount;
	int score;
};

class Wall : public Actor {
public:
	Wall(StudentWorld* world, double startX, double startY);
	void doSomething();
private:

};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
