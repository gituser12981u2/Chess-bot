// src/ChessBoard.h
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Bitboard.h"
#include <string>

class ChessBoard
{
public:
    static const std::string STARTPOS_FEN;

    ChessBoard();
    void setPosition(const std::string &position);
    void applyMove(const std::string &move);
    void switchTurn();

    bool isOccupied(int position) const;
    bool isOccupiedByBlack(int position) const;
    bool isOccupiedByWhite(int position) const;

    Bitboard getWhitePawns() const;
    Bitboard getBlackPawns() const;
    void setIsWhiteTurn(bool isWhite);
    bool getIsWhiteTurn() const;

    int stringToSquare(const std::string &str);

private:
    Bitboard white_pawns;
    Bitboard white_rooks;
    Bitboard white_knights;
    Bitboard white_bishops;
    Bitboard white_queen;
    Bitboard white_king;

    Bitboard black_pawns;
    Bitboard black_rooks;
    Bitboard black_knights;
    Bitboard black_bishops;
    Bitboard black_queen;
    Bitboard black_king;

    bool isWhiteTurn;
    bool canCastleWhiteKingside;
    bool canCastleWhiteQueenside;
    bool canCastleBlackKingside;
    bool canCastleBlackQueenside;
    int enPassantTarget;
    int halfMoveClock;
    int fullMoveNumber;
};

#endif // CHESSBOARD_H