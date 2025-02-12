# Snake Game in C++

## Overview
This is a simple console-based Snake Game implemented in C++. The game allows the player to control the snake's movement using the keyboard. The objective is to collect the fruit ($) while avoiding collisions with the walls and the snake's own tail.

## Features
- Move the snake using `WASD` keys.
- Fruit appears randomly on the board; eating fruit increases the score and lengthens the tail.
- Game over when the snake collides with the wall or itself.
- Three difficulty levels: Easy, Medium (default), and Hard.
- Option to restart the game after losing.

## Controls
- `W` - Move Up
- `S` - Move Down
- `A` - Move Left
- `D` - Move Right
- `X` - Exit the Game
- 'P' - pause the game

## Difficulty Levels
At the start of the game, you can choose a difficulty level:
1. Easy 
2. Medium 
3. Hard
4. Extemely Difficult

## Compilation & Execution
### Windows (using MinGW/g++)
```sh
 g++ snake_game.cpp -o snake_game.exe
 ./snake_game.exe
```

### Linux/Mac (using g++)
```sh
 g++ snake_game.cpp -o snake_game
 ./snake_game
```

## Requirements
- C++ Compiler (g++, Clang, MSVC)
- Terminal with ANSI support (for Linux/macOS)
- Windows requires `<conio.h>` and `<windows.h>` for keyboard input handling.

## How to Play
1. Run the compiled program.
2. Enter your name when prompted.
3. Choose a difficulty level.
4. Use `WASD` keys to move the snake.
5. Eat fruits to gain points and grow longer.
6. Avoid hitting the walls or yourself.
7. Press `X` to exit the game.
8. Press 'P' to pause the game.
9. After losing, you have the option to restart.

## Known Issues
- The game does not support diagonal movement.
- The snake's speed increases as the difficulty level rises.

## Future Improvements
- Implement a high-score system.
- Add colored output for better visuals.
- Implement a pause/resume feature.
- Add an AI-controlled snake mode.

## Author
Created by Team H Square.
