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

void GameManager::executeMove(Move& move){
    if(move == nullptr){

    }
}

executeCommandMessage Game::executeMove(Command cmd){
    Cell source = cmd.source, target = cmd.target;
    int sourceRow = getRow(source), sourceCol = getCol(source), targetRow = getRow(target), targetCol = getCol(target);
    Piece *sourceTool = this->gameBoard[sourceRow][sourceCol], *targetTool = this->gameBoard[targetRow][targetCol];
    //trying to move tool doesn't belong to player
    if(sourceTool->getPlayer() != this->getCurrentPlayer())
        return EXECUTE_COMMAND_NOT_YOUR_TOOL;
        //trying to move tool that cannot move
    else if(!sourceTool->canMove(source, target))
        return EXECUTE_COMMAND_TOOL_CANT_MOVE;
        //move's target cell contain player tool
    else if(sourceTool->getPlayer() == targetTool->getPlayer())
        return EXECUTE_COMMAND_CELL_OCCUPIED;
        //valid move
    else{
        this->gameBoard[sourceRow][sourceCol] = this->emptyTool;
        this->gameBoard[targetRow][targetCol] = this->battleWinner(sourceTool, targetTool);
        return EXECUTE_COMMAND_SUCCESS;
    }
}

