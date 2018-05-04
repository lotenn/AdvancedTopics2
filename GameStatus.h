//
// Created by Saar on 04/05/2018.
//

#ifndef ADVANCEDTOPICS2_GAMESTATUS_H
#define ADVANCEDTOPICS2_GAMESTATUS_H


//************************Player Enum ****************************************************
enum playerEnum {
    PLAYER_1 = 1,
    PLAYER_2 = 2,
    NO_PLAYER = 0
};

//************************End Game Reason Enum ****************************************************
enum endGameReason{
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

class GameStatus {
private:
    bool gameOn;
    endGameReason mainReason;
    endGameReason reason1;
    endGameReason reason2;
    playerEnum winner;
    playerEnum loser;
    int errorLine1;
    int errorLine2;

public:
    GameStatus(): gameOn(true){}
    bool isGameOn() const {
        return gameOn;
    }

    void setGameOn(bool gameOn) {
        GameStatus::gameOn = gameOn;
    }

    endGameReason getMainReason() const {
        return mainReason;
    }

    void setMainReason(endGameReason mainReason) {
        GameStatus::mainReason = mainReason;
    }

    endGameReason getReason1() const {
        return reason1;
    }

    void setReason1(endGameReason reason1) {
        GameStatus::reason1 = reason1;
    }

    endGameReason getReason2() const {
        return reason2;
    }

    void setReason2(endGameReason reason2) {
        GameStatus::reason2 = reason2;
    }

    playerEnum getWinner() const {
        return winner;
    }

    void setWinner(playerEnum winner) {
        GameStatus::winner = winner;
    }

    playerEnum getLoser() const {
        return loser;
    }

    void setLoser(playerEnum loser) {
        GameStatus::loser = loser;
    }

    int getErrorLine1() const {
        return errorLine1;
    }

    void setErrorLine1(int errorLine1) {
        GameStatus::errorLine1 = errorLine1;
    }

    int getErrorLine2() const {
        return errorLine2;
    }

    void setErrorLine2(int errorLine2) {
        GameStatus::errorLine2 = errorLine2;
    }
};


#endif //ADVANCEDTOPICS2_GAMESTATUS_H
