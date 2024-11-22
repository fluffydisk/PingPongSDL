# PingPongSDL

**PingPongSDL** is a classic two-player Pong game developed using **SDL2** and **C++**. It includes single-player and two-player modes, with smooth animations, and an engaging gameplay experience.

![Screenshot](https://github.com/user-attachments/assets/9e2487a1-6a74-4bd0-9f96-0b8b913f03fd)

---

## Features

- **Single-player mode:** Play against an AI opponent (Impossible to beat).
- **Two-player mode:** Compete with a friend in local multiplayer.
- **Welcome screen:** Choose between game modes via interface.

---

## Controls

| Action                 | Key (Player 1) | Key (Player 2) |
|------------------------|----------------|----------------|
| Move Paddle Up         | W              | ↑              |
| Move Paddle Down       | S              | ↓              |
| Return to Main Menu    | Mouse (Click "Menu") | Mouse (Click "Menu") |
| Restart Game           | Mouse (Click "Restart") | Mouse (Click "Restart") |

---

## Game Logic Highlights

1. **Ball Dynamics:**
   - The ball speed increases after each score until a maximum cap is reached.
   - Randomized ball angles make gameplay challenging and less predictable.

2. **AI Player:**
   - In single-player mode, Player 2 adapts its position to the ball's y axis.

3. **Score System:**
   - Scores are displayed at the top of the screen.

---

## Project Structure

- **`Game.cpp` and `Game.h`**: Core game logic and flow management.
- **Utils**: Utilities for rendering, event handling, and SDL resource management.
- **Dependencies Folder**: Fonts and SDL library folders used in the game.

---

## License

This project is licensed under the [MIT License](LICENSE).

---
