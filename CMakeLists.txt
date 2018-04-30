cmake_minimum_required(VERSION 3.10)
project(AdvancedTopics2)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG")

add_executable(AdvancedTopics2 main.cpp Point.cpp PiecePosition.cpp Board.cpp FightInfo.cpp Move.cpp JokerChange.cpp Piece.cpp Piece.h Game.cpp Parser.cpp MainAux.cpp Files.h Files.cpp PlayerAlgorithm.cpp PlayerAlgorithm.h GameManager.cpp GameManager.h)