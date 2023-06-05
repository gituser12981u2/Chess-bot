// src/ChessBoard.cpp
#include "include/ChessBoard.h"
#include <iostream>
#include <sstream>

const std::string ChessBoard::STARTPOS_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

ChessBoard::ChessBoard()
{
    setPosition(STARTPOS_FEN);
}

void ChessBoard::setPosition(const std::string &fen)
{
    // Reset the bitboards
    white_pawns.reset();
    white_rooks.reset();
    white_knights.reset();
    white_bishops.reset();
    white_queen.reset();
    white_king.reset();

    black_pawns.reset();
    black_rooks.reset();
    black_knights.reset();
    black_bishops.reset();
    black_queen.reset();
    black_king.reset();

    // Parse the fen string
    std::istringstream fenStream(fen);
    std::string board, turn, castling, enPassant, halfmove, fullmove;

    fenStream >> board >> turn >> castling >> enPassant >> halfmove >> fullmove;

    // parse the board
    int rank = 7, file = 0;
    for (char c : board)
    {
        if (isdigit(c))
        {
            file += c - '0';
        }
        else if (c == '/')
        {
            --rank;
            file = 0;
        }
        else
        {
            int position = rank * 8 + file;
            switch (tolower(c))
            {
            case 'p':
                (islower(c) ? black_pawns : white_pawns).set(position);
                break;
            case 'r':
                (islower(c) ? black_rooks : white_rooks).set(position);
                break;
            case 'n':
                (islower(c) ? black_knights : white_knights).set(position);
            case 'b':
                (islower(c) ? black_bishops : white_bishops).set(position);
            case 'q':
                (islower(c) ? black_queen : white_queen).set(position);
            case 'k':
                (islower(c) ? black_king : white_king).set(position);
            }
            ++file;
        }
    }

    // handle turn
    isWhiteTurn = (turn == "w");

    // Handle castling
    canCastleWhiteKingside = (castling.find('K') != std::string::npos);
    canCastleWhiteQueenside = (castling.find('Q') != std::string::npos);
    canCastleBlackKingside = (castling.find('k') != std::string::npos);
    canCastleBlackQueenside = (castling.find('q') != std::string::npos);

    // handle en passant
    enPassantTarget = (enPassant == "-" ? -1 : (enPassant[0] - 'a') + 8 * (enPassant[1] - '1'));

    // handle halfmoves and fullmoves
    if (!halfmove.empty())
    {
        halfMoveClock = std::stoi(halfmove);
    }
    else
    {
        halfMoveClock = 0;
    }

    if (!fullmove.empty())
    {
        fullMoveNumber = std::stoi(fullmove);
    }
    else
    {
        fullMoveNumber = 1;
    }
}

void ChessBoard::applyMove(const std::string &move)
{
    int source = stringToSquare(move.substr(0, 2));
    int destination = stringToSquare(move.substr(2, 2));

    // find the piece that is moving
    Bitboard *piece = nullptr;
    if (white_pawns.isSet(source))
        piece = &white_pawns;
    else if (white_rooks.isSet(source))
        piece = &white_rooks;
    else if (white_knights.isSet(source))
        piece = &white_knights;
    else if (white_bishops.isSet(source))
        piece = &white_bishops;
    else if (white_queen.isSet(source))
        piece = &white_queen;
    else if (white_king.isSet(source))
        piece = &white_king;
    else if (black_pawns.isSet(source))
        piece = &black_pawns;
    else if (black_rooks.isSet(source))
        piece = &black_rooks;
    else if (black_knights.isSet(source))
        piece = &black_knights;
    else if (black_bishops.isSet(source))
        piece = &black_bishops;
    else if (black_queen.isSet(source))
        piece = &black_queen;
    else if (black_king.isSet(source))
        piece = &black_king;

    // move the piece
    if (piece)
    {
        piece->clear(source);
        piece->set(destination);
    }

    // handle castling
    if (piece == &white_king && abs(destination - source) == 2)
    {
        if (destination > source) // kingside castle
        {
            white_rooks.clear(7);
            white_rooks.set(5);
        }
        else // queenside castle
        {
            white_rooks.clear(0);
            white_rooks.set(3);
        }
    }
    else if (piece == &black_king && abs(destination - source) == 2)
    {
        if (destination > source) // kingside castle
        {
            black_rooks.clear(63);
            black_rooks.set(61);
        }
        else // queenside castle
        {
            black_rooks.clear(56);
            black_rooks.set(59);
        }
    }

    // handle en passant
    if (piece == &white_pawns && abs(destination - source) == 9 && !isOccupied(destination))
    {
        black_pawns.clear(destination - 8);
    }
    else if (piece == &black_pawns && abs(destination - source) == 9 && !isOccupied(destination))
    {
        white_pawns.clear(destination + 8);
    }

    // handle pawn promotion
    if (piece == &white_pawns && destination / 8 == 7)
    {
        white_pawns.clear(destination);
        white_queen.set(destination);
    }
    else if (piece == &black_pawns && destination / 8 == 0)
    {
        black_pawns.clear(destination);
        black_queen.set(destination);
    }

    // handle captures
    if (isWhiteTurn)
    {
        if (black_pawns.isSet(destination))
            black_pawns.clear(destination);
        else if (black_rooks.isSet(destination))
            black_rooks.clear(destination);
        else if (black_knights.isSet(destination))
            black_knights.clear(destination);
        else if (black_bishops.isSet(destination))
            black_bishops.clear(destination);
        else if (black_queen.isSet(destination))
            black_queen.clear(destination);
        else if (black_king.isSet(destination))
            black_king.clear(destination);
    }
    else
    {
        if (white_pawns.isSet(destination))
            white_pawns.clear(destination);
        else if (white_rooks.isSet(destination))
            white_rooks.clear(destination);
        else if (white_knights.isSet(destination))
            white_knights.clear(destination);
        else if (white_bishops.isSet(destination))
            white_bishops.clear(destination);
        else if (white_queen.isSet(destination))
            white_queen.clear(destination);
        else if (white_king.isSet(destination))
            white_king.clear(destination);
    }

    switchTurn();
}

int ChessBoard::stringToSquare(const std::string &str)
{
    return (8 - std::stoi(str.substr(1, 1))) * 8 + (str[0] - 'a');
}

bool ChessBoard::isOccupied(int position) const
{
    return white_pawns.isSet(position) || white_rooks.isSet(position) || white_knights.isSet(position) || white_bishops.isSet(position) || white_queen.isSet(position) || white_king.isSet(position) || black_pawns.isSet(position) || black_rooks.isSet(position) || black_knights.isSet(position) || black_bishops.isSet(position) || black_queen.isSet(position) || black_king.isSet(position);
}

bool ChessBoard::isOccupiedByWhite(int position) const
{
    return white_pawns.isSet(position) || white_rooks.isSet(position) || white_knights.isSet(position) || white_bishops.isSet(position) || white_queen.isSet(position) || white_king.isSet(position);
}

bool ChessBoard::isOccupiedByBlack(int position) const
{
    return black_pawns.isSet(position) || black_rooks.isSet(position) || black_knights.isSet(position) || black_bishops.isSet(position) || black_queen.isSet(position) || black_king.isSet(position);
}

Bitboard ChessBoard::getWhitePawns() const
{
    return white_pawns;
}

Bitboard ChessBoard::getBlackPawns() const
{
    return black_pawns;
}

bool ChessBoard::getIsWhiteTurn() const
{
    return isWhiteTurn;
}

void ChessBoard::switchTurn()
{
    isWhiteTurn = !isWhiteTurn;
}

void ChessBoard::setIsWhiteTurn(bool isWhite)
{
    isWhiteTurn = isWhite;
}