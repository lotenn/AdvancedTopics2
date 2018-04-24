//
// Created by loten on 23/04/2018.
//

#ifndef ADVANCEDTOPICS2_PLAYERALGORITHM_H
#define ADVANCEDTOPICS2_PLAYERALGORITHM_H

#include <vector>
#include <list>
#include "Board.h"
#include "PiecePosition.h"
#include "Move.h"
#include "FightInfo.h"
#include "Command.h"
#include "Parser.h"

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
    int currentMove;
    vector<MoveImp> moves;
    vector<JokerChangeImp> jokerChanges;

public:
    FilePlayerAlgorithm():currentMove(0){}
    unique_ptr<Move> getMove() override;
};


#endif //ADVANCEDTOPICS2_PLAYERALGORITHM_H
