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

Avatar::Avatar(StudentWorld* world, double startX, double startY) : Actor(IID_PLAYER, startX, startY, 0, 0, world)
{
	setVisible(true);
	updateHealth(20);
	peaCount = 20;
}
void Avatar::firePea() {
	double x = getX();
	double y = getY();
	//create pea at location in front of where avatar is facing
	if (getDirection() == 90) { //direction  == right
		return; //create pea at x + 1, y
	}
	if (getDirection() == 180) { //direction  == left
		return; //create pea at x - 1, y
	}
	if (getDirection() == 0) { //direction  == up
		return; //create pea at x, y + 1
	}
	if (getDirection() == 270) { //direction  == down
		return; //create pea at x, y - 1
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
			if (getStudentWorld()->runOver(x, y + 1)) {
				moveTo(x, y + 1);
				setDirection(90);
			}
			break;
		case KEY_PRESS_DOWN:
			if (getStudentWorld()->runOver(x, y - 1)) {
				moveTo(x, y - 1);
				setDirection(270);
			}
			break;
		case KEY_PRESS_LEFT:
			if (getStudentWorld()->runOver(x - 1, y)) {
				moveTo(x - 1, y);
				setDirection(180);
			}
			break;
		case KEY_PRESS_RIGHT:
			if (getStudentWorld()->runOver(x + 1, y)) {
				moveTo(x + 1, y);
				setDirection(0);
			}
			break;
		case KEY_PRESS_SPACE:
			//introduce pea object
			firePea();
			peaCount--;
			break;
		}

	}
}
bool Avatar::canRunOver() {
	return true;
}

//Wall

Wall::Wall(StudentWorld* world, double startX, double startY) : Actor(IID_WALL, startX, startY, none, 1, world) {
	setVisible(true);
	updateHealth(1);
}
void Wall::doSomething() {
	return;
}
bool Wall::canRunOver() {
	return false;
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
