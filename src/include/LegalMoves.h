// src/include/LegalMoves.h
#ifndef LEGALMOVES_H
#define LEGALMOVES_H

#include "ChessBoard.h"
#include <vector>

class LegalMoves
{
public:
    LegalMoves(const ChessBoard &cb);
    std::vector<std::string> generateMoves();

private:
    const ChessBoard &chessBoard;
    std::vector<std::string> generateWhitePawnMoves();
    std::vector<std::string> generateBlackPawnMoves();

    std::vector<std::string> generateRookMoves(int position);
    std::vector<std::string> generateBishopMoves(int position);
    std::vector<std::string> generateKnightMoves(int position);
    std::vector<std::string> generateQueenMoves(int position);
    std::vector<std::string> generateKingMoves(int position);

    std::vector<std::string> generateCastlingMoves();
    bool canCastleKingside(bool isWhite) const;
    bool canCastleQueenside(bool isWhite) const;

    std::string squareToString(int square);
};

#endif // LEGALMOVES_H