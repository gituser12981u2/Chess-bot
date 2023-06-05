// src/main.cpp
#include "include/ChessBoard.h"
#include "include/UCIHandler.h"
#include <iostream>
#include <string>

int main()
{
    ChessBoard cb;
    UCIHandler uciHandler(cb);

    std::string line;
    while (std::getline(std::cin, line))
    {
        uciHandler.handleCommand(line);
    }

    return 0;
}