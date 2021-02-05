#pragma once

#include <array>
#include <string>

namespace chessed { namespace chess {

enum Piece {
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

typedef std::array<Piece, 64> BoardState;

enum EventType {
    /* RightClickDown,
    RightClickDrag,
    RightClickRelease, */
    DragPieceBegin,
    DragPiece,
    DragPieceEnd
};

struct Square {
    int row;
    int col;
};

struct Event {
    EventType type;
    Square start_index;
    std::string start_square;
    Square current_index;
    std::string current_square;
};

inline int is_white(Piece p)
{
    switch (p)
    {
        case WhitePawn:
        case WhiteKnight:
        case WhiteBishop:
        case WhiteRook:
        case WhiteQueen:
        case WhiteKing:
            return 1;
        case BlackPawn:
        case BlackKnight:
        case BlackBishop:
        case BlackRook:
        case BlackQueen:
        case BlackKing:
            return 0;
        case Empty:
        default:
            return -1;
    }
}

inline Square to_2d(int index)
{
    int row = index / 8;
    int col = index % 8;

    return { row, col };
}

inline int to_1d(int row, int col)
{
    return row * 8 + col;
}

}}
