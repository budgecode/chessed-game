#pragma once

#include <iostream>

#include <catch2/catch.hpp>

#include "../include/common.h"
#include "../include/game.h"

using namespace chessed::chess;

/**
 * Test that game starts with correct state
 * Test that white goes first
 * 
 * Start testing moves
 **/

TEST_CASE("It is white's turn first", "[game]") {
    Game game;
    game.reset();

    REQUIRE((game.get_turn() % 2) == 1);
}

TEST_CASE("It is black's turn after white's", "[game]") {
    Game game;
    game.reset();

    game.move({1, 2}, {2, 2});

    REQUIRE((game.get_turn() % 2) == 0);
}

TEST_CASE("It goes back to white's turn after black's", "[game]") {
    Game game;
    game.reset();

    game.move({1, 1}, {3, 1});
    game.move({6, 2}, {4, 2});

    REQUIRE((game.get_turn() % 2) == 1);
}

TEST_CASE("Pawns move correctly", "[game]") {

    Game game;

    SECTION("White pawn can move 2 forward from starting location") {
        game.reset();

        bool legal = game.move({1, 3}, {3, 3});
        REQUIRE(legal);
    }

    SECTION("White pawn can move 1 forward") {
        game.reset();

        bool legal = game.move({1, 2}, {2, 2});
        REQUIRE(legal);
    }

    SECTION("White pawn can capture diagonally right", "[game]") {
        game.reset();

        game.move({1, 1}, {3, 1});
        game.move({6, 2}, {4, 2});

        bool legal = game.move({3, 1}, {4, 2});
        REQUIRE(legal);
    }

    SECTION("White pawn can capture diagonally left", "[game]") {
        game.reset();

        game.move({1, 1}, {3, 1});
        game.move({6, 0}, {4, 0});

        bool legal = game.move({3, 1}, {4, 0});
        REQUIRE(legal);
    }

    SECTION("Black pawn can move 2 forward from starting location") {
        game.reset();

        game.move({1, 3}, {3, 3}); // White makes a move

        bool legal = game.move({6, 2}, {4, 2});
        REQUIRE(legal);
    }

    SECTION("Black pawn can move 1 forward") {
        game.reset();

        game.move({1, 3}, {3, 3}); // White makes a move

        bool legal = game.move({6, 0}, {5, 0});
        REQUIRE(legal);
    }

    SECTION("Black pawn can capture diagonally left", "[game]") {
        game.reset();

        game.move({1, 1}, {3, 1});
        game.move({6, 2}, {4, 2});
        game.move({1, 6}, {3, 6}); // Random move.

        bool legal = game.move({4, 2}, {3, 1});
        REQUIRE(legal);
    }

    SECTION("Black pawn can capture diagonally right", "[game]") {
        game.reset();

        game.move({1, 1}, {3, 1});
        game.move({6, 0}, {4, 0});
        game.move({1, 6}, {3, 6}); // Random move.

        bool legal = game.move({4, 0}, {3, 1});
        REQUIRE(legal);
    }

}

TEST_CASE("Bishops move correctly", "[game]") {
    Game game;

    SECTION("Bishops can move diagonally", "[game]") {
        game.reset();
        
        // Move pawns out from blocking bishops.
        game.move({3, 1}, {3, 3});
        game.move({4, 1}, {4, 3});
        game.move({3, 1}, {3, 3});
        game.move({4, 1}, {4, 3});

        // Bd2
        bool legal = game.move({2, 0}, {3, 1});
        REQUIRE(legal);

        // Bc4
        legal = game.move({5, 0}, {2, 3});
        REQUIRE(legal);
    }
}