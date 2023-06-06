# MyChessBot

MyChessBot is a simple chess bot that uses the Universal Chess Interface (UCI) protocol. It uses a basic random move selection strategy and does not implement any form of AI or machine learning.

## Structure

The project is structured as follows:

MyChessBot/
├── include/
│ ├── Bitboard.h
│ ├── ChessBoard.h
│ ├── LegalMoves.h
│ └── UCIHandler.h
├── src/
│ ├── Bitboard.cpp
│ ├── ChessBoard.cpp
│ ├── LegalMoves.cpp
│ └── UCIHandler.cpp
├── main.cpp
└── Makefile

- `Bitboard`: This class represents a bitboard for each piece of each color; it uses bitwise operators for quick updating of the internal boards.
- `ChessBoard`: This class represents the chess board. It uses bitboards to keep track of the positions of the pieces.
- `LegalMoves`: This class is responsible for generating legal moves.
- `UCIHandler`: This class handles communication with the UCI interface.

## Usage

To build the project, navigate to the project directory and input the command `run make`.

To start the bot, run the resulting executable. The bot communicates via the UCI protocol, so it should be compatible with any chess GUI that supports UCI.

## Future Work

Future improvements will include implementing a chess AI algorithm such as minimax or alpha-beta pruning, adding support for different board representations, or improving the move generation algorithm.

## License

This project is licensed under the terms of the MIT license. For more information, see the [LICENSE](LICENSE) file.

## Acknowledgements

Thank you to everyone who has contributed to this project!

​
