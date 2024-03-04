#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath)
{
}



int StudentWorld::init()
{
    crystals = 0;
    bonus = 1000;
    Level lev(assetPath());
    string level_str = "level0" + to_string(getLevel()) + ".txt";
    Level::LoadResult result = lev.loadLevel(level_str);
    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find " << level_str << " data file\n";
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted\n";
    else if (result == Level::load_success) {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                Level::MazeEntry item = lev.getContentsOf(i, j);
                if (item == Level::player) {
                    player = new Player(this, i, j);
                    actors.push_back(player);
                }
                if (item == Level::wall) {
                    actors.push_back(new Wall(this, i, j));
                }
                if (item == Level::marble) {
                    actors.push_back(new Marble(this, i, j));
                }
                if (item == Level::exit) {
                    actors.push_back(new Exit(this, i, j));
                }
                if (item == Level::horiz_ragebot) {
                    actors.push_back(new RageBot(this, i, j, 0));
                }
                if (item == Level::vert_ragebot) {
                    actors.push_back(new RageBot(this, i, j, 270));
                }
                if (item == Level::ammo) {
                    actors.push_back(new AmmoGoodie(this, i, j));
                }
                if (item == Level::crystal) {
                    actors.push_back(new Crystal(this, i, j));
                    crystals++;
                }
                if (item == Level::pit) {
                    actors.push_back(new Pit(this, i, j));
                }
                if (item == Level::extra_life) {
                    actors.push_back(new ExtraLifeGoodie(this, i, j));
                }
                if (item == Level::restore_health) {
                    actors.push_back(new RestoreHealthGoodie(this, i, j));
                }
                if (item == Level::mean_thiefbot_factory) {
                    actors.push_back(new ThiefBotFactory(this, i, j, ThiefBotFactory::MEAN));
                }
                if (item == Level::thiefbot_factory) {
                    actors.push_back(new ThiefBotFactory(this, i, j, ThiefBotFactory::REGULAR));
                } //marbles before pits, goodies before thiefbot, thiefbotfactory before thiefbot (already done), 
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you type q
    int score = getScore();
    int level = getLevel();
    int livesLeft = getLives();
    double health = player->getHealthPct();
    int ammo = player->getAmmo();

    ostringstream statusLine;

    statusLine << "Score: " << setw(7) << setfill('0') << score << "  "
        << "Level: " << setw(2) << setfill('0') << level << "  "
        << "Lives: " << setw(2) << setfill(' ') << livesLeft << "  "
        << "Health: " << setw(3) << setfill(' ') << health << "%" << "  "
        << "Ammo: " << setw(3) << setfill(' ') << ammo << "  "
        << "Bonus: " << setw(4) << setfill(' ') << bonus;
    if (bonus > 0) {
        bonus--;
    }
    setGameStatText(statusLine.str());
    list<Actor*>::iterator i = actors.begin();
    while (i != actors.end()) {
        (*i)->doSomething();
        if (!((*i)->isAlive())) {
            delete* i;
            i = actors.erase(i);
        }
        else {
            i++;
        }
        if (!player->isAlive()) {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
    }

    if (finished) {
        increaseScore(bonus);
        if (getLevel() == 3) {
            return GWSTATUS_PLAYER_WON;
        }
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    finished = false;
    for (list<Actor*>::iterator i = actors.begin(); i != actors.end();) {
        delete *i;
        i = actors.erase(i);
    }
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

Actor* StudentWorld::getActor(int x, int y) {
    for (list<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        if ((*i)->getX() == x && (*i)->getY() == y) {
            return *i;
        }
    }
    return nullptr;
}

/*Player* StudentWorld::getPlayer() {
    return player;
}*/

bool StudentWorld::canAgentMoveTo(Agent* agent, int x, int y, int dx, int dy)
{
    for (list<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        if ((*i)->getX() == (x + dx) && (*i)->getY() == (y + dy)) {
            if ((*i)->allowsAgentColocation()) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

bool StudentWorld::canMarbleMoveTo(int x, int y) {
    for (list<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        if ((*i)->getX() == x && (*i)->getY() == y) {
            if ((*i)->allowsMarble()) {
                return true;
            }
            return false;
        }
    }
    return true;
}
bool StudentWorld::isPlayerColocatedWith(int x, int y) {
    int px = player->getX();
    int py = player->getY();
    if (px == x && py == y) {
        return true;
    }
    /*for (list<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        if ((*i)->getX() == x && (*i)->getY() == y && (*i) == player) {
            return true;
        }
    }*/
    return false;
}

bool StudentWorld::damageSomething(Actor* a, int damageAmt) {
    int x = a->getX();
    int y = a->getY();
    for (list<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        if ((*i)->getX() == x && (*i)->getY() == y) {
            if ((*i)->stopsPea()) {
                if ((*i)->isDamageable()) {
                    (*i)->damage(damageAmt);
                }
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::swallowSwallowable(Actor* a) {
    int x = a->getX();
    int y = a->getY();
    for (list<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        if ((*i)->getX() == x && (*i)->getY() == y) {
            if ((*i)->isSwallowable()) {
                (*i)->setDead();
                return true;
            }
        }
    }
    return false;
}
//0, 1 = 90 | 0, -1 = 270 | 1, 0 = 0 | -1, 0 = 180
bool StudentWorld::existsClearShotToPlayer(int x, int y, int dx, int dy) {
    int px = player->getX();
    int py = player->getY();
    if ((dx == 1 && py == y && px > x)) { //right
        while (x != px) {
            Actor* a = getActor(x, y);
            if (a == nullptr || (a != nullptr && a->stopsPea())) {
                return false;
            }
            x++;
        }
    }
    if (dx == -1 && py == y && px < x) { //left
        while (x != px) {
            Actor* a = getActor(x, y);
            if (a == nullptr || (a != nullptr && a->stopsPea())) {
                return false;
            }
            x--;
        }
    }
    if (dy == 1 && px == x && py > y) { //up
        while (y != py) {
            Actor* a = getActor(x, y);
            if (a == nullptr || (a != nullptr && a->stopsPea())) {
                return false;
            }
            y++;
        }
    }
    if (dy == -1 && px == x && py < y) { //down
        while (y != py) {
            Actor* a = getActor(x, y);
            if (a == nullptr || (a != nullptr && a->stopsPea())) {
                return false;
            }
            y--;
        }
    }
    return true;
}

void StudentWorld::addActor(Actor* a) {
    actors.push_front(a);
}

void StudentWorld::increaseAmmo() {
    player->increaseAmmo();
}

void StudentWorld::restorePlayerHealth() {
    player->restoreHealth();
}

Actor* StudentWorld::getColocatedStealable(int x, int y) {
    for (list<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        if ((*i)->getX() == x && (*i)->getY() == y && (*i)->isStealable()) {
            return *i;
        }
    }
    return nullptr;
}

bool StudentWorld::anyCrystals() const {
    return crystals > 0;
}

bool StudentWorld::decCrystals() {
    if (crystals > 0) {
        crystals = crystals - 1;
        return true;
    }
    return false;
}

void StudentWorld::setLevelFinished() {
    playSound(SOUND_FINISHED_LEVEL);
    increaseScore(2000);
    if (getLives() > 0) {
        setFinished();
    }
}

bool StudentWorld::doFactoryCensus(int x, int y, int distance, int& count) {
    count = 0;
    for (int i = x - distance; i < x + distance; i++) {
        for (int j = y - distance; j < y + distance; j++) {
            if (getActor(x, y)->countsInFactoryCensus()) {
                return false;
            }
            else if (getActor(i, j) != nullptr) {
                if (getActor(i, j)->countsInFactoryCensus()) {
                    count++;
                }
            }
        }
    } 
    
    return true;
}







