cmake_minimum_required(VERSION 3.10)
project(AdvancedTopics2)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG")

add_executable(AdvancedTopics2 main.cpp Board.cpp Point.h FightInfo.cpp JokerChange.cpp Piece.cpp Piece.h Parser.cpp PlayerAlgorithm.cpp PlayerAlgorithm.h GameManager.cpp GameManager.h GameStatus.cpp GameStatus.h EnumUtils.cpp EnumUtils.h PiecePosition.h Move.h)