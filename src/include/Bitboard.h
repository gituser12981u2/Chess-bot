// src/Bitboard.h
#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>

class Bitboard
{
public:
    Bitboard();
    void set(int position);
    void clear(int position);
    bool isSet(int position) const;
    void print() const;
    void reset();

private:
    uint64_t bits;
};

#endif // BITBOARD_H