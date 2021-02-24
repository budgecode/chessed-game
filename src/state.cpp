#include "../include/state.h"

namespace chessed { namespace chess {

    bool State::move(int from_row, int from_col, int to_row, int to_col)
    {
        if (!check_move(from_row, from_col, to_row, to_col))
            return false;
        
        int from_index = to_1d(from_row, from_col);
        int to_index = to_1d(to_row, to_col);

        m_state[to_index] = m_state[from_index];
        m_state[from_index] = Empty;
        
        m_move_stack.push_back({from_index, to_index});

        return true;
    }

    bool State::move(Square from, Square to)
    {
        return move(from.row, from.col, to.row, to.col);
    }

    bool State::check_move(int from_row, int from_col, int to_row, int to_col)
    {
        if (from_row < 0 || from_row > 7 ||
            from_col < 0 || from_col > 7 ||
            to_row < 0 || to_row > 7 ||
            to_col < 0 || to_col > 7)
        {
            return false;
        }

        int from_index = to_1d(from_row, from_col);
        int to_index = to_1d(to_row, to_col);
        
        if (is_white(m_state[from_index]) == is_white(m_state[to_index]))
            return false;

        return true;
    }

    bool State::check_move(Square from, Square to)
    {
        return check_move(from.row, from.col, to.row, to.col);
    }

    Piece State::get(int row, int col)
    {
        if (row < 0 || row > 7 ||
            col < 0 || col > 7)
        {
            return OutOfBounds;
        }

        return m_state[to_1d(row, col)];
    }

    Piece State::get(Square square)
    {
        return get(square.row, square.col);
    }

    void State::undo()
    {
        const Square&  last_move = m_move_stack.back();

        m_state[last_move.row] = m_state[last_move.col];
        m_state[last_move.col] = Empty;

        m_move_stack.pop_back();
    }
}}