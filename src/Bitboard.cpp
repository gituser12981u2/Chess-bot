// src/Bitboard.cpp
#include "include/Bitboard.h"
#include <bitset>
#include <iostream>

// Initialize the bitboard with all zeros.
Bitboard::Bitboard() : bits(0) {}

// Set the bit at the given position (0-63).
void Bitboard::set(int position)
{
    bits |= (1ULL << position);
}

// Clear the bit at the given position (0-63).
void Bitboard::clear(int position)
{
    bits &= ~(1ULL << position);
}

// check if the bit is set already
bool Bitboard::isSet(int position) const
{
    return bits & (1ULL << position);
}

void Bitboard::reset()
{
    bits = 0;
}

// Print the bitboard as an 8x8 grid.
void Bitboard::print() const
{
    for (int rank = 7; rank >= 0; --rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            int position = rank * 8 + file;
            std::cout << ((bits >> position) & 1) << ' ';
        }
        std::cout << '\n';
    }
}