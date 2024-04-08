The Marble Madness project involves creating a replica of the game Marble Madness for NachenGames by analyzing stolen prototype files from SmallSoft. Players navigate robot-infested mazes to collect crystals, avoiding hazards and enemies while aiming to complete all levels with limited lives. The game features smooth animation, tick-based gameplay, and dynamic object interactions, including movement, shooting, and scoring mechanisms.


**Marble Madness Game Implementation**

This project involves implementing the Marble Madness game by creating various classes to handle different aspects of the game. The provided classes should work seamlessly with the provided framework without any modifications to the existing code. Here's a summary of what needs to be done:

1. **StudentWorld Class**:
   - Responsible for managing the game world, including the maze and all game actors.
   - Derived from the provided GameWorld class.
   - Implements methods `init()`, `move()`, and `cleanUp()`.
   - `init()` initializes the game world, loads maze details from level data files, and constructs the game world.
   - `move()` orchestrates game play by handling actor actions and interactions.
   - `cleanUp()` clears the game world when a player completes a level or loses a life.

2. **Player Class**:
   - Represents the player's avatar in the game.

3. **Other Actor Classes**:
   - Horizontal/Vertical RageBots, Regular/Mean ThiefBots, factories, marbles, pits, walls, crystals, extra life/restore health/ammo goodies, and the exit.
   - Additional base classes may be created as needed (e.g., a robot base class).

4. **Level Data File**:
   - Maze layout for each level stored in level data files (e.g., `level00.txt`, `level01.txt`, etc.).
   - Characters in the data file represent different actors in the game (e.g., walls, RageBots, ThiefBot factories, crystals, etc.).

5. **Level Class**:
   - Provided class for loading level data files (`Level.h`).
   - Helps in loading maze details from level data files.

6. **Game Mechanics**:
   - Actors perform actions during each tick of the game.
   - Player's avatar and other actors interact based on their behavior.
   - Actors that are no longer active must be removed at the end of each tick.
   - Bonus points decrease with each tick, encouraging players to complete levels quickly.
   - Exit becomes active once all crystals are collected, allowing the player to proceed to the next level.

7. **Game Statistics**:
   - Displayed at the top of the screen.
   - Includes score, level, lives, health, ammo, and bonus.

8. **Framework Integration**:
   - Provided framework calls necessary methods (e.g., `init()`, `move()`, `cleanUp()`).
   - Game status and player input are managed by the framework.

9. **Testing and Debugging**:
   - Framework allows for freezing game activity to examine the screen and step through the game.
   - Actors' movement and interactions should be thoroughly tested.

By implementing these classes and mechanics according to the provided specifications, the Marble Madness game can be created and integrated with the provided framework effectively.
