#include <iostream>

#include "../include/game.h"

namespace chessed { namespace chess {

void Game::reset()
{
    m_turn = 1;
    m_state.reset();
}

std::vector<Square> Game::get_possible_moves(Square from)
{

    Piece piece = m_state.get(from);

    std::vector<Square> possible_moves;
    switch (piece)
    {
        case WhitePawn:
            possible_moves.push_back({from.row + 1, from.col});
            
            if (from.row == 1)
            {
                possible_moves.push_back({from.row + 2, from.col});
            }

            if (m_state.get(from.row + 1, from.col - 1) != Empty &&
                m_state.get(from.row + 1, from.col - 1) != OutOfBounds) {
                possible_moves.push_back({from.row + 1, from.col - 1});
            }

            if (m_state.get(from.row + 1, from.col + 1) != Empty &&
                m_state.get(from.row + 1, from.col + 1) != OutOfBounds) {
                possible_moves.push_back({from.row + 1, from.col + 1});
            }

            break;
        case BlackPawn:
            possible_moves.push_back({from.row - 1, from.col});

            if (from.row == 6)
            {
                possible_moves.push_back({from.row - 2, from.col});
            }

            if (m_state.get(from.row - 1, from.col - 1) != Empty &&
                m_state.get(from.row - 1, from.col - 1) != OutOfBounds) {
                possible_moves.push_back({from.row - 1, from.col - 1});
            }

            if (m_state.get(from.row - 1, from.col + 1) != Empty &&
                m_state.get(from.row - 1, from.col + 1) != OutOfBounds) {
                possible_moves.push_back({from.row - 1, from.col + 1});
            }
            
            break;
        case WhiteRook:
        case BlackRook:
        {
            std::vector<Square> directions;
            directions.push_back({1, 0});
            directions.push_back({-1, 0});
            directions.push_back({0, 1});
            directions.push_back({0, -1});

            for (const Square& direction : directions)
            {
                int vertical_distance = 1;
                int horizontal_distance = 1;

                Square to = {from.row + (direction.row * vertical_distance),
                             from.col + (direction.col * horizontal_distance)};

                while (m_state.check_move(from, to))
                {
                    possible_moves.push_back(to);

                    vertical_distance++;
                    horizontal_distance++;
                    to = {from.row + (direction.row * vertical_distance),
                          from.col + (direction.col * horizontal_distance)};
                }
            }

            break;
        }
        case WhiteBishop:
        case BlackBishop:
        {
            std::vector<Square> directions;
            directions.push_back({1, 1});
            directions.push_back({-1, -1});
            directions.push_back({-1, 1});
            directions.push_back({1, -1});

            for (const Square& direction : directions)
            {
                int vertical_distance = 1;
                int horizontal_distance = 1;

                Square to = {from.row + (direction.row * vertical_distance),
                             from.col + (direction.col * horizontal_distance)};

                while (m_state.check_move(from, to))
                {
                    possible_moves.push_back(to);

                    vertical_distance++;
                    horizontal_distance++;
                    to = {from.row + (direction.row * vertical_distance),
                          from.col + (direction.col * horizontal_distance)};
                }
            }

            break;
        }
        case WhiteKnight:
        case BlackKnight:
            break;
        case WhiteKing:
        case BlackKing:
            break;
        case WhiteQueen:
        case BlackQueen:
        {
            std::vector<Square> directions;
            directions.push_back({1, 1});
            directions.push_back({-1, -1});
            directions.push_back({-1, 1});
            directions.push_back({1, -1});
            directions.push_back({1, 0});
            directions.push_back({-1, 0});
            directions.push_back({0, 1});
            directions.push_back({0, -1});

            for (const Square& direction : directions)
            {
                int vertical_distance = 1;
                int horizontal_distance = 1;

                Square to = {from.row + (direction.row * vertical_distance),
                             from.col + (direction.col * horizontal_distance)};

                while (m_state.check_move(from, to))
                {
                    possible_moves.push_back(to);

                    vertical_distance++;
                    horizontal_distance++;
                    to = {from.row + (direction.row * vertical_distance),
                          from.col + (direction.col * horizontal_distance)};
                }
            }

            break;
        }
        case Empty:
        case OutOfBounds:
        default:
            break;
    }

    return possible_moves;
}

bool Game::move(Square from_index, Square to_index)
{
    Piece piece = m_state.get(from_index);

    // Check if it was this players turn.
    if ((m_turn % 2 == 1 && is_white(piece) == 0) || 
        (m_turn % 2 == 0 && is_white(piece) == 1))
    {
        return false;
    }
    
    std::vector<Square> possible_moves = get_possible_moves(from_index);

    bool legal = false;
    for (Square possible_move : possible_moves)
    {
        if (possible_move.row == to_index.row &&
            possible_move.col == to_index.col)
        {
                legal = true;
        }
    }

    // Actually persist the move
    if (legal)
    {
        m_state.move(from_index, to_index);
        m_turn++;
    }

    return legal;
}

int Game::get_turn()
{
    return m_turn;
}
  
}}
