// src/LegalMoves.cpp
#include "include/LegalMoves.h"
#include <sstream>

LegalMoves::LegalMoves(const ChessBoard &cb) : chessBoard(cb) {}

std::vector<std::string> LegalMoves::generateMoves()
{
    std::vector<std::string> moves;

    if (chessBoard.getIsWhiteTurn())
    {
        moves = generateWhitePawnMoves();
    }
    else
    {
        moves = generateBlackPawnMoves();
    }

    // TODO: generate moves for other pieces

    std::vector<std::string> castlingMoves = generateCastlingMoves();
    moves.insert(moves.end(), castlingMoves.begin(), castlingMoves.end());

    return moves;
}

std::vector<std::string> LegalMoves::generateWhitePawnMoves()
{
    std::vector<std::string> moves;
    Bitboard whitePawns = chessBoard.getWhitePawns();

    // generate moves for white pawns
    for (int i = 0; i < 64; ++i)
    {
        if (whitePawns.isSet(i))
        {
            // check if the pawn can move forward one square
            if (i < 56 && !chessBoard.isOccupied(i + 8))
            {
                moves.push_back(squareToString(i) + squareToString(i + 8));

                // check if the pawn can move forward two squares
                if (i < 16 && !chessBoard.isOccupied(i + 16))
                {
                    moves.push_back(squareToString(i) + squareToString(i + 16));
                }
            }

            // check if the pawn can capture diagonally
            if (i % 8 != 0 && i < 56 && chessBoard.isOccupiedByBlack(i + 7))
            {
                moves.push_back(squareToString(i) + squareToString(i + 7));
            }
            if (i % 8 != 7 && i < 56 && chessBoard.isOccupiedByBlack(i + 9))
            {
                moves.push_back(squareToString(i) + squareToString(i + 9));
            }
        }
    }

    return moves;
}

std::vector<std::string> LegalMoves::generateBlackPawnMoves()
{
    std::vector<std::string> moves;
    Bitboard blackPawns = chessBoard.getBlackPawns();

    // generate moves for black pawns
    for (int i = 0; i < 64; ++i)
    {
        if (blackPawns.isSet(i))
        {
            // check if the pawn can move forward one square
            if (i >= 8 && !chessBoard.isOccupied(i - 8))
            {
                moves.push_back(squareToString(i) + squareToString(i - 8));

                // check if the pawn can move forward two squares
                if (i >= 48 && !chessBoard.isOccupied(i - 16))
                {
                    moves.push_back(squareToString(i) + squareToString(i - 16));
                }
            }

            // check if the pawn can capture diagonally
            if (i % 8 != 0 && i >= 8 && chessBoard.isOccupiedByWhite(i - 9))
            {
                moves.push_back(squareToString(i) + squareToString(i - 9));
            }
            if (i % 8 != 7 && i >= 8 && chessBoard.isOccupiedByWhite(i - 7))
            {
                moves.push_back(squareToString(i) + squareToString(i - 7));
            }
        }
    }

    return moves;
}

std::vector<std::string> LegalMoves::generateRookMoves(int position)
{
    std::vector<std::string> moves;
    int rank = position / 8, file = position % 8;

    // Horizontal moves
    for (int f = 0; f < 8; ++f)
    {
        if (f != file)
        {
            int newPosition = rank * 8 + f;
            if (!chessBoard.isOccupied(newPosition))
            {
                moves.push_back(squareToString(position) + squareToString(newPosition));
            }
            else
            {
                break;
            }
        }
    }

    // Vertical moves
    for (int r = 0; r < 8; ++r)
    {
        if (r != rank)
        {
            int newPosition = r * 8 + file;
            if (!chessBoard.isOccupied(newPosition))
            {
                moves.push_back(squareToString(position) + squareToString(newPosition));
            }
            else
            {
                break;
            }
        }
    }

    return moves;
}

std::vector<std::string> LegalMoves::generateBishopMoves(int position)
{
    std::vector<std::string> moves;
    int rank = position / 8, file = position % 8;

    // Diagonal moves
    for (int offset = 1; offset < 8; ++offset)
    {
        if (rank + offset < 8 && file + offset < 8)
        {
            int newPosition = (rank + offset) * 8 + (file + offset);
            if (!chessBoard.isOccupied(newPosition))
            {
                moves.push_back(squareToString(position) + squareToString(newPosition));
            }
            else
            {
                break;
            }
        }
    }

    for (int offset = 1; offset < 8; ++offset)
    {
        if (rank - offset >= 0 && file - offset >= 0)
        {
            int newPosition = (rank - offset) * 8 + (file - offset);
            if (!chessBoard.isOccupied(newPosition))
            {
                moves.push_back(squareToString(position) + squareToString(newPosition));
            }
            else
            {
                break;
            }
        }
    }

    return moves;
}

std::vector<std::string> LegalMoves::generateKnightMoves(int position)
{
    std::vector<std::string> moves;
    int rank = position / 8, file = position % 8;

    // knight moves
    int offsets[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    for (int i = 0; i < 8; ++i)
    {
        int newRank = rank + offsets[i][0], newFile = file + offsets[i][1];
        if (newRank >= 0 && newRank < 8 && newFile >= 0 && newFile < 8)
        {
            int newPosition = newRank * 8 + newFile;
            if (!chessBoard.isOccupied(newPosition))
            {
                moves.push_back(squareToString(position) + squareToString(newPosition));
            }
        }
    }

    return moves;
}

std::vector<std::string> LegalMoves::generateQueenMoves(int position)
{
    // queen moves
    std::vector<std::string> rookMoves = generateRookMoves(position);
    std::vector<std::string> bishopMoves = generateBishopMoves(position);
    rookMoves.insert(rookMoves.end(), bishopMoves.begin(), bishopMoves.end());
    return rookMoves;
}
std::vector<std::string> LegalMoves::generateKingMoves(int position)
{
    std::vector<std::string> moves;
    int rank = position / 8, file = position % 8;

    // King moves
    int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < 8; ++i)
    {
        int newRank = rank + offsets[i][0], newFile = file + offsets[i][1];
        if (newRank >= 0 && newRank < 8 && newFile >= 0 && newFile < 8)
        {
            int newPosition = newRank * 8 + newFile;
            if (!chessBoard.isOccupied(newPosition))
            {
                moves.push_back(squareToString(position) + squareToString(newPosition));
            }
        }
    }

    return moves;
}

std::vector<std::string> LegalMoves::generateCastlingMoves()
{
    std::vector<std::string> moves;

    if (canCastleKingside(true))
        moves.push_back("e1g1");
    if (canCastleQueenside(true))
        moves.push_back("e1c1");
    if (canCastleKingside(false))
        moves.push_back("e8g8");
    if (canCastleQueenside(false))
        moves.push_back("e8c8");

    return moves;
}

bool LegalMoves::canCastleKingside(bool isWhite) const
{
    // TODO: Check if the king and the kingside rook have not moved,
    // and the squares between them are not attacked by enemy pieces.
    return false;
}

bool LegalMoves::canCastleQueenside(bool isWhite) const
{
    // TODO: Check if the king and the queenside rook have not moved,
    // and the squares between them are not attacked by enemy pieces.
    return false;
}

std::string LegalMoves::squareToString(int square)
{
    return std::string(1, 'a' + (square % 8)) + std::to_string(8 - square / 8);
}