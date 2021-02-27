#pragma once

#include <string>
#include <array>
#include <unordered_set>

namespace chessed { namespace chess {

enum Piece
{
    OutOfBounds,
    Empty,
    WhiteKing,
    WhiteQueen,
    WhiteBishop,
    WhiteRook,
    WhiteKnight,
    WhitePawn,
    BlackKing,
    BlackQueen,
    BlackBishop,
    BlackRook,
    BlackKnight,
    BlackPawn
};

enum Color
{
    White,
    Black,
    None
};

typedef std::string Square;
typedef std::unordered_set<Square> Squares;
typedef std::array<Piece, 64> GameState;

inline Color color(Piece p)
{
    switch (p)
    {
        case WhitePawn:
        case WhiteKnight:
        case WhiteBishop:
        case WhiteRook:
        case WhiteQueen:
        case WhiteKing:
            return White;
        case BlackPawn:
        case BlackKnight:
        case BlackBishop:
        case BlackRook:
        case BlackQueen:
        case BlackKing:
            return Black;
        case Empty:
        case OutOfBounds:
        default:
            return None;
    }
}

inline bool empty_or_oob(const Piece& p)
{
    return p == Empty || p == OutOfBounds;
}

}}