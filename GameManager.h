//
// Created by loten on 30/04/2018.
//

#ifndef ADVANCEDTOPICS2_GAMEMANAGER_H
#define ADVANCEDTOPICS2_GAMEMANAGER_H

#include "Board.h"
#include "FightInfo.h"
#include "GameStatus.h"
#include "Move.h"
#include "Parser.h"
#define NUM_OF_R 2
#define NUM_OF_P 5
#define NUM_OF_S 1
#define NUM_OF_B 2
#define NUM_OF_J 2
#define NUM_OF_F 1
#define NUM_OF_TOOLS (NUM_OF_B + NUM_OF_F + NUM_OF_J + NUM_OF_P + NUM_OF_R + NUM_OF_S)




int static playerEnumToInt(playerEnum player){
    switch(player){
        case PLAYER_1:
            return 1;
        case PLAYER_2:
            return 2;
        case NO_PLAYER:
            return 0;
        default:
            return -1;
    }
}

string playerEnumToString(playerEnum player);

playerEnum getOpposite(playerEnum player);

string getWinnerString(playerEnum player);

//***********************Game Manager*****************************************************

class GameManager {
private:
    BoardImp board;
    vector<shared_ptr<Piece>> player1Tools;
    vector<shared_ptr<Piece>> player2Tools;
    int player1Score;
    int player2Score;
    playerEnum currentPlayer;
    FightInfoImp fightInfo;
    GameStatus gameStatus;


public:
    void validatePositioningVector(playerEnum player, vector<unique_ptr<PiecePosition>>&  piecePositions);

    /*
     * Set @arg(player) tools according to @arg(commands)
    */
    void setPlayerTools(const vector<PositioningCommand> &commands, playerEnum player);

    bool executeMove(unique_ptr<Move> move);

    bool performBattle(Point& point,shared_ptr<Piece> sourcePiece, shared_ptr<Piece> targetPiece, FightInfoImp& fightInfo);

};


#endif //ADVANCEDTOPICS2_GAMEMANAGER_H
