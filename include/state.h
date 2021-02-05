#pragma once

#include "common.h"

#include <vector>

namespace chessed { namespace chess {

class State {

public:
    void reset();
    
    bool move(Square from, Square to);
    bool move(int from_row, int from_col, int to_row, int to_col);

    // Checks to see if a move is semantically valid
    // (doesn't capture own color, doesn't run off board, etc.).
    // Doesn't actually make the move.
    bool check_move(Square from, Square to);
    bool check_move(int from_row, int from_col, int to_row, int to_col);

    Piece get(Square square);
    Piece get(int row, int col);
    
    void undo();

private:
    BoardState m_state;
    std::vector<Square> m_move_stack; 

};

}}
