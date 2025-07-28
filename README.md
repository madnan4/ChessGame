# Terminal Chess Game ♟️

A terminal-based chess game written in **C++**, supporting full rule validation, legal move enforcement, and turn-based play. Designed with object-oriented principles and tested using **Google Test** to ensure correctness of game mechanics.

---

## 🧩 Features

- Fully functional chess logic: movement, capturing, check/checkmate detection
- Turn-based play with alternating players
- Input validation to prevent illegal moves
- Command-line interface for gameplay
- Unit testing with **Google Test** for critical components

---

## 🛠️ Tech Stack

- **Language:** C++
- **Testing Framework:** Google Test
- **Concepts Used:** OOP (classes for `Piece`, `Board`, `Game`), STL, Game state management

---

## 🚀 How to Run

1. **Clone the repo**
   ```bash
   git clone https://github.com/madnan4/ChessGame.git
   cd ChessGame
2. **Build the project**
   - Make sure you have a C++ compiler installed (e.g., g++, clang++)
   - g++ -std=c++17 -o chess main.cpp Game.cpp Board.cpp Piece.cpp
3. **Run the game**
   - /chess

## 📁 Folder Structure 
    -ChessGame/ 
    |- main.cpp          # Game loop  
    |- chessboard.h/.cpp # Chessboard logic and move validation
    |- square.h/.cpp     # Square representation and piece logic
    |- tests.cpp         # Unit tests using Google Test
    |-  README.md

## 📚 What I Learned
Applied OOP principles to structure game logic cleanly and modularly
Implemented test-driven development using Google Test
Strengthened problem-solving by addressing rule edge cases and input errors
Gained practical experience building a fully interactive C++ CLI application

## 🔧Future Improvements
- Add save/load game state
- Support for castling, en passant, and pawn promotion
- Create a graphical UI using SDL or SFML
