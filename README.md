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

**Part #1 Submission:**

source code for the simple version of the game. Ensure that your code builds without errors under either Visual Studio or Xcode. The submission should be a zip file containing only the following four files:

1. `Actor.h`
2. `Actor.cpp`
3. `StudentWorld.h`
4. `StudentWorld.cpp`

These files should include the necessary declarations and implementations for the base, Avatar, and Wall classes, as well as any constants required by these classes. Your `StudentWorld.h` and `StudentWorld.cpp` files should contain the declaration and implementation of your `StudentWorld` class.

Do not include any additional files in the zip file. The provided files will be used for testing your code. Remember not to modify any of the provided files except for the string literal "Assets" in `main.cpp`. No report is required for Part #1, and it won't be evaluated for program comments, documentation, or test cases. Correct behavior for the specified subset of requirements is the primary focus.

**Part #2 Submission:**

For Part #2 of the project, you must implement a fully working version of the Marble Madness game, adhering precisely to the functional specification provided. The submission requirements are similar to Part #1, but with an additional report:

1. **Source Code**: Submit your game's source code, which should build without errors under Visual Studio or Xcode. Include the following five files in a zip file:
   - `Actor.h`
   - `Actor.cpp`
   - `StudentWorld.h`
   - `StudentWorld.cpp`
   - `report.docx` or `report.txt`

2. **Report**: The report should contain the following:
   - **Description of Control Flow**: Explain how the player avatar and a goodie interact in terms of control flow. Detail where in the code the co-location of the two objects is detected and what happens from that point until the interaction is finished. Describe which functions of which objects are called and what they do during the handling of this situation.
   - **Functionality Not Finished and Known Bugs**: Provide a list of all functionality that you failed to finish and any known bugs in your classes. For example, mention if you didn't implement a specific class or if there are issues with a particular feature.
   - **Design Decisions and Assumptions**: List any other design decisions and assumptions you made during the development process. For instance, explain how you handled situations not specified in the requirements.

Remember not to modify any of the provided files except for the string literal "Assets" or the value of the constant `msPerTick` in `main.cpp`.
