
#ifndef ADVANCEDTOPICS2_PARSER_H
#define ADVANCEDTOPICS2_PARSER_H

#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include "PiecePosition.h"
#include "Game.h"
#include "PlayerAlgorithm.h"
#define INVALID_POINT 0
#define INVALID_SYMBOL 0

using namespace std;

class Parser {
public:
	Parser()= default;
	Parser(const Parser&)= delete;
	Parser& operator=(const Parser&)= delete;

    unique_ptr<PiecePosition> parsePiecePosition(string commandLine);
	commandType parseMoveCommand(string commandLine, vector<Move>& moves, vector<JokerChange>& jokerChanges);

};


#endif //ADVANCEDTOPICS2_PARSER_H
