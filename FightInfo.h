//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_FIGHTINFO_H
#define ADVANCEDTOPICS2_FIGHTINFO_H

#include "Board.h"

class FightInfo {
public:
    virtual const Point& getPosition() const;
    virtual char getOpponentPiece() const; // R, P, S, B or F (but NOT J)
    virtual int getWinner() const; // 0 - both lost, 1 - player 1 won, 2 - player 2 won
};

class FightInfoImp: public FightInfo{
private:
    unique_ptr<Point> position;
    char opponentPiece;
    int winner;

public:
    FightInfoImp():position(nullptr){};
    const Point& getPosition() const override;
    char getOpponentPiece() const override ; // R, P, S, B or F (but NOT J)
    int getWinner() const override ;
};


#endif //ADVANCEDTOPICS2_FIGHTINFO_H
