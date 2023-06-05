// src/UCIHandler.cpp
#include "include/UCIHandler.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

UCIHandler::UCIHandler(ChessBoard &cb) : chessBoard(cb), legalMoves(cb) {}

void UCIHandler::handleCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::string word;
    iss >> word;

    if (word == "uci")
    {
        std::cout << "id name MyChessBot\n";
        std::cout << "uciok\n";
    }
    else if (word == "isready")
    {
        std::cout << "readyok\n";
    }
    else if (word == "position")
    {
        iss >> word;
        if (word == "startpos")
        {
            // Set the position to the starting position
            chessBoard.setPosition(ChessBoard::STARTPOS_FEN);

            iss >> word;
            if (word == "moves")
            {
                // Apply each move in the list
                int moveCount = 0;
                while (iss >> word)
                {
                    chessBoard.applyMove(word);
                    moveCount++;
                }
                chessBoard.setIsWhiteTurn(moveCount % 2 == 0);
            }
        }
        else
        {
            std::string fen = word;
            while (iss >> word)
            {
                fen += " " + word;
            }
            chessBoard.setPosition(fen);
        }
    }
    else if (word == "go")
    {
        int wtime = 0, btime = 0, winc = 0, binc = 0;
        while (iss >> word)
        {
            if (word == "wtime")
            {
                iss >> wtime;
            }
            else if (word == "btime")
            {
                iss >> btime;
            }
            else if (word == "winc")
            {
                iss >> winc;
            }
            else if (word == "binc")
            {
                iss >> binc;
            }
        }

        std::vector<std::string> moves = legalMoves.generateMoves();
        if (!moves.empty())
        {
            // seed the random number generator
            std::srand(std::time(0));
            // choose a random move
            std::string move = moves[std::rand() % moves.size()];
            std::cout << "bestmove " << move << "\n";
        }
    }
    else if (command == "quit")
    {
        exit(0);
    }
    // TODO: handle other UCI commands
}
