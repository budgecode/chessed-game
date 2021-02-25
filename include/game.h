#pragma once

#include <string>
#include <array>
#include <unordered_set>

namespace chessed { namespace chess {

typedef std::string Square;
typedef std::unordered_set<Square> Squares;

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

    int get_turn();
    int get_move_num();
    int get_half_moves();

    Squares get_possible_moves(const Square& from);

    // Accessors
    Piece& operator[](int);
    Piece& operator[](const Square&);
    Piece& operator()(int, int);

private:
    std::array<Piece, 64> m_state;
    int m_half_moves;
    Piece oob = OutOfBounds;
    
    int get_row(const Square& s);
    int get_col(const Square& s);
    int to_index(int row, int col);
    bool empty_or_oob(const Piece& p);

    Square to_square(int row, int col);

    Squares get_moves_for_pawn(const Square& from);
    Squares get_moves_for_bishop(const Square& from);
    Squares get_moves_for_knight(const Square& from);
    Squares get_moves_for_rook(const Square& from);
    Squares get_moves_for_queen(const Square& from);
    Squares get_moves_for_king(const Square& from);

};

}}
