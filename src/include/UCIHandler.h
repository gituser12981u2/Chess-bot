// src/include/UCIHandler.h
#ifndef UCIHANDLER_H
#define UCIHANDLER_H

#include "ChessBoard.h"
#include "LegalMoves.h"
#include <string>

class UCIHandler
{
public:
    UCIHandler(ChessBoard &cb);
    void handleCommand(const std::string &command);

private:
    ChessBoard &chessBoard;
    LegalMoves legalMoves;
};

#endif // UCIHANDLER_H
