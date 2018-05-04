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

bool GameManager::performBattle(Point& point, shared_ptr<Piece> source, shared_ptr<Piece> target){
    bool wasFight = false, sourceWin = source->canCapture(target), targetWin = target->canCapture(source);
    char player1Piece = '#', player2Piece = '#';
    playerEnum winner = NO_PLAYER;
    if((source->getPlayer() == PLAYER_1 && target->getPlayer() == PLAYER_2) ||
       (source->getPlayer() == PLAYER_2 && target->getPlayer() == PLAYER_1)){
        wasFight = true;
        player1Piece = source->getPlayer() == PLAYER_1 ?
                       pieceTypeToChar(source->getType()) : pieceTypeToChar(target->getType());
        player2Piece = target->getPlayer() == PLAYER_2 ?
                       pieceTypeToChar(target->getType()) : pieceTypeToChar(source->getType());
    }
    if(sourceWin && targetWin){
        source->removePiece();
        target->removePiece();
        board.setPiece(point, board.getEmptyPiece());
    }
    else if(sourceWin){
        source->placePiece();
        target->removePiece();
        winner = source->getPlayer();
        board.setPiece(point, source);
    }
    else{
        target->placePiece();
        source->removePiece();
        winner = target->getPlayer();
        board.setPiece(point, target);
    }
    fightInfo.setPosition(point.getX(), point.getY());
    fightInfo.setPlayer1Piece(player1Piece);
    fightInfo.setPlayer2Piece(player2Piece);
    fightInfo.setWinner(winner);
    return wasFight;
}

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
        return performBattle(targetPoint, sourcePiece, targetPiece);
    }
}

void GameManager::executeJoker(unique_ptr<JokerChange> jokerChange){
    if(jokerChange == nullptr){
        gameStatus.setGameOff();
        gameStatus.setMainReason(BAD_MOVE_FILE_INVALID);
    }
    pieceType joker_new_type = charToPieceType(jokerChange->getJokerNewRep());
    shared_ptr<Piece> jokerPiece = board.getPiece(jokerChange->getJokerChangePosition());
    jokerPiece->setJoker(joker_new_type, gameStatus);
}