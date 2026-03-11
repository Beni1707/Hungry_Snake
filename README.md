# 🐍 Snake Game – C++ / Raylib

A simple **2D Snake Game** developed from scratch using **C++** and the **Raylib graphics library**.

The goal of the game is to **eat as many apples as possible** while avoiding collisions with:
- the walls of the square game area
- the snake's own body

Each apple eaten increases the snake's length and the player's score. The game ends when a collision occurs.

---

## 🎮 Features

- Classic Snake gameplay
- Real-time keyboard input
- Score tracking
- Simple and clean 2D graphics
- Smooth game loop using Raylib

---

## 🛠️ Technologies Used

- **C++**
- **Raylib** (graphics, window, input and audio handling)
- **Makefile** for compilation
- **Git / GitHub** for version control

---

## ⚙️ Technical Details

The game was built with a modular structure using C++ and Raylib.

Key concepts implemented:

- **Game Loop**  
  Continuous update and rendering cycle using Raylib functions.

- **Input Handling**  
  Keyboard inputs are used to control the snake's direction.

- **Collision Detection**
  - Snake with walls
  - Snake with its own body
  - Snake with apples

- **Data Structures**
  The snake body is dynamically updated as the snake grows.

- **Rendering**
  Raylib is used to draw the game grid, snake segments, apples, and UI elements.

- **Audio**
  Sound effects are played when:
  - the snake eats an apple
  - the game ends

---

## 📂 Project Structure

```
snake-game/
│
├── .vscode/            # VS Code configuration
├── lib/                # External libraries
├── src/                # Source code files
│
├── main.cpp            # Main program entry point
├── Makefile            # Compilation instructions
│
├── apple.png           # Apple sprite
├── apple1.png          # Alternate apple sprite
├── preview.jpg         # Game preview image
│
├── .gitignore
├── .gitattributes
└── README.md
```

---

## 🚀 How to Run the Game

Make sure Raylib is installed, then compile and run the program:

```bash
g++ main.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./main
```

If you are using **VS Code**, you can also run the project directly by pressing **F5**.
---

## 📌 Learning Objectives
This project helped strengthen my understanding of:

- C++ programming
- Game development fundamentals
- Real-time rendering
- Input handling
- Basic collision detection
- Using Raylib for graphical applications
