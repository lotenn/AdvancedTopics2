#ifndef EX1_FILES_H
#define EX1_FILES_H

#include "Game.h"
#include "Parser.h"
#include <iostream>
#include <fstream>


void validatePositioningFile(const char                         *filePath,
                             vector<unique_ptr<PiecePosition>>&  piecePositions,
                             GameStatus&                         gameStatus);

void parsingMoveFile(const char                      *filePath,
                     vector<unique_ptr<Move>>&        moves,
                     vector<unique_ptr<JokerChange>>& jokerChanges,
                     GameStatus&                      gameStatus);

void generateOutputFile(const char *outputFilePath, string winner, string reason, string board);

#endif //EX1_FILES_H
