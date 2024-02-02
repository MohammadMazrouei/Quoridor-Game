
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

## Contributing

Contributions to the Quoridor game project are welcome. Please feel free to fork the repository, make your changes, and submit a pull request.

## License

This project is open source and available under the [MIT License](LICENSE).

## Acknowledgments

- Inspired by the original Quoridor game.
- Thanks to all contributors and players.
