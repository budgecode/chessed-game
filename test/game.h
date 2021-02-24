#pragma once

#include <iostream>

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

TEST_CASE("Ensure players take turns and moves are counted", "[game")
{
    Game game;
    Move info;
    bool valid = game.move("a2", "a3", info);
    REQUIRE(valid);
    REQUIRE(info.captured == Empty);
    REQUIRE(info.to == "a3");
    REQUIRE(info.from == "a2");
    REQUIRE(game.half_moves() == 1);
    REQUIRE(game.move_num() == 1);

    valid = game.move("h7", "h6", info);
    REQUIRE(valid);
    REQUIRE(info.captured == Empty);
    REQUIRE(info.to == "h6");
    REQUIRE(info.from == "h7");
    REQUIRE(game.half_moves() == 2);
    REQUIRE(game.move_num() == 2);

    valid = game.move("a3", "a4", info);
    REQUIRE(valid);
    REQUIRE(info.captured == Empty);
    REQUIRE(info.to == "a4");
    REQUIRE(info.from == "a3");
    REQUIRE(game.half_moves() == 3);
    REQUIRE(game.move_num() == 2);
}
