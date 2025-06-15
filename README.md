# Luxury Pong Game

A modern take on the classic Pong game implemented in C++ using the [Raylib](https://www.raylib.com/) library. This project features:

- Smooth ball and paddle mechanics
- AI opponent with simple tracking logic
- Luxury-themed color palette (gold, silver, bronze)
- Rounded paddle corners for a polished look
- Background music and sound effects for paddle hits and wall collisions
- Gradient background for a sleek visual style
- Score tracking for both player and AI

---

## Demo

![Gameplay screenshot](demo)  

---

## Features

- **Ball Physics:** The ball moves and bounces off paddles and screen borders with sound feedback.
- **Player Controls:** Use `UP` and `DOWN` arrow keys to control the right paddle.
- **AI Opponent:** The left paddle follows the ball vertically with adjustable speed.
- **Audio:** Background music plays continuously; paddle hits and wall collisions trigger sound effects.
- **Visuals:** Luxury colors with a gradient background and semi-transparent center line.

---

## Getting Started

### Prerequisites

- C++ compiler supporting C++11 or later
- [Raylib](https://www.raylib.com/) installed and configured on your system
- Audio assets (`PongBGM.mp3`, `paddle.mp3`, `boader.mp3`) placed in the `assets/` folder

### Build Instructions

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/luxury-pong-game.git
   cd luxury-pong-game
Compile the project (example using g++):

bash
Copy
Edit
g++ -o LuxuryPong main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -std=c++11
Run the executable:

bash
Copy
Edit
./LuxuryPong
Controls
UP Arrow: Move player paddle up

DOWN Arrow: Move player paddle down

ESC: Quit the game

File Structure
bash
Copy
Edit
luxury-pong-game/
│
├── assets/
│   ├── PongBGM.mp3       # Background music
│   ├── paddle.mp3        # Paddle hit sound
│   └── boader.mp3        # Border collision sound
│
├── main.cpp              # Game source code
└── README.md
Notes
Make sure your audio device supports playback and that Raylib is correctly initialized.

The AI paddle speed and difficulty can be adjusted by modifying the AI.speed variable in the code.

The ball resets to the center with random direction after scoring.

License
This project is licensed under the MIT License — see the LICENSE file for details.

Acknowledgments
Raylib for the simple and powerful graphics/audio/game library.

Inspiration from the classic Pong game.

Feel free to contribute or report issues. Enjoy playing the luxury-themed Pong!

