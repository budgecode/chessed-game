CMAKE_POLICY(SET CMP0048 NEW)
PROJECT(ChessedGame LANGUAGES CXX VERSION "0.0.0")
set(CMAKE_CXX_STANDARD 20)

CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)

ADD_LIBRARY(ChessedGame
    include/state.h
    include/game.h
    include/common.h
    src/state.cpp
    src/game.cpp
)

ADD_SUBDIRECTORY(test)