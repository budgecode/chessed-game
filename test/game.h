#pragma once

#include <catch2/catch.hpp>

#include "../include/game.h"

using namespace chessed::chess;

/**
 * Test that game starts with correct state
 * Test that white goes first
 * 
 * Start testing moves
 **/

TEST_CASE("Index operators work", "[game]")
{
    Game game;

    REQUIRE(game[0] == WhiteRook);
    REQUIRE(game["a1"] == WhiteRook);
    REQUIRE(game(0, 0) == WhiteRook);
    REQUIRE(game[63] == BlackRook);
    REQUIRE(game["h8"] == BlackRook);
    REQUIRE(game(7, 7) == BlackRook);
}

TEST_CASE("Ensure moves are counted correctly", "[game]")
{
    Game game;
    Move info;
    bool valid = game.move("a2", "a3", info);
    REQUIRE(valid);
    REQUIRE(game.get_half_moves() == 1);
    REQUIRE(game.get_move_num() == 1);

    valid = game.move("h7", "h6", info);
    REQUIRE(valid);
    REQUIRE(game.get_half_moves() == 2);
    REQUIRE(game.get_move_num() == 2);

    valid = game.move("a3", "a4", info);
    REQUIRE(valid);
    REQUIRE(game.get_half_moves() == 3);
    REQUIRE(game.get_move_num() == 2);
}

TEST_CASE("Ensure turn changes on each move", "[game]")
{
    Game game;
    
    REQUIRE(game.get_turn() == 0);

    Move info;
    bool valid = game.move("a2", "a3", info);
    REQUIRE(valid);
    REQUIRE(game.get_turn() == 1);
    
    valid = game.move("h7", "h6", info);
    REQUIRE(valid);
    REQUIRE(game.get_turn() == 0);
    
    valid = game.move("a3", "a4", info);
    REQUIRE(valid);
    REQUIRE(game.get_turn() == 1);
    
}

TEST_CASE("Ensure player can't move out of turn", "[game]")
{
    Game game;
    Move info;
    bool valid = game.move("a2", "a3", info);
    REQUIRE(valid);

    valid = game.move("a3", "a4", info);
    REQUIRE_FALSE(valid);
    
    valid = game.move("a3", "a4", info);
    REQUIRE_FALSE(valid);
    
}

TEST_CASE("Ensure pawns move correctly", "[game]")
{
    SECTION("pawn moves forward to empty spot")
    {
        Game game;
        Move info;
        bool valid = game.move("a2", "a3", info);
        REQUIRE(valid);

        valid = game.move("h7", "h6", info);
        REQUIRE(valid);
    }
    
    SECTION("pawn can move forward two spaces to empty spot from starting position")
    {
        Game game;
        Move info;
        bool valid = game.move("a2", "a4", info);
        REQUIRE(valid);

        valid = game.move("h7", "h5", info);
        REQUIRE(valid);
    }

    SECTION("pawns can capture")
    {
        Game game;
        Move info;
        bool valid = game.move("a2", "a4", info);
        REQUIRE(valid);

        valid = game.move("b7", "b5", info);
        REQUIRE(valid);

        valid = game.move("a4", "b5", info);
        REQUIRE(valid);
    }

}

TEST_CASE("Ensure bishops move correctly", "[game]")
{
    SECTION("bishops can't move through pieces")
    {
        Game game;
        Move info;
        bool valid = game.move("c1", "a3", info);
        REQUIRE_FALSE(valid);

        valid = game.move("c8", "a6", info);
        REQUIRE_FALSE(valid);

        valid = game.move("f1", "d3", info);
        REQUIRE_FALSE(valid);

        valid = game.move("c1", "d2", info);
        REQUIRE_FALSE(valid);

        valid = game.move("f1", "h3", info);
        REQUIRE_FALSE(valid);

        valid = game.move("f8", "e7", info);
        REQUIRE_FALSE(valid);

        valid = game.move("c8", "e6", info);
        REQUIRE_FALSE(valid);

        valid = game.move("f8", "g7", info);
        REQUIRE_FALSE(valid);
    }

    SECTION("bishops can move on diagonals")
    {
        Game game;
        Move info;
        
        bool valid = game.move("d2", "d4", info);
        REQUIRE(valid);
        
        valid = game.move("e7", "e5", info);
        REQUIRE(valid);

        valid = game.move("e2", "e4", info);
        REQUIRE(valid);

        valid = game.move("d7", "d5", info);
        REQUIRE(valid);

        valid = game.move("c1", "d2", info);
        REQUIRE(valid);

        valid = game.move("f8", "c5", info);
        REQUIRE(valid);
    }

    SECTION("bishops can capture on diagonals")
    {
        Game game;
        Move info;
        
        bool valid = game.move("d2", "d4", info);
        REQUIRE(valid);
        
        valid = game.move("e7", "e5", info);
        REQUIRE(valid);

        valid = game.move("e2", "e4", info);
        REQUIRE(valid);

        valid = game.move("d7", "d5", info);
        REQUIRE(valid);

        valid = game.move("c1", "g5", info);
        REQUIRE(valid);
        
        valid = game.move("f8", "c5", info);
        REQUIRE(valid);

        valid = game.move("g5", "d8", info);
        REQUIRE(valid);

        valid = game.move("c5", "d4", info);
        REQUIRE(valid);
    }

    SECTION("bishops can't make illegal moves")
    {
        Game game;
        Move info;
        
        bool valid = game.move("d2", "d4", info);
        REQUIRE(valid);
        
        valid = game.move("e7", "e5", info);
        REQUIRE(valid);

        valid = game.move("e2", "e4", info);
        REQUIRE(valid);

        valid = game.move("d7", "d5", info);
        REQUIRE(valid);

        valid = game.move("c1", "g5", info);
        REQUIRE(valid);
        
        valid = game.move("f8", "c5", info);
        REQUIRE(valid);

        valid = game.move("g5", "g6", info);
        REQUIRE_FALSE(valid);

        valid = game.move("c5", "e2", info);
        REQUIRE_FALSE(valid);
    }
}

TEST_CASE("Ensure rooks move correctly", "[game]")
{
    SECTION("rooks can't move through pieces")
    {
        Game game;
        Move info;
        bool valid = game.move("a1", "a3", info);
        REQUIRE_FALSE(valid);

        valid = game.move("a8", "a6", info);
        REQUIRE_FALSE(valid);

        valid = game.move("h1", "h3", info);
        REQUIRE_FALSE(valid);

        valid = game.move("h8", "h6", info);
        REQUIRE_FALSE(valid);
    }

    SECTION("rooks can move on rows and columns")
    {
        Game game;
        Move info;
        
        bool valid = game.move("a2", "a4", info);
        REQUIRE(valid);
        
        valid = game.move("a7", "a5", info);
        REQUIRE(valid);

        valid = game.move("h2", "h4", info);
        REQUIRE(valid);

        valid = game.move("h7", "h5", info);
        REQUIRE(valid);

        valid = game.move("a1", "a3", info);
        REQUIRE(valid);

        valid = game.move("a8", "a6", info);
        REQUIRE(valid);

        valid = game.move("h1", "h3", info);
        REQUIRE(valid);

        valid = game.move("h8", "h6", info);
        REQUIRE(valid);

        valid = game.move("a3", "b3", info);
        REQUIRE(valid);

        valid = game.move("a6", "c6", info);
        REQUIRE(valid);
        
        valid = game.move("h3", "g3", info);
        REQUIRE(valid);

        valid = game.move("h6", "f6", info);
        REQUIRE(valid);

    }

    SECTION("rooks can capture on rows and columns")
    {
        Game game;
        Move info;
        
        bool valid = game.move("a2", "a4", info);
        valid = game.move("a7", "a5", info);
        valid = game.move("h2", "h4", info);
        valid = game.move("h7", "h5", info);
        valid = game.move("a1", "a3", info);
        valid = game.move("a8", "a6", info);
        valid = game.move("h1", "h3", info);
        valid = game.move("h8", "h6", info);
        valid = game.move("a3", "c3", info);
        valid = game.move("a6", "c6", info);
        valid = game.move("h3", "f3", info);
        valid = game.move("h6", "f6", info);
        
        valid = game.move("f3", "f6", info);
        REQUIRE(valid);

        valid = game.move("c6", "c3", info);
        REQUIRE(valid);
    }
}

TEST_CASE("Ensure queens move correctly", "[game]")
{
    SECTION("queens can't move through pieces")
    {
        Game game;
        Move info;
        bool valid = game.move("d1", "d3", info);
        REQUIRE_FALSE(valid);

        valid = game.move("d8", "d6", info);
        REQUIRE_FALSE(valid);
    }

    SECTION("queens can move on rows and columns")
    {
        Game game;
        Move info;
        
        bool valid = game.move("d2", "d4", info);
        valid = game.move("d7", "d5", info);

        valid = game.move("d1", "d3", info);
        REQUIRE(valid);

        valid = game.move("d8", "d6", info);
        REQUIRE(valid);
        
        valid = game.move("d3", "h3", info);
        REQUIRE(valid);

        valid = game.move("d6", "h6", info);
        REQUIRE(valid);
    }

    SECTION("queens can capture on rows and columns")
    {
        Game game;
        Move info;
        
        bool valid = game.move("d2", "d4", info);
        valid = game.move("d7", "d5", info);
        valid = game.move("d1", "d3", info);
        valid = game.move("d8", "d6", info);
        valid = game.move("d3", "h3", info);
        valid = game.move("d6", "h6", info);

        valid = game.move("h3", "c8", info);
        REQUIRE(valid);

        valid = game.move("h6", "c1", info);
        REQUIRE(valid);

    }

    SECTION("queens can move on diagonals")
    {
        Game game;
        Move info;
        
        bool valid = game.move("c2", "c4", info);
        valid = game.move("c7", "c5", info);

        valid = game.move("d1", "a4", info);
        REQUIRE(valid);

        valid = game.move("d8", "a5", info);
        REQUIRE(valid);
    }

    SECTION("queens can capture on diagonals")
    {
        Game game;
        Move info;
        
        bool valid = game.move("c2", "c4", info);
        valid = game.move("c7", "c5", info);
        valid = game.move("d1", "a4", info);
        valid = game.move("d8", "a5", info);
        
        valid = game.move("a4", "d7", info);
        REQUIRE(valid);

        valid = game.move("a5", "d2", info);
        REQUIRE(valid);

    }

}

TEST_CASE("Ensure kings move correctly", "[game]")
{
    SECTION("kings can't move through pieces")
    {
        Game game;
        Move info;
        bool valid = game.move("e1", "e2", info);
        REQUIRE_FALSE(valid);

        valid = game.move("e8", "e7", info);
        REQUIRE_FALSE(valid);
    }

    SECTION("kings can move one space")
    {
        Game game;
        Move info;
        
        bool valid = game.move("e2", "e4", info);
        valid = game.move("e7", "e5", info);
        
        valid = game.move("e1", "e2", info);
        REQUIRE(valid);

        valid = game.move("e8", "e7", info);
        REQUIRE(valid);

        valid = game.move("e2", "f3", info);
        REQUIRE(valid);
        
        valid = game.move("e7", "f6", info);
        REQUIRE(valid);
        
        valid = game.move("f3", "e3", info);
        REQUIRE(valid);
        
        valid = game.move("f6", "g6", info);
        REQUIRE(valid);
    }

    SECTION("kings can capture space")
    {
        Game game;
        Move info;
        
        bool valid = game.move("e2", "e4", info);
        valid = game.move("e7", "e5", info);
        valid = game.move("d2", "d4", info);
        valid = game.move("d7", "d5", info);
        valid = game.move("c1", "g5", info);
        valid = game.move("c8", "g4", info);
        valid = game.move("g5", "e7", info);
        valid = game.move("g4", "e2", info);

        valid = game.move("e1", "e2", info);
        REQUIRE(valid);

        valid = game.move("e8", "e7", info);
        REQUIRE(valid);
    }
}

TEST_CASE("Ensure knights move correctly", "[game]")
{
    SECTION("knights can move and capture")
    {
        Game game;
        Move info;
        
        bool valid = game.move("b1", "c3", info);
        REQUIRE(valid);
        
        valid = game.move("g8", "f6", info);
        REQUIRE(valid);

        valid = game.move("g1", "f3", info);
        REQUIRE(valid);
        
        valid = game.move("b8", "c6", info);
        REQUIRE(valid);

        valid = game.move("c3", "e4", info);
        REQUIRE(valid);

        valid = game.move("c6", "e5", info);
        REQUIRE(valid);

        valid = game.move("f3", "e5", info);
        REQUIRE(valid);

        valid = game.move("f6", "e4", info);
        REQUIRE(valid);


    }
}