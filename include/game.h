#pragma once

#include "utils.h"

namespace chessed { namespace chess {

struct Move {
    bool is_check;
    bool is_mate;
    bool is_promoting;
    Piece captured;
    Square from;
    Square to;
};

class Game {

public:
    Game();

    void init_with_fen(const std::string& fen);
    void init_with_pgn(const std::string& pgn) {};
    std::string to_fen() { return ""; };
    std::string to_pgn() { return ""; };
    
    bool move(const Square& from, const Square& to, Move& info);
    bool validate_move(const Square& from, const Square& to, Move& info);

    Color get_turn();
    int get_move_num();
    int get_half_moves();

    Squares get_possible_moves(const Square& from);

    const GameState& get_game_state();

    bool is_check();

    // Accessors
    Piece& operator[](int);
    Piece& operator[](const Square&);
    Piece& operator()(int, int);

private:
    GameState m_state;
    int m_half_moves;
    Piece oob = OutOfBounds;
    
    Square m_white_king;
    Square m_black_king;

    int get_row(const Square& s);
    int get_col(const Square& s);
    int to_index(int row, int col);

    Square to_square(int row, int col);

    void get_moves_for_pawn(const Square& from, Squares& squares);
    void get_moves_for_bishop(const Square& from, Squares& squares);
    void get_moves_for_knight(const Square& from, Squares& squares);
    void get_moves_for_rook(const Square& from, Squares& squares);
    void get_moves_for_queen(const Square& from, Squares& squares);
    void get_moves_for_king(const Square& from, Squares& squares);

    void get_moves_for_dir(const Square& from, int r_dir, int c_dir, Squares& squares);
};

}}
