#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
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
{ /*
   Level lev(assetPath()); //fix this
   Level::LoadResult result = lev.loadLevel("level00.txt");
   if (result == Level::load_fail_file_not_found)
       cerr << "Could not find level00.txt data file\n";
   else if (result == Level::load_fail_bad_format)
       cerr << "Your level was improperly formatted\n";
   else if (result == Level::load_success)
   {
       for (int i = 0; i < 15;) {
           for (int j = 0; j < 15; j++) {
               Level::MazeEntry item = lev.getContentsOf(i, j);
               if (item == Level::player) {
                   _avatar = new Avatar(this);
                   actors.push_back(_avatar);
               }
               if (item == Level::wall) {
                   actors.push_back(new Wall(this, i, j));
               }
           }
       }
   }
   */
   return GWSTATUS_CONTINUE_GAME;

}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you type q

    list<Actor*>::iterator i = actors.begin();
    while (i != actors.end()) {
        (*i)->doSomething();
        if (!((*i)->isAlive())) {
            return GWSTATUS_PLAYER_DIED;
        }
        i++;
    }
    double x = _avatar->getX();
    double y = _avatar->getY();
    //if location is a exit square, score + 2000

    setGameStatText("Game will end when you type q");
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    //opposite of init
}

void StudentWorld::addActor(Actor* actor) 
{
    actors.push_front(actor);
}
