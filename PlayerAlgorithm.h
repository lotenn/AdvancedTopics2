//
// Created by loten on 23/04/2018.
//

#ifndef ADVANCEDTOPICS2_PLAYERALGORITHM_H
#define ADVANCEDTOPICS2_PLAYERALGORITHM_H

#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include "Parser.h"

#define INVALID_COORD (-1)
#define INVALID_CHAR '\0'
#define PRIMARY 0
#define SECONDARY 1

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
        //moves file was not parsed yet
        if(currentMove==0)
            this->getMoves();
        if(currentMove == (int)moves.size()){
            return make_unique<MoveImp>(INVALID_COORD,INVALID_COORD,INVALID_COORD,INVALID_COORD);
        }
        return move(moves[currentMove++]);
    }

    unique_ptr<JokerChange> getJokerChange() override  {
        if(currentJokerChange == (int)jokerChanges.size()){
            return make_unique<JokerChangeImp>(INVALID_COORD,INVALID_COORD,INVALID_CHAR);
        }
        return move(jokerChanges[currentJokerChange++]);
    }

    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;

    void getMoves();

    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override {
        //nonsense - to use the unused parameter
        if(b.getPlayer(PointImp(1,1)) && fights.size()>0){
            return;
        }
    };

    void notifyOnOpponentMove(const Move& move) override {
        //nonsense - to use the unused parameter
        if(move.getTo().getX() >0){
            return;
        }
    }; // called only on opponent’s move

    void notifyFightResult(const FightInfo& fightInfo) override {
        //nonsense - to use the unused parameter
        if(fightInfo.getWinner()==NO_PLAYER){
            return;
        }
    }; // called only if there was a fight
};

class PossiblePieces {
private:
    playerEnum player;
    possiblePieceType possiblePiece;
    bool isMovable;
    bool isJoker;

public:

    bool isIsJoker() const {
        return isJoker;
    }

    void setIsJoker(bool isJoker) {
        PossiblePieces::isJoker = isJoker;
    }

    playerEnum getPlayer() const {
        return player;
    }

    void setPlayer(playerEnum player) {
        PossiblePieces::player = player;
    }

    possiblePieceType getPossiblePiece() const {
        return possiblePiece;
    }

    void setPossiblePiece(possiblePieceType possiblePiece) {
        PossiblePieces::possiblePiece = possiblePiece;
    }

    bool isIsMovable() const {
        return isMovable;
    }

    void setIsMovable(bool isMovable) {
        PossiblePieces::isMovable = isMovable;
    }

    void reset(){
        this->player = NO_PLAYER;
        this->possiblePiece = pEMPTY;
        this->isMovable = false;
        this->isJoker = false;
    }
};

class AutoPlayerAlgorithm: public PlayerAlgorithm{
private:
    playerEnum player;
    PossiblePieces knownBoard[N][M][2];

public:
    AutoPlayerAlgorithm(playerEnum _player): player(_player){
        resetKnownBoard();
    }

    void resetKnownBoard(){
        for(int i=0; i<N; i++)
            for(int j=0; j<M; j++)
                for(int k=0; k<2; k++)
                    knownBoard[i][j][k].reset();
    }

    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
    void notifyOnOpponentMove(const Move& move) override; // called only on opponent’s move
    void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
    unique_ptr<Move> getMove() override;
    unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
};


#endif //ADVANCEDTOPICS2_PLAYERALGORITHM_H
