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

void Actor::damage(int amt) {
	updateHealth(getHealth() - amt);
}

StudentWorld* Actor::getStudentWorld() {
	return _world;
}
//Agent
/*
bool Agent::moveIfPossible() {
	int x = getX();
	int y = getY();
	if (getDirection() == 90 && getStudentWorld()->runOver(x, y + 1)) {
		return true;
	}
	if (getDirection() == 180 && getStudentWorld()->runOver(x - 1, y)) {
		return true;
	}
	if (getDirection() == 0 && getStudentWorld()->runOver(x + 1, y)) {
		return true;
	}
	if (getDirection() == 270 && getStudentWorld()->runOver(x, y - 1)) {
		return true;
	}
	return false;
}
*/
//Avatar

Avatar::Avatar(StudentWorld* world, double startX, double startY) : Actor(IID_PLAYER, startX, startY, 0, 0, world)
{
	setVisible(true);
	updateHealth(20);
	peaCount = 20;
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
			if (peaCount > 0) {
				if (getDirection() == 90) {
					getStudentWorld()->addActor(new Pea(getStudentWorld(), x, y + 1, getDirection()));
				}
				if (getDirection() == 180) {
					getStudentWorld()->addActor(new Pea(getStudentWorld(), x - 1, y, getDirection()));
				}
				if (getDirection() == 0) {
					getStudentWorld()->addActor(new Pea(getStudentWorld(), x + 1, y, getDirection()));
				}
				if (getDirection() == 270) {
					getStudentWorld()->addActor(new Pea(getStudentWorld(), x, y - 1, getDirection()));
				}
				peaCount--;
				break;
			}
			break;
		}
	}
}



//Wall

Wall::Wall(StudentWorld* world, double startX, double startY) : Actor(IID_WALL, startX, startY, none, 1, world) {
	setVisible(true);
	updateHealth(1);
}
void Wall::doSomething() {
	return;
}

//Pea
Pea::Pea(StudentWorld* world, double startX, double startY, int dir) : Actor(IID_PEA, startX, startY, dir, 1, world) {
	setVisible(true);
	updateHealth(1);
}

void Pea::doSomething() {
	if (!isAlive()) {
		return;
	}
	double x = getX();
	double y = getY();

	double newX = x;
	double newY = y;

	if (!getStudentWorld()->runOver(x, y)) {
		cout << "d" << endl;
		getStudentWorld()->damage(x, y, 2);
		updateHealth(0);
	}
	else {
		if (getDirection() == 90) {
			newY += 1;
		}
		else if (getDirection() == 180) {
			newX -= 1;
		}
		else if (getDirection() == 0) {
			newX += 1;
		}
		else if (getDirection() == 270) {
			newY -= 1;
		}
		if (getStudentWorld()->runOver(newX, newY)) {
			moveTo(newX, newY);
		}
		else {
			updateHealth(0);
		}
	}
}

Exit::Exit(StudentWorld* world, double startX, double startY) : Actor(IID_EXIT, startX, startY, none, 1, world) {
	setVisible(true);
}

Marble::Marble(StudentWorld* world, double startX, double startY) : Actor(IID_MARBLE, startX, startY, none, 1, world) {
	setVisible(true);
	updateHealth(10);
}

bool Marble::bePushedBy(Avatar* a, int x, int y) {
	if ((a->getX() == x - 1 && a->getY() == y && a->getDirection() == 180)
		|| (a->getX() == x + 1 && a->getY() == y && a->getDirection() == 0)
		|| (a->getX() == x && a->getY() == y + 1 && a->getDirection() == 90)
		|| (a->getX() == x && a->getY() == y - 1 && a->getDirection() == 270)) {
		return true;
	}
	
	return false;
}

void Marble::bePushed() {
	Avatar* a = getStudentWorld()->getAvatar();
	if (bePushedBy(a, getX(), getY())) {
		double x = a->getX();
		double y = a->getY();

		double newX = getX();
		double newY = getY();
		if (getDirection() == 90) {
			newY += 1;
			y++;
		}
		else if (getDirection() == 180) {
			newX -= 1;
			x--;
		}
		else if (getDirection() == 0) {
			newX += 1;
			x++;
		}
		else if (getDirection() == 270) {
			newY -= 1;
			y--;
		}
		if (getStudentWorld()->runOver(newX, newY)) {
			moveTo(newX, newY);
			a->moveTo(x, y);
		}
	}
}

Pit::Pit(StudentWorld* world, double startX, double startY) : Actor(IID_PIT, startX, startY, none, 1, world) {
	setVisible(true);
}

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
