#ifndef ADVANCEDTOPICS2_GAME_H
#define ADVANCEDTOPICS2_GAME_H

#include "Move.h"
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include "Piece.h"
using namespace std;

#define NUM_OF_R 2
#define NUM_OF_P 5
#define NUM_OF_S 1
#define NUM_OF_B 2
#define NUM_OF_J 2
#define NUM_OF_F 1
#define NUM_OF_TOOLS (NUM_OF_B + NUM_OF_F + NUM_OF_J + NUM_OF_P + NUM_OF_R + NUM_OF_S)

//************************Game messages ****************************************************
enum executeCommandMessage{
	EXECUTE_COMMAND_SUCCESS,
	EXECUTE_COMMAND_NOT_YOUR_TOOL,
	EXECUTE_COMMAND_TOOL_CANT_MOVE,
	EXECUTE_COMMAND_CELL_OCCUPIED,
	EXECUTE_COMMAND_NOT_JOKER,
	EXECUTE_COMMAND_INVALID
};

enum endGameReason{
	NO_WINNER,
	NO_MORE_FLAGS,
	NO_MOVING_TOOLS,
	NO_POSITIONING_FILE,
	BAD_POSITIONING_FILE_INVALID,
	BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS,
	BAD_POSITIONING_FILE_TOO_MANY_TOOLS,
	BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION,
	NO_MOVE_FILE,
	BAD_MOVE_FILE_NOT_YOUR_TOOL,
	BAD_MOVE_FILE_TOOL_CANT_MOVE,
	BAD_MOVE_FILE_CELL_OCCUPIED,
	BAD_MOVE_FILE_NOT_JOKER,
	BAD_MOVE_FILE_INVALID,
	DRAW_NO_MORE_MOVES,
	DRAW_NO_MOVING_TOOLS,
	DRAW_POSITIONING_ENDED_WITH_NO_FLAGS,
	DRAW_POSITIONING_ENDED_WITH_NO_MOVING_TOOLS, //todo: check if need to change output file message in this case
	DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS
};

endGameReason toReason(executeCommandMessage msg);

string getBadInputFileMessage(endGameReason reason);

struct endGameMessage{
	endGameReason mainReason;
	endGameReason reason1;
	endGameReason reason2;
	playerEnum winner;
	int errorLine1;
	int errorLine2;
};

endGameMessage createEndGameMessage(endGameReason mainReason, endGameReason reason1, endGameReason reason2, playerEnum winner, int _errorLine1, int _errorLine2);

endGameMessage createEndGameMessage(endGameReason reason, playerEnum winner, int _errorLine1, int _errorLine2);

endGameMessage createEndGameMessage(endGameReason reason, playerEnum winner);

string getReasonString(endGameMessage);

//************************Game Class ****************************************************
class Game {

public:
	Game();
	~Game();
	/*
	 * Set @arg(player) tools according to @arg(commands)
	 */
	void setPlayerTools(const vector<PositioningCommand> &commands, playerEnum player);
	/*
	 * Removes all tools from game board
	 */
	void resetGameBoard();
	playerEnum getCurrentPlayer(){return this->currentPlayer;}
	void setCurrentPlayer(playerEnum player);
	/*
	 * @ret: the winner of the battle source vs. target
	 */
	Piece* battleWinner(Piece *source, Piece *target);
	executeCommandMessage executeCommand(Command cmd);
	executeCommandMessage executeJoker(Command cmd);
	executeCommandMessage executeMove(Command cmd);
	endGameReason playerHasLost(vector<Piece*> playerTools);
	endGameMessage checkGameWinner();
	void raisePlayerScore(int score, playerEnum player);
	string boardToString();
};

#endif //ADVANCEDTOPICS2_GAME_H
