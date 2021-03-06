#include <iostream>
#include <cassert>
#include "../include/game.h"

namespace chessed { namespace chess {
    Game::Game() : m_half_moves(0) {
        m_state[0] = WhiteRook;
        m_state[1] = WhiteKnight;
        m_state[2] = WhiteBishop;
        m_state[3] = WhiteQueen;
        m_state[4] = WhiteKing;
        m_state[5] = WhiteBishop;
        m_state[6] = WhiteKnight;
        m_state[7] = WhiteRook;

        m_state[8] = WhitePawn;
        m_state[9] = WhitePawn;
        m_state[10] = WhitePawn;
        m_state[11] = WhitePawn;
        m_state[12] = WhitePawn;
        m_state[13] = WhitePawn;
        m_state[14] = WhitePawn;
        m_state[15] = WhitePawn;

        for (int i = 16; i < 48; i++)
        {
            m_state[i] = Empty;
        }

        m_state[48] = BlackPawn;
        m_state[49] = BlackPawn;
        m_state[50] = BlackPawn;
        m_state[51] = BlackPawn;
        m_state[52] = BlackPawn;
        m_state[53] = BlackPawn;
        m_state[54] = BlackPawn;
        m_state[55] = BlackPawn;

        m_state[56] = BlackRook;
        m_state[57] = BlackKnight;
        m_state[58] = BlackBishop;
        m_state[59] = BlackQueen;
        m_state[60] = BlackKing;
        m_state[61] = BlackBishop;
        m_state[62] = BlackKnight;
        m_state[63] = BlackRook;

        m_white_king = "e1";
        m_black_king = "e8";
    };

    Piece& Game::operator[](int i)
    {
        if (i > 63 || i < 0)
            return oob;
        return m_state[i];
    }

    Piece& Game::operator[](const Square& s)
    {
        int col = s[0] - 'a';
        int row = s[1] - '1';
        int i = row * 8 + col;
        if (row < 0 || row > 7 ||
            col < 0 || col > 7)
            return oob;

        return m_state[i];
    }

    Piece& Game::operator()(int row, int col)
    {
        if (row < 0 || row > 7 ||
            col < 0 || col > 7)
            return oob;

        int i = row * 8 + col;
        return m_state[i];
    }

    int Game::get_half_moves()
    {
        return m_half_moves;
    }

    int Game::get_move_num()
    {
        return m_half_moves / 2 + 1;
    }

    Color Game::get_turn()
    {
        return m_half_moves % 2 == 0 ? White : Black;
    }

    bool Game::move(const Square& from, const Square& to, Move& info)
    {
        if (get_color((*this)[from]) != get_turn())
            return false;

        Squares possible_moves;
        get_possible_moves(from, possible_moves);
        if (possible_moves.find(to) == possible_moves.end())
            return false;

        if ((*this)[from] == WhiteKing)
        {
            m_white_king = to;
        }
        else if ((*this)[from] == BlackKing)
        {
            m_black_king = to;
        }

        info.to = to;
        info.from = from;
        info.captured = (*this)[to];
        info.is_check = false;
        info.is_mate = false;
        info.is_promoting = false;

        (*this)[to] = (*this)[from];
        (*this)[from] = Empty;

        m_half_moves++;

        return true;
    }

    void Game::get_possible_moves(const Square& from, Squares& squares)
    {
        if ((*this)[from] == WhitePawn ||
            (*this)[from] == BlackPawn)
        {
            get_moves_for_pawn(from, squares);
        }
        else if ((*this)[from] == WhiteBishop ||
                 (*this)[from] == BlackBishop)
        {
            get_moves_for_bishop(from, squares);
        }
        else if ((*this)[from] == WhiteRook ||
                 (*this)[from] == BlackRook)
        {
            get_moves_for_rook(from, squares);
        }
        else if ((*this)[from] == WhiteQueen ||
                 (*this)[from] == BlackQueen)
        {
            get_moves_for_queen(from, squares);
        }
        else if ((*this)[from] == WhiteKing ||
                 (*this)[from] == BlackKing)
        {
            get_moves_for_king(from, squares);
        }
        else if ((*this)[from] == WhiteKnight ||
                 (*this)[from] == BlackKnight)
        {
            get_moves_for_knight(from, squares);
        }
    }

    const GameState& Game::get_game_state()
    {
        return m_state;
    }

    bool Game::is_check()
    {
        // @to-do: implement after implementing get all moves
        // Color turn = get_turn();
        // if (turn == White)
        // {   
        // }
        // else if (turn == Black)
        // {
        // }

        return false;
    }

    // Private methods
    int Game::get_row(const Square& s)
    {
        return s[1] - '1';
    }

    int Game::get_col(const Square& s)
    {
        return s[0] - 'a';
    }

    int Game::to_index(int row, int col)
    {
        return row * 8 + col;
    }

    Square Game::to_square(int row, int col)
    {
        Square s = "";
        s += 'a' + col;
        s += '1' + row;
        return s;
    }

    void Game::get_moves_for_pawn(const Square& from, Squares& squares)
    {
        /**
         * @to-do:
         * 1. Add support for en-passant.
         * 2. Add support for promotion.
         */
        int row = get_row(from);
        int col = get_col(from);
        
        Color c = get_color((*this)[from]);
        assert(c != None); // This should not happen.
        
        int direction = 1;
        if (c == Black)
        {
            direction = -1;
        }

        if ((*this)(row + direction, col) == Empty)
            squares.insert(to_square(row + direction, col));
    
        if ((c == 0 && row == 1 && (*this)(row + direction * 2, col) == Empty) ||
            (c == 1 && row == 6 && (*this)(row + direction * 2, col) == Empty))
            squares.insert(to_square(row + direction * 2, col));

        Piece& right_diagonal = (*this)(row + direction, col + 1);
        Piece& left_diagonal = (*this)(row + direction, col - 1);

        if (!empty_or_oob(left_diagonal) && get_color(left_diagonal) != c)
            squares.insert(to_square(row + direction, col - 1));

        if (!empty_or_oob(right_diagonal) && get_color(right_diagonal) != c)
            squares.insert(to_square(row + direction, col + 1));

    }

    void Game::get_moves_for_bishop(const Square& from, Squares& squares)
    {
        int r_dir = -1;
        int c_dir = -1;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = 1;
        c_dir = -1;
        get_moves_for_dir(from, r_dir, c_dir, squares);


        r_dir = -1;
        c_dir = 1;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = 1;
        c_dir = 1;
        get_moves_for_dir(from, r_dir, c_dir, squares);
    }

    void Game::get_moves_for_rook(const Square& from, Squares& squares)
    {
        int r_dir = -1;
        int c_dir = 0;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = 1;
        c_dir = 0;
        get_moves_for_dir(from, r_dir, c_dir, squares);


        r_dir = 0;
        c_dir = -1;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = 0;
        c_dir = 1;
        get_moves_for_dir(from, r_dir, c_dir, squares);
    }

    void Game::get_moves_for_queen(const Square& from, Squares& squares)
    {
        int r_dir = -1;
        int c_dir = 0;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = 1;
        c_dir = 0;
        get_moves_for_dir(from, r_dir, c_dir, squares);


        r_dir = 0;
        c_dir = -1;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = 0;
        c_dir = 1;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = -1;
        c_dir = -1;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = 1;
        c_dir = -1;
        get_moves_for_dir(from, r_dir, c_dir, squares);


        r_dir = -1;
        c_dir = 1;
        get_moves_for_dir(from, r_dir, c_dir, squares);

        r_dir = 1;
        c_dir = 1;
        get_moves_for_dir(from, r_dir, c_dir, squares);
    }

    void Game::get_moves_for_king(const Square& from, Squares& squares)
    {
        int row = get_row(from);
        int col = get_col(from);
        Color c = get_color((*this)[from]);
        
        Piece curr = Empty;
        if ((curr = (*this)(row + 0, col + 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 0, col + 1));
        }
        
        if ((curr = (*this)(row + 1, col + 0)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 1, col + 0));
        }

        if ((curr = (*this)(row + 1, col + 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 1, col + 1));
        }
        
        if ((curr = (*this)(row - 1 , col + 0)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row - 1, col + 0));
        }

        if ((curr = (*this)(row + 0, col - 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 0, col - 1));
        }

        if ((curr = (*this)(row - 1, col - 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row - 1, col - 1));
        }

        if ((curr = (*this)(row + 1, col - 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 1, col - 1));
        }

        if ((curr = (*this)(row - 1, col + 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row - 1, col + 1));
        }
    }

    void Game::get_moves_for_knight(const Square& from, Squares& squares)
    {
        int row = get_row(from);
        int col = get_col(from);
        Color c = get_color((*this)[from]);
        
        Piece curr = Empty;
        if ((curr = (*this)(row + 1, col + 2)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 1, col + 2));
        }
        
        if ((curr = (*this)(row + 2, col + 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 2, col + 1));
        }

        if ((curr = (*this)(row - 1, col + 2)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row - 1, col + 2));
        }
        
        if ((curr = (*this)(row + 2, col - 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 2, col - 1));
        }

        if ((curr = (*this)(row - 2, col + 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row - 2, col + 1));
        }

        if ((curr = (*this)(row + 1, col - 2)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row + 1, col - 2));
        }

        if ((curr = (*this)(row - 1, col - 2)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row - 1, col - 2));
        }

        if ((curr = (*this)(row - 2, col - 1)) == Empty ||
            get_color(curr) != c)
        {
            squares.insert(to_square(row - 2, col - 1));
        }
    }

    void Game::get_moves_for_dir(const Square& from, int r_dir, int c_dir, Squares& squares)
    {
        int row = get_row(from);
        int col = get_col(from);
        Color c = get_color((*this)[from]);

        int i = 1;
        Piece curr = Empty;
        while ((curr = (*this)(row + i * r_dir, col + i * c_dir)) == Empty)
        {
            squares.insert(to_square(row + i * r_dir, col + i * c_dir));
            i++;
        }

        if (curr != OutOfBounds && get_color(curr) != c)
            squares.insert(to_square(row + i * r_dir, col + i * c_dir));
    }

}}
