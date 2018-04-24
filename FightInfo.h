//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_FIGHTINFO_H
#define ADVANCEDTOPICS2_FIGHTINFO_H

#include "Board.h"

class FightInfo {
    virtual const Point& getPosition() const;
    virtual char getOpponentPiece() const; // R, P, S, B or F (but NOT J)
    virtual int getWinner() const; // 0 - both lost, 1 - player 1 won, 2 - player 2 won
};


#endif //ADVANCEDTOPICS2_FIGHTINFO_H
