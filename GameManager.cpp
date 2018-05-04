#include "GameManager.h"

playerEnum getOpposite(playerEnum player){
    switch(player){
        case PLAYER_1:
            return PLAYER_2;
        case PLAYER_2:
            return PLAYER_1;
        default:
            return NO_PLAYER;
    }
}

string playerEnumToString(playerEnum player){
    map<playerEnum , string> strings;
    strings[PLAYER_1] = "player 1";
    strings[PLAYER_2] = "player 2";
    strings[NO_PLAYER] = "no player";
    auto str = strings.find(player);
    return str != strings.end() ? str->second : "";
}

string getWinnerString(playerEnum player){
    map<playerEnum , string> winner;
    winner[PLAYER_1] = "1";
    winner[PLAYER_2] = "2";
    winner[NO_PLAYER] = "0";
    auto str = winner.find(player);
    return str != winner.end() ? str->second : "";
}


//*********************************************************************

bool GameManager::executeMove(unique_ptr<Move> move){
    if(move == nullptr){
        gameStatus.setGameOff();
        gameStatus.setMainReason(BAD_MOVE_FILE_INVALID);
        return false;
    }
    Point sourcePoint = move->getFrom(), targetPoint = move->getTo();
    shared_ptr<Piece> sourcePiece = board.getPiece(sourcePoint), targetPiece = board.getPiece(targetPoint);
    if(sourcePiece->getPlayer() != this->currentPlayer){
        gameStatus.setGameOff();
        gameStatus.setMainReason(BAD_MOVE_FILE_NOT_YOUR_TOOL);
         return false;
    }
    else if(!sourcePiece->canMove(sourcePoint, targetPoint)){
        gameStatus.setGameOff();
        gameStatus.setMainReason(BAD_MOVE_FILE_TOOL_CANT_MOVE);
        return false;
    }
    else if(sourcePiece->getPlayer() == targetPiece->getPlayer()){
        gameStatus.setGameOff();
        gameStatus.setMainReason(BAD_MOVE_FILE_CELL_OCCUPIED);
        return false;
    }
    else{
        board.setPiece(sourcePoint, board.getEmptyPiece());
        return performBattle(targetPoint, sourcePiece, targetPiece, fightInfo);
    }
}

bool performBattle(Point& point, shared_ptr<Piece> sourcePiece, shared_ptr<Piece> targetPiece){
    bool wasFight = false;
    if((sourcePiece->getPlayer() == PLAYER_1 && targetPiece->getPlayer() == PLAYER_2) ||
            (sourcePiece->getPlayer() == PLAYER_2 && targetPiece->getPlayer() == PLAYER_1)){
        wasFight = true;
        char player1Piece, player2Piece;
        player1Piece = sourcePiece->getPlayer() == PLAYER_1 ?
                       pieceTypeToChar(sourcePiece->getType()) : pieceTypeToChar(targetPiece->getType());
    }
    char player1Piece, player2Piece;
}
