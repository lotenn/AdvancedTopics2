//
// Created by Saar on 04/05/2018.
//

#ifndef ADVANCEDTOPICS2_GAMESTATUS_H
#define ADVANCEDTOPICS2_GAMESTATUS_H

#include "EnumUtils.h"


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

    void setGameOn(){
        GameStatus::gameOn = true;
    }

    void setGameOff() {
        GameStatus::gameOn = false;
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

    void reset();
};


#endif //ADVANCEDTOPICS2_GAMESTATUS_H
