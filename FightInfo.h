//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_FIGHTINFO_H
#define ADVANCEDTOPICS2_FIGHTINFO_H

#include "Board.h"
#include "GameManager.h"

class FightInfo {
public:
    virtual const Point& getPosition() const=0;
    virtual char getPiece(int player) const = 0; // R, P, S, B or F (but NOT J)
    virtual int getWinner() const=0; // 0 - both lost, 1 - player 1 won, 2 - player 2 won
};

class FightInfoImp: public FightInfo{
private:
    unique_ptr<Point> position;
    char player1Piece;
    char player2Piece;
    playerEnum winner;

public:
    const Point& getPosition() const override{
        return *position;
    }

    void setPosition(int x, int y){
        position = make_unique<PointImp>(x,y);
    }

    virtual char getPiece(int player) const override{
        if(player == 1){return player1Piece;}
        return player2Piece;
    }

    void setPlayer1Piece(char piece){
        player1Piece = piece;
    }

    void setPlayer2Piece(char piece){
        player2Piece = piece;
    }

    int getWinner() const override{
        return playerEnumToInt(winner);
    }

    void setWinner (playerEnum _winner){
        winner = _winner;
    }
};


#endif //ADVANCEDTOPICS2_FIGHTINFO_H
