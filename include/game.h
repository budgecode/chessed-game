#pragma once

#include <string>
#include <array>

namespace chessed { namespace chess {

typedef std::string Square;

enum Piece {
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

struct Move {
    bool is_check;
    bool is_mate;
    bool is_promoting;
    Piece captured;
    Square from;
    Square to;
};

inline int color(Piece p)
{
    switch (p)
    {
        case WhitePawn:
        case WhiteKnight:
        case WhiteBishop:
        case WhiteRook:
        case WhiteQueen:
        case WhiteKing:
            return 0;
        case BlackPawn:
        case BlackKnight:
        case BlackBishop:
        case BlackRook:
        case BlackQueen:
        case BlackKing:
            return 1;
        case Empty:
        default:
            return -1;
    }
}

class Game {

public:
    Game();

    void init_with_fen(const std::string& fen);
    void init_with_pgn(const std::string& pgn) {};
    std::string to_fen() { return ""; };
    std::string to_pgn() { return ""; };
    
    bool move(const Square& from, const Square& to, Move& info);
    bool validate_move(const Square& from, const Square& to, Move& info);

    int turn();
    int move_num();
    int half_moves();

    // Accessors
    Piece& operator[](int);
    Piece& operator[](const Square&);
    Piece& operator()(int, int); 

private:
    std::array<Piece, 64> m_state;
    int m_half_moves;

};

}}
