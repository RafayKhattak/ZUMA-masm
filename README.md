# Game Project: **[ZUMA]**

## Description

This project is a **[ZUMA]** game built in **Assembly** language using **x86 architecture**. It includes various game screens such as the logo, menu, instructions, high scores, gameplay, pause, and game over. The project uses system calls and custom macros to handle input, display graphics, and manage game logic, providing a structured way to implement basic game functionality.

![1](https://github.com/user-attachments/assets/183fbdea-a1d7-42aa-a824-737fc705c037)
![2](https://github.com/user-attachments/assets/acb4aae4-a1f3-4da7-bb91-1a809c5be3c6)

---

## Features

- **Multiple Game Screens**:
  - Logo Screen
  - Menu Screen
  - Enter Name Screen
  - High Scores Screen
  - Instructions Screen
  - Pause Game Screen
  - Game Over Screen
- **Game State Management**: Efficient switching between different states such as the game logo, menu, and gameplay.
- **Score and Level Tracking**: Keeps track of the player's score, current level, and remaining lives.
- **Input Handling**: Reads key presses to navigate through menus, pause the game, or enter a name.
- **Time Handling**: Accurate calculation of elapsed time for the game loop and levels.
- **File Handling**: Load and sort high scores.
- **Multimedia Support**: Uses Windows Multimedia library for time-based functionalities.

---

## Prerequisites

### Required Libraries

The project uses the following libraries:
- **Irvine32.lib**: Provides basic I/O functions like `ReadKey`, `Sleep`, etc.
- **winmm.lib**: For multimedia functions, mainly used for managing time and delays.
- **kernel32.lib**: Basic system functions like `ExitProcess`.

---

## Project Structure

### `game_macros.inc`

This file contains custom macros used throughout the project. These macros help manage different game states, such as displaying the logo screen or managing menu inputs. The use of macros ensures the code remains efficient and modular.

### `filehandling.inc`

This file handles file I/O operations such as saving and loading high scores. It also contains functions to manage the score records and ensure proper storage and retrieval.

### `graphics.inc`

Handles basic graphics-related functions to display the different game screens, including the logo, menu, and other visual elements.

### `game_screens.inc`

Contains functions for rendering various game screens based on the current game state (e.g., displaying the main menu, game over screen).

### `game_play.inc`

Defines game logic and gameplay management, including the calculation of score, levels, and handling user input during gameplay.

### `menu_screens.inc`

Handles the functionality of the game’s menus, including the main menu and any other in-game menus.

### `menu.inc`

Contains basic menu logic, input handling, and transitions between different game states from the menu.

---

## Installation

### Requirements

- **Assembler**: You'll need an assembler that supports 32-bit x86 assembly code (e.g., **MASM**, **TASM**, or **FASM**).
- **Windows Operating System**: Since the project uses Windows system libraries like **kernel32.lib** and **winmm.lib**, it should be run on a Windows environment.

---

## Game States

The game uses different states to manage the flow of the game. The following states are defined:

- **LOGO_SCREEN**: Displays the game’s logo at the start.
- **MENU_SCREEN**: The main menu where the user can start the game, view high scores, etc.
- **ENTER_NAME**: Screen to enter the player's name.
- **EXIT_SCREEN**: Exit the game after showing the exit screen.
- **HIGH_SCORE**: Shows the list of top scores.
- **INSTRUCTION_SCREEN**: Displays the instructions for playing the game.
- **PAUSE_GAME**: Pauses the game during gameplay.
- **STAT_SCREEN**: Displays user statistics like score, level, and lives.
- **OVER_SCREEN**: Shows the game over screen when the player loses all lives.

---

## Functions Overview

### `main_game_loop`

The main loop of the game, which continuously checks the `gameState` variable and handles game flow, such as rendering different screens, processing user input, and calling the necessary functions to update the game state.

### Time Management

The game uses the **`GetTickCount`** function to measure the time elapsed between game frames and update the elapsed time for gameplay. The `Sleep` function is used to introduce delays between actions.

### Input Handling

The game reads key presses from the user to navigate between screens and perform actions. Key presses are handled via the **`ReadKey`** function, which processes the user's input.

---

## Usage

1. **Starting the Game**: The game will begin with the logo screen. Press a key to move to the main menu.
2. **Main Menu**: Choose options like:
   - Start Game
   - View High Scores
   - View Instructions
   - Exit Game
3. **Gameplay**: Once you start the game, you’ll enter the gameplay state, where you can earn points, progress through levels, and lose lives.
4. **Pause**: Press a key to pause the game, returning to the pause menu.
5. **Game Over**: If you lose all lives, the game will show the game over screen and allow you to restart or exit.
6. **High Scores**: View the top scores and sort them to see how you compare against others.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- **Irvine32 Library**: A powerful library for assembly language programming with Windows.
- **MASM**: The assembler used for compiling the code.
- **Windows Multimedia API**: Provides functions to manage system time, multimedia functions, and system-level tasks.
- Custom macros and functions built specifically for this project.

---
