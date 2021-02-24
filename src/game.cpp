#include <iostream>

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
    };

    Piece& Game::operator[](int i)
    {
        return m_state[i];
    }

    Piece& Game::operator[](const Square& s)
    {
        int row = 0;
        int col = 0;
        col = s[0] - 'a';
        row = s[1] - '1';
        int i = row * 8 + col;
        return m_state[i];
    }

    Piece& Game::operator()(int row, int col)
    {
        int i = row * 8 + col;
        return m_state[i];
    }

    int Game::half_moves()
    {
        return m_half_moves;
    }

    int Game::move_num()
    {
        return m_half_moves / 2;
    }

    int Game::turn()
    {
        return m_half_moves % 2; // 0 for white, 1 for black.
    }

    bool Game::move(const Square& from, const Square& to, Move& info)
    {
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
}}
