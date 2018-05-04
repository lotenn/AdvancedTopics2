#include <map>
#include <memory.h>
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


//********************************************************************************************

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

void GameManager::validatePositioningVector(playerEnum player, vector<unique_ptr<PiecePosition>>&  piecePositions){
    //No positioning file or empty file
    if (piecePositions.empty()) {
        player == PLAYER_1 ? gameStatus.setReason1(NO_POSITIONING_FILE) : gameStatus.setReason2(NO_POSITIONING_FILE);
        gameStatus.setGameOff();
        return;
    }

    bool alreadyPositioned[N][M];
    memset(alreadyPositioned, 0, sizeof(bool) * M * N);
    int rockCounter = NUM_OF_R,
            scissorsCounter = NUM_OF_S,
            paperCounter = NUM_OF_P,
            flagCounter = NUM_OF_F,
            bombCounter = NUM_OF_B,
            jokerCounter = NUM_OF_J,
            lineNumber = 1;

    //iterating through the vector
   for(int i=0; i<piecePositions.size(); i++) {
       lineNumber = i+1;
       //Invalid command
       if (piecePositions[i] == nullptr) {
           player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_INVALID)
                              : gameStatus.setReason2(BAD_POSITIONING_FILE_INVALID);
           player == PLAYER_1 ? gameStatus.setErrorLine1(lineNumber)
                              : gameStatus.setErrorLine2(lineNumber);
           gameStatus.setGameOff();
           return;
       }
       Point position = piecePositions[i]->getPosition();
       int row = PointUtils::getRow(position), col = PointUtils::getCol(position);

       //current point already contains same winner's tool
       if (alreadyPositioned[row][col]) {
           player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION)
                              : gameStatus.setReason2(BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION);
           player == PLAYER_1 ? gameStatus.setErrorLine1(lineNumber)
                              : gameStatus.setErrorLine2(lineNumber);
           gameStatus.setGameOff();
           return;
       }
       //regular command
       if (piecePositions[i]->getJokerRep() == NO_JOKER_CHANGE_SYMBOL) {
           switch (piecePositions[i]->getPiece()) {
               case 'R':
                   rockCounter--;
                   break;
               case 'S':
                   scissorsCounter--;
                   break;
               case 'P':
                   paperCounter--;
                   break;
               case 'F':
                   flagCounter--;
                   break;
               default:
                   bombCounter--;
                   break;
           }

           //out of tools
           if (rockCounter < 0 || scissorsCounter < 0 || paperCounter < 0 || flagCounter < 0 || bombCounter < 0) {
               player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_TOO_MANY_TOOLS)
                                  : gameStatus.setReason2(BAD_POSITIONING_FILE_TOO_MANY_TOOLS);
               player == PLAYER_1 ? gameStatus.setErrorLine1(lineNumber)
                                  : gameStatus.setErrorLine2(lineNumber);
               gameStatus.setGameOff();
               return;
           }
       }
       //joker command
       else {
           jokerCounter--;
           //out of tools
           if (jokerCounter < 0) {
               player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_TOO_MANY_TOOLS)
                                  : gameStatus.setReason2(BAD_POSITIONING_FILE_TOO_MANY_TOOLS);
               player == PLAYER_1 ? gameStatus.setErrorLine1(lineNumber)
                                  : gameStatus.setErrorLine2(lineNumber);
               gameStatus.setGameOff();
               return;
           }
           alreadyPositioned[row][col] = true;
       }
   }
    //vector ended with not enough flags positioned
    if (flagCounter != 0) {
        player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS)
                           : gameStatus.setReason2(BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS);
        player == PLAYER_1 ? gameStatus.setErrorLine1(lineNumber)
                           : gameStatus.setErrorLine2(lineNumber);
        gameStatus.setGameOff();
    }
}
