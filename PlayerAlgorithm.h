//
// Created by loten on 23/04/2018.
//

#ifndef ADVANCEDTOPICS2_PLAYERALGORITHM_H
#define ADVANCEDTOPICS2_PLAYERALGORITHM_H

#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include "Board.h"
#include "PiecePosition.h"
#include "Move.h"
#include "FightInfo.h"
#include "Parser.h"

#define INVALID_COORD (-1)
#define INVALID_CHAR '\0'


class PlayerAlgorithm {
public:
    virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)=0;
    virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights)=0;
    virtual void notifyOnOpponentMove(const Move& move)=0; // called only on opponent’s move
    virtual void notifyFightResult(const FightInfo& fightInfo)=0; // called only if there was a fight
    virtual unique_ptr<Move> getMove()=0;
    virtual unique_ptr<JokerChange> getJokerChange()=0; // nullptr if no change is requested

};

class FilePlayerAlgorithm: public PlayerAlgorithm{
private:
    vector<unique_ptr<Move>> moves;
    vector<unique_ptr<JokerChange>> jokerChanges;
    playerEnum player;
    int currentMove;
    int currentJokerChange;


public:
    FilePlayerAlgorithm():player(NO_PLAYER), currentMove(0), currentJokerChange(0){}

    unique_ptr<Move> getMove() override {
        //no more moves
        if(currentMove == moves.size()){
            return make_unique<MoveImp>(INVALID_COORD,INVALID_COORD,INVALID_COORD,INVALID_COORD);
        }
        //moves file was not parsed yet
        if(currentMove==0)
            this->getMoves();
        return move(moves[currentMove++]);
    }

    unique_ptr<JokerChange> getJokerChange() override  {
        if(currentMove == moves.size()){
            return make_unique<JokerChangeImp>(INVALID_COORD,INVALID_COORD,INVALID_CHAR);
        }
        return move(jokerChanges[currentJokerChange++]);
    }

    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;

    void getMoves();

    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override {};

    void notifyOnOpponentMove(const Move& move) override {}; // called only on opponent’s move

    void notifyFightResult(const FightInfo& fightInfo) override {}; // called only if there was a fight
};


#endif //ADVANCEDTOPICS2_PLAYERALGORITHM_H
