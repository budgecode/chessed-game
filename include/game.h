#pragma once

#include "common.h"
#include "state.h"

#include <vector>

namespace chessed { namespace chess {

class Game {

public:
    void reset();
    bool move(Square from_index, Square to_index);
    std::vector<Square> get_possible_moves(Square from);
    int get_turn();
    
private:
    State m_state;
    int m_turn;

};

}}
