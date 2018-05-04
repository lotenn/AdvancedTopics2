//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_FIGHTINFO_H
#define ADVANCEDTOPICS2_FIGHTINFO_H

#include "Board.h"

class FightInfo {
public:
    virtual const Point& getPosition() const=0;
    virtual char getOpponentPiece() const=0; // R, P, S, B or F (but NOT J)
    virtual int getWinner() const=0; // 0 - both lost, 1 - player 1 won, 2 - player 2 won
};

class FightInfoImp: public FightInfo{
private:
    unique_ptr<Point> position;
    char opponentPiece;
    int winner;

public:
    FightInfoImp():position(nullptr), opponentPiece('\0'), winner(0){};

    const Point& getPosition() const override{
        return *position;
    }

    void setPosition(int x, int y){
        position = make_unique<PointImp>(x,y);
    }

    char getOpponentPiece() const override{
        return opponentPiece;
    }

    void setOpponentPiece(char _opponentPiece){
        opponentPiece = _opponentPiece;
    }

    int getWinner() const override{
        return winner;
    }

    void setWinner (int _winner){
        winner = _winner;
    }
};


#endif //ADVANCEDTOPICS2_FIGHTINFO_H
