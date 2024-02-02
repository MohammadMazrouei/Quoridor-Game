
# Quoridor Game in C++

This repository contains the C++ implementation of the Quoridor game, a strategy board game for 2 to 4 players. The aim is to reach the opposite side of the board while hindering your opponent's progress by strategically placing walls.

## Features

- Support for 2, 3, and 4-player games.
- Various game modes including classic and Daliz versions.
- Command-line interface for game interaction.
- Leaderboard functionality to track high scores.
- Help section for new players.

## Getting Started

### Prerequisites

- A C++ compiler (GCC recommended)
- Wine (if running on non-Windows platforms)

### Compilation

To compile the game, use the following command in the terminal:

```bash
g++ -o Quoridor qouridor.cpp
```

Or, if you are using `winegcc` for a Windows-like environment on Linux:

```bash
wineg++ -o Quoridor.exe qourider.cpp
```

### Running the Game

After compilation, you can start the game by running:

```bash
./Quoridor
```

On Windows or Wine:

```bash
wine Quoridor.exe
```

## Gameplay

1. Start the game by choosing the number of players (2, 3, or 4) and the game mode (Classic, Daliz, etc.).
2. Follow the on-screen instructions to place walls and move your pawn.
3. Reach the opposite side of the board before your opponents to win.

## How to Play a Move

In the Quoridor game, players can move their pawn or place walls to hinder their opponents' progress. Here's how to make your move:

### Moving Your Pawn

- **Directional Moves:** To move your pawn, enter the direction you wish to move (up, down, left, right) when prompted. The game will check for the legality of the move based on the current board state and the presence of any walls.

### Placing Walls

- **Wall Placement:** You can place walls to block your opponents' paths. When it's your turn to place a wall, specify the wall's orientation (horizontal or vertical) and position (e.g., `_ab12` for a horizontal wall, `|ab12` for a vertical wall). The game ensures that all wall placements are valid and do not completely block any player's path to the goal.

Remember, the objective is to reach the opposite side of the board first. Use your walls wisely to create paths for yourself and obstacles for your opponents!

## Strategy Tips

- **Plan Your Route:** Always be aware of the shortest path to your goal and plan your moves accordingly.
- **Use Walls Strategically:** Instead of using walls early in the game, consider saving them for critical moments to effectively block your opponents.
- **Adapt Your Strategy:** Keep an eye on your opponents' moves and be ready to adapt your strategy. Blocking an opponent's path might sometimes be more beneficial than advancing your own pawn.

## Contributing

Contributions to the Quoridor game project are welcome. Please feel free to fork the repository, make your changes, and submit a pull request.

## License

This project is open source and available under the [MIT License](LICENSE).

## Acknowledgments

- Inspired by the original Quoridor game.
- Thanks to all contributors and players.
