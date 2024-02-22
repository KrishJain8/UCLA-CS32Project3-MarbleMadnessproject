#include "Actor.h"
#include "StudentWorld.h"


//Actor
bool Actor::isAlive() {
	return _health > 0;
}

int Actor::getHealth() {
	return _health;
}
void Actor::updateHealth(int health) {
	_health = health;
}
StudentWorld* Actor::getStudentWorld() {
	return _world;
}

//Avatar

Avatar::Avatar(StudentWorld* world) : Actor(IID_PLAYER, 0, 0, 0, 0, world) 
{
	setVisible(true);
	updateHealth(20);
	peaCount = 20;
}
void Avatar::firePea() {
	//create pea at location in front of where avatar is facing
	if (true) { //direction  == right

	}
	return;
}

void Avatar::doSomething() {
	double x = getX();
	double y = getY();
	if (!isAlive()) {
		return;
	}
	int input;
	if (getStudentWorld()->getKey(input)) {
		switch (input) {
		case KEY_PRESS_ESCAPE:
			updateHealth(0); //kill avatar
			break;
		case KEY_PRESS_UP:
			moveTo(x, y + 1); //check for wall first
			setDirection(90);
			break;
		case KEY_PRESS_DOWN:
			moveTo(x, y - 1);
			setDirection(270);
			break;
		case KEY_PRESS_LEFT:
			moveTo(x - 1, y);
			setDirection(180);
			break;
		case KEY_PRESS_RIGHT:
			moveTo(x + 1, y);
			setDirection(0);
			break;
		case KEY_PRESS_SPACE:
			//introduce pea object
			firePea();
			peaCount--;
			break;
		}
		
	}
}


//Wall

Wall::Wall(StudentWorld* world, double startX, double startY) : Actor(IID_WALL, startX, startY, none, 1, world) {
	setVisible(true);
}
void Wall::doSomething() {
	return;
}

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
