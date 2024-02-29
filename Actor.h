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
	bool isAlive();
	int getHealth();
	void updateHealth(int health);
	virtual void damage(int amt);

	virtual void doSomething() = 0;

	virtual bool canRunOver() { return false; } //can pea go over it
	virtual bool takeDamage() { return false; } //damageable by peas
	//virtual bool allowsAgentColocation() const = 0;
	//virtual bool allowsMarble() const = 0; //can marble share spot with this
	//virtual bool stopsPea() const = 0; //stops pea

	//virtual bool bePushedBy(Agent* a, int x, int y);


	StudentWorld* getStudentWorld();

private:
	StudentWorld* _world;
	int _health;
};
/*
class Agent : public Actor
{
public:
	Agent(StudentWorld* world, int startX, int startY, int imageID, int hitPoints, int startDir);

	// Move to the adjacent square in the direction the agent is facing
	// if it is not blocked, and return true.  Return false if the agent
	// can't move.
	bool moveIfPossible();

	// Return true if this agent can push marbles (which means it's the
	// player).
	//virtual bool canPushMarbles() const;

	// Return true if this agent doesn't shoot unless there's an unobstructed
	// path to the player.
	//virtual bool needsClearShot() const;

	// Return the sound effect ID for a shot from this agent.
	//virtual int shootingSound() const;


};
*/

//AVATAR
class Avatar : public Actor {
public:
	Avatar(StudentWorld* world, double startX, double startY);
	void doSomething();

	virtual bool takeDamage() { return true; }
	virtual bool canRunOver() { return false; }
	virtual bool canPushMarbles() const { return true; }
	virtual bool stopsPea() const { return true; } //stops it or damages it??
private:
	int peaCount;
};

class Wall : public Actor {
public:
	Wall(StudentWorld* world, double startX, double startY);
	void doSomething();
	virtual bool canRunOver() const { return false; }
	virtual bool stopsPea() const { return true; }
};

class Pea : public Actor {
public:
	Pea(StudentWorld* world, double startX, double startY, int direction);
	void doSomething();
	virtual bool canRunOver() { return true; }
	virtual bool takeDamage() { return false; }
};

class Exit : public Actor {
public:
	Exit(StudentWorld* world, double startX, double startY);
	void doSomething() { return; }
	virtual bool canRunOver() { return true; }
	virtual bool takeDamage() { return false; }
};

class Marble : public Actor {
public:
	Marble(StudentWorld* world, double startX, double startY);
	void doSomething() { return; }
	virtual bool canRunOver() { return false; }
	virtual bool takeDamage() { return true; }
	virtual bool bePushedBy(Avatar* a, int x, int y);
	void bePushed();
};

class Pit : public Actor {
public:
	Pit(StudentWorld* world, double startX, double startY);
	void doSomething() { return; }
	virtual bool canRunOver() { return false; }
	virtual bool takeDamage() { return false; }
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
