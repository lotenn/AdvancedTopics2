//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_FIGHTINFO_H
#define ADVANCEDTOPICS2_FIGHTINFO_H

#include <iostream>
#include "Board.h"

class FightInfo {
public:
//    virtual ~FightInfo(){};
    virtual const Point& getPosition() const=0;
    virtual char getPiece(int player) const = 0; // R, P, S, B or F (but NOT J)
    virtual int getWinner() const=0; // 0 - both lost, 1 - player 1 won, 2 - player 2 won
};

class FightInfoImp: public FightInfo{
private:
    //todo: returen to Point
    PointImp position;
    char player1Piece;
    char player2Piece;
    playerEnum winner;

public:
    FightInfoImp(): position(0,0), player1Piece('0'), player2Piece('0'), winner(NO_PLAYER) {};
    FightInfoImp(const Point& point, char _player1Piece, char _player2Piece, playerEnum _winner):
            position(point.getX(), point.getY()),
            player1Piece(_player1Piece),
            player2Piece(_player2Piece),
            winner(_winner){}

//    virtual ~FightInfoImp() override = default;

    const Point& getPosition() const override{
        return position;
    }

    void setPosition(int x, int y){
        position = PointImp(x,y);
    }

    char getPiece(int player) const override{
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
