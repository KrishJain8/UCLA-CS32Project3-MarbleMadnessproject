#include "Actor.h"
#include "StudentWorld.h"
#include "GraphObject.h"
#include <cstdlib>


//Actor
Actor::Actor(StudentWorld* world, int startX, int startY, int imageID, int hitPoints, int startDir) 
	: GraphObject(imageID, startX, startY, startDir, 1) {
	_world = world;
}
bool Actor::isAlive() const {
	return _health > 0;
}

void Actor::setDead() {
	_health = 0;
}

int Actor::getHitPoints() const {
	return _health;
}

void Actor::decHitPoints(int amt) {
	_health = _health - amt;
}
void Actor::setHitPoints(int amt) {
	_health = amt;
}

void Actor::damage(int damageAmt) {
	if (isDamageable()) {
		setHitPoints(getHitPoints() - damageAmt);
	}
}

StudentWorld* Actor::getWorld() const {
	return _world;
}

//AGENT

Agent::Agent(StudentWorld* world, int startX, int startY, int imageID, int hitPoints, int startDir) 
: Actor(world, startX, startY, imageID, hitPoints, startDir) {
	setVisible(true);
}
bool Agent::moveIfPossible() {
	int x = getX();
	int y = getY();
	if (getDirection() == 90 && getWorld()->canAgentMoveTo(this, x, y, 0, 1)) {
		moveTo(x, y + 1);
		return true;
	}
	if (getDirection() == 180 && getWorld()->canAgentMoveTo(this, x, y, -1, 0)) {
		moveTo(x - 1, y);
		return true;
	}
	if (getDirection() == 0 && getWorld()->canAgentMoveTo(this, x, y, 1, 0)) {
		moveTo(x + 1, y);
		return true;
	}
	if (getDirection() == 270 && getWorld()->canAgentMoveTo(this, x, y, 0, -1)) {
		moveTo(x, y - 1);
		return true;
	}
	return false;
}

//Avatar

Player::Player(StudentWorld* world, int startX, int startY) : Agent(world, startX, startY, IID_PLAYER, 20, 0)
{
	setVisible(true);
	setHitPoints(20);
	ammo = 20;
}


void Player::doSomething() {
	int x = getX();
	int y = getY();
	if (!isAlive()) {
		return;
	}
	int input;
	if (getWorld()->getKey(input)) {
		switch (input) {
		case KEY_PRESS_ESCAPE:
			setHitPoints(0); //kill avatar
			break; 
		case KEY_PRESS_UP:
			setDirection(90);
			if (moveIfPossible()) {
				moveTo(x, y + 1);
				break;
			}
			if (getWorld()->getActor(x, y + 1) != nullptr) {
				if (getWorld()->getActor(x, y + 1)->bePushedBy(this, x, y + 1) && getWorld()->getActor(x, y + 1)->isSwallowable()) {
					getWorld()->getActor(x, y + 1)->moveTo(x, y + 2);
					moveTo(x, y + 1);
				}
			}
			break;
		case KEY_PRESS_DOWN:
			setDirection(270);
			if (moveIfPossible()) {
				moveTo(x, y - 1);
				break;
			}
			if (getWorld()->getActor(x, y - 1)->isSwallowable()) {
				if (getWorld()->getActor(x, y - 1)->bePushedBy(this, x, y - 1)) {
					getWorld()->getActor(x, y - 1)->moveTo(x, y - 2);
					moveTo(x, y - 1);
				}
			}
			break;
		case KEY_PRESS_LEFT:
			setDirection(180);
			if (moveIfPossible()) {
				moveTo(x - 1, y);
				break;
			}
			if (getWorld()->getActor(x - 1, y)->isSwallowable()) {
				if (getWorld()->getActor(x - 1, y)->bePushedBy(this, x - 1, y)) {
					getWorld()->getActor(x - 1, y)->moveTo(x - 2, y);
					moveTo(x - 1, y);
				}
			}
			break;
		case KEY_PRESS_RIGHT:
			setDirection(0);
			if (moveIfPossible()) {
				moveTo(x + 1, y);
				break;
			}
			if (getWorld()->getActor(x + 1, y)->isSwallowable()) {
				if (getWorld()->getActor(x + 1, y)->bePushedBy(this, x + 1, y)) {
					getWorld()->getActor(x + 1, y)->moveTo(x + 2, y);
					moveTo(x + 1, y);
				}
			}
			break;
		case KEY_PRESS_SPACE:
			//introduce pea object
			if (ammo > 0) {
				if (getDirection() == 90) {
					getWorld()->addActor(new Pea(getWorld(), x, y + 1, getDirection()));
				}
				if (getDirection() == 180) {
					getWorld()->addActor(new Pea(getWorld(), x - 1, y, getDirection()));
				}
				if (getDirection() == 0) {
					getWorld()->addActor(new Pea(getWorld(), x + 1, y, getDirection()));
				}
				if (getDirection() == 270) {
					getWorld()->addActor(new Pea(getWorld(), x, y - 1, getDirection()));
				}
				ammo--;
				break;
			}
			break;
		}
	}
}

double Player::getHealthPct() const {
	return static_cast<double>(getHitPoints()) / 20.0 * 100.0;
}

void Player::restoreHealth() {
	setHitPoints(20);
}

void Player::increaseAmmo() {
	ammo+= 20;
}
int Player::getAmmo() const {
	return ammo;
}


void Player::damage(int damageAmt) {
	Actor::damage(damageAmt);
}

//ROBOT

Robot::Robot(StudentWorld* world, int startX, int startY, int imageID, int hitPoints, int score, int startDir)
	: Agent(world, startX, startY, imageID, hitPoints, startDir)
{
	setVisible(true);
	setCurrentTick(0);
}
void Robot::damage(int damageAmt) {
	Actor::damage(damageAmt);
	if (isAlive()) {
		getWorld()->playSound(SOUND_ROBOT_IMPACT);
	}
}

bool Robot::hasClearShot() const {
	int dx = 1;
	int dy = 0;
	if (getDirection() == 90) {
		dx = 0;
		dy = 1;
	}
	else if (getDirection() == 180) {
		dx = -1;
		dy = 0;
	}
	else if (getDirection() == 270) {
		dx = 0;
		dy = -1;
	}
	else if (getDirection() == 0) {
		dx = 1;
		dy = 0;
	}
	if (getWorld()->existsClearShotToPlayer(getX(), getY(), dx, dy)) {
		return false;
	}
	return true;
}

int Robot::getTicks() {
	return (28 - getWorld()->getLevel()) / 4;
}

int Robot::getCurrentTick() {
	return currentTick;
}

void Robot::setCurrentTick(int tick) {
	currentTick = tick;
}

//RAGEBOT
RageBot::RageBot(StudentWorld* world, int startX, int startY, int startDir) 
: Robot(world, startX, startY, IID_RAGEBOT, 10, 0, startDir) 
{
	setVisible(true);
	setHitPoints(10);
}
void RageBot::doSomething() {
	if (getCurrentTick() < getTicks()) {
		setCurrentTick(getCurrentTick() + 1);
	}
	else {
		setCurrentTick(0);
		if (!isAlive()) {
			getWorld()->playSound(SOUND_ROBOT_DIE);
			getWorld()->increaseScore(100);
			return;
		}
		if (hasClearShot()) {
			int x = getX();
			int y = getY();
			if (getDirection() == 90) {
				getWorld()->addActor(new Pea(getWorld(), x, y + 1, getDirection()));
				getWorld()->playSound(SOUND_ENEMY_FIRE);
			}
			if (getDirection() == 180) {
				getWorld()->addActor(new Pea(getWorld(), x - 1, y, getDirection()));
				getWorld()->playSound(SOUND_ENEMY_FIRE);
			}
			if (getDirection() == 0) {
				getWorld()->addActor(new Pea(getWorld(), x + 1, y, getDirection()));
				getWorld()->playSound(SOUND_ENEMY_FIRE);
			}
			if (getDirection() == 270) {
				getWorld()->addActor(new Pea(getWorld(), x, y - 1, getDirection()));
				getWorld()->playSound(SOUND_ENEMY_FIRE);
			}
		}
		else {
			if (!moveIfPossible()) {
				setDirection(getDirection() - 180);
			}
		}
	}
}


//THIEFBOT
ThiefBot::ThiefBot(StudentWorld* world, int startX, int startY, int imageID, int hitPoints, int score) 
: Robot(world, startX, startY, imageID, hitPoints, score, 0) { //thiefbot faces right
	setVisible(true);
	turnDistance = rand() % 6 + 1;
	goodie = nullptr;
}

void ThiefBot::doSomething() {
	return;
}

void ThiefBot::damage(int damageAmt) {
	Robot::damage(damageAmt);
}

int ThiefBot::getTurnDistance() {
	return turnDistance;
}

void ThiefBot::setTurnDistance(int d) {
	turnDistance = d;
}

Actor* ThiefBot::getGoodie() {
	return goodie;
}

void ThiefBot::setGoodie(Actor* g) {
	goodie = g;
}

//REGULAR THIEFBOT
RegularThiefBot::RegularThiefBot(StudentWorld* world, int startX, int startY)
	: ThiefBot(world, startX, startY, IID_THIEFBOT, 5, 0) 
{
	setVisible(true);
	setHitPoints(5);
}

void RegularThiefBot::doSomething() {
	if (getCurrentTick() < getTicks()) {
		setCurrentTick(getCurrentTick() + 1);
	}
	else {
		setCurrentTick(0);
		//doSomething
		if (!isAlive()) {
			getWorld()->playSound(SOUND_ROBOT_DIE);
			getWorld()->increaseScore(10);
			setDead();
			getGoodie()->setVisible(true);
			setGoodie(nullptr);
			return;
		}
		int x = getX();
		int y = getY();
		if (getWorld()->getColocatedStealable(x, y) != nullptr && getGoodie() == nullptr) {
			setGoodie(getWorld()->getColocatedStealable(x, y));
			getGoodie()->setVisible(false);
			getWorld()->playSound(SOUND_ROBOT_MUNCH);
		}
		else {
			if (!moveIfPossible()) {
				if (getGoodie() != nullptr) {
					getGoodie()->moveTo(getX(), getY());
				}
				int currentDirection = getDirection();
				int newDirection = currentDirection;
				while (newDirection == currentDirection) {
					int d = rand() % 4 + 1;
					if (d == 1)
						newDirection = 0;
					else if (d == 2)
						newDirection = 90;
					else if (d == 3)
						newDirection = 180;
					else
						newDirection = 270;
				}
				setDirection(newDirection);
			}
		}
	}
}

//MEAN THIEFBOT
MeanThiefBot::MeanThiefBot(StudentWorld* world, int startX, int startY) 
	: ThiefBot(world, startX, startY, IID_MEAN_THIEFBOT, 8, 0)
{
	setHitPoints(8);
	setVisible(true);
}

void MeanThiefBot::doSomething() {
	if (getCurrentTick() < getTicks()) {
		setCurrentTick(getCurrentTick() + 1);
	}
	else {
		setCurrentTick(0);
		//doSomething
		if (!isAlive()) {
			getWorld()->playSound(SOUND_ROBOT_DIE);
			setDead();
			getWorld()->increaseScore(20);
			getGoodie()->setVisible(true);
			setGoodie(nullptr);
			return;
		}
		int x = getX();
		int y = getY();
		if (getWorld()->getColocatedStealable(x, y) != nullptr && getGoodie() == nullptr) {
			setGoodie(getWorld()->getColocatedStealable(x, y));
			getGoodie()->setVisible(false);
			getWorld()->playSound(SOUND_ROBOT_MUNCH);
		}
		else {
			if (hasClearShot()) {
				int x = getX();
				int y = getY();
				if (getDirection() == 90) {
					getWorld()->addActor(new Pea(getWorld(), x, y + 1, getDirection()));
				}
				if (getDirection() == 180) {
					getWorld()->addActor(new Pea(getWorld(), x - 1, y, getDirection()));
				}
				if (getDirection() == 0) {
					getWorld()->addActor(new Pea(getWorld(), x + 1, y, getDirection()));
				}
				if (getDirection() == 270) {
					getWorld()->addActor(new Pea(getWorld(), x, y - 1, getDirection()));
				}
			}
			if (!moveIfPossible()) {
				setTurnDistance(rand() % 6 + 1);
				int d = rand() % 4 + 1;
				if (d == 1)
					setDirection(0);
				else if (d == 2)
					setDirection(90);
				else if (d == 3)
					setDirection(180);
				else {
					setDirection(270);
				}
			}
		}

	}
}
//END OF AGENTS*****************

//Wall
Wall::Wall(StudentWorld* world, int startX, int startY) : Actor(world, startX, startY, IID_WALL, 1, none) {
	setVisible(true);
	setHitPoints(1);

}

//Pea
Pea::Pea(StudentWorld* world, int startX, int startY, int startDir) : Actor(world, startX, startY, IID_PEA, 1, startDir) {
	setHitPoints(1);
	if (isAlive()) {
		setVisible(true);
	}
}

void Pea::doSomething() {
	if (!isAlive()) {
		return;
	}
	int x = getX();
	int y = getY();

	if (getWorld()->damageSomething(this, 2)) {
		setDead();
	}
	else {
		switch (getDirection()) {
		case 0:
			if (getWorld()->getActor(x + 1, y) == nullptr || !getWorld()->getActor(x + 1, y)->stopsPea()) {
				moveTo(x + 1, y);
				break;
			}
			getWorld()->getActor(x + 1, y)->damage(2);
			setDead();
			break;
		case 90:
			if (getWorld()->getActor(x, y + 1) == nullptr || !getWorld()->getActor(x, y + 1)->stopsPea()) {
				moveTo(x, y + 1);
				break;
			}
			getWorld()->getActor(x, y + 1)->damage(2);
			setDead();
			break;
		case 180:
			if (getWorld()->getActor(x - 1, y) == nullptr || !getWorld()->getActor(x - 1, y)->stopsPea()) {
				moveTo(x - 1, y);
				break;
			}
			getWorld()->getActor(x - 1, y)->damage(2);
			setDead();
			break;
		case 270:
			if (getWorld()->getActor(x, y - 1) == nullptr || !getWorld()->getActor(x, y - 1)->stopsPea()) {
				moveTo(x, y - 1);
				break;
			}
			getWorld()->getActor(x, y - 1)->damage(2);
			setDead();
			break;

		default:
			setDead();
		}
	}
}

Exit::Exit(StudentWorld* world, int startX, int startY) : Actor(world, startX, startY, IID_EXIT, 1, none), playedSound(false) {
	setVisible(false);
	setHitPoints(1);
}
void Exit::doSomething() {
	if (getWorld()->anyCrystals() == false) {
		if (!playedSound) {
			getWorld()->playSound(SOUND_REVEAL_EXIT);
			playedSound = true;
		}
		setVisible(true);
		if (getWorld()->isPlayerColocatedWith(getX(), getY())) {
			getWorld()->setLevelFinished();
		}
	}
}

Marble::Marble(StudentWorld* world, int startX, int startY) : Actor(world, startX, startY, IID_MARBLE, 10, none) {
	setHitPoints(10);
	if (isAlive()) {
		setVisible(true);
	}
}

void Marble::damage(int damageAmt) {
	Actor::damage(damageAmt);
}

bool Marble::bePushedBy(Actor* a, int x, int y) {
	switch (a->getDirection()) {
	case 90:
		if (getWorld()->canMarbleMoveTo(x, y + 1) && a->getY() == y - 1) {
			return true;
		}
		break;
	case 270:
		if (getWorld()->canMarbleMoveTo(x, y - 1) && a->getY() == y + 1) {
			return true;
		}
		break;
	case 0:
		if (getWorld()->canMarbleMoveTo(x + 1, y) && a->getX() == x - 1) {
			return true;
		}
		break;
	case 180:
		if (getWorld()->canMarbleMoveTo(x - 1, y) && a->getX() == x + 1) {
			return true;
		}
		break;
	}
	return false;
}


Pit::Pit(StudentWorld* world, int startX, int startY) : Actor(world, startX, startY, IID_PIT, none, none) {
	setVisible(true);
	setHitPoints(1);
}

void Pit::doSomething() {
	if (!isAlive()) {
		return;
	}
	int x = getX();
	int y = getY();
	if (getWorld()->swallowSwallowable(this)) {
		setDead();
	}
}

//PICKUPABLE ITEMS
PickupableItem::PickupableItem(StudentWorld* world, int startX, int startY, int imageID, int score)
	: Actor(world, startX, startY, imageID, none, none)
{
	setHitPoints(1);
}

//CRYSTAL
Crystal::Crystal(StudentWorld* world, int startX, int startY) 
	: PickupableItem(world, startX, startY, IID_CRYSTAL, 50)
{
	setVisible(true);
}

void Crystal::doSomething() {
	if (!(isAlive())) {
		return;
	}
	int x = getX();
	int y = getY();
	if (getWorld()->isPlayerColocatedWith(x, y)) {
		getWorld()->decCrystals();
		getWorld()->increaseScore(50);
		setDead();
	}
}

//GOODIES
Goodie::Goodie(StudentWorld* world, int startX, int startY, int imageID, int score) 
	: PickupableItem(world, startX, startY, imageID, score)
{

}

//EXTRA LIFE GOODIE
ExtraLifeGoodie::ExtraLifeGoodie(StudentWorld* world, int startX, int startY) 
	: Goodie(world, startX, startY, IID_EXTRA_LIFE, 1000)
{
	setVisible(true);
}

void ExtraLifeGoodie::doSomething() {
	if (!(isAlive())) {
		return;
	}
	int x = getX();
	int y = getY();
	if (getWorld()->isPlayerColocatedWith(x, y)) {
		setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->incLives();
		getWorld()->increaseScore(50);
	}
}

//RESTOREHEALTH GOODIE
RestoreHealthGoodie::RestoreHealthGoodie(StudentWorld* world, int startX, int startY)
	: Goodie(world, startX, startY, IID_RESTORE_HEALTH, 500)
{
	setVisible(true);
}

void RestoreHealthGoodie::doSomething() {
	if (!(isAlive())) {
		return;
	}
	int x = getX();
	int y = getY();
	if (getWorld()->isPlayerColocatedWith(x, y)) {
		setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->restorePlayerHealth();
		getWorld()->increaseScore(500);
	}
}

//AMMO GOODIE
AmmoGoodie::AmmoGoodie(StudentWorld* world, int startX, int startY) 
	: Goodie(world, startX, startY, IID_AMMO, 100)
{
	setVisible(true);
}

void AmmoGoodie::doSomething() {
	if (!(isAlive())) {
		return;
	}
	int x = getX();
	int y = getY();
	if (getWorld()->isPlayerColocatedWith(x, y)) {
		setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->increaseScore(100);
		getWorld()->increaseAmmo();
	}
}

//FACTORY
ThiefBotFactory::ThiefBotFactory(StudentWorld* world, int startX, int startY, ProductType type) 
	: Actor(world, startX, startY, IID_ROBOT_FACTORY, 1, none)
{
	setVisible(true);
	setHitPoints(1);
	_type = type;
}

void ThiefBotFactory::doSomething() {
	int count = 0;
	if (getWorld()->doFactoryCensus(getX(), getY(), 3, count)) {
		if (count < 3 && !getWorld()->getActor(getX(), getY())->countsInFactoryCensus()) {
			int random = rand() % 50 + 1;
			if (random == 50) {
				if (_type == MEAN) {
					getWorld()->addActor(new MeanThiefBot(getWorld(), getX(), getY()));
				}
				else if (_type == REGULAR) {
					getWorld()->addActor(new RegularThiefBot(getWorld(), getX(), getY()));
				}
				getWorld()->playSound(SOUND_ROBOT_BORN);
			}
		}
	}
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
