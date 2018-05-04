#include "Game.h"



endGameReason toReason(executeCommandMessage msg){
    switch(msg){
        case EXECUTE_COMMAND_NOT_YOUR_TOOL:
            return BAD_MOVE_FILE_NOT_YOUR_TOOL;
        case EXECUTE_COMMAND_TOOL_CANT_MOVE:
            return BAD_MOVE_FILE_TOOL_CANT_MOVE;
        case EXECUTE_COMMAND_CELL_OCCUPIED:
            return BAD_MOVE_FILE_CELL_OCCUPIED;
        case EXECUTE_COMMAND_NOT_JOKER:
            return BAD_MOVE_FILE_NOT_JOKER;
        default:
            return BAD_MOVE_FILE_INVALID;
    }
}

string getBadInputFileMessage(endGameReason reason){
    map<endGameReason, string> messages;
    messages[BAD_POSITIONING_FILE_INVALID] = "invalid line in Positioning input file";
    messages[BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS] = "not enough flags in the positioning input file";
    messages[BAD_POSITIONING_FILE_TOO_MANY_TOOLS] = "too many tools in positioning input file";
    messages[BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION] = "2 tools located in the same cell in the positioning input file";
    messages[BAD_MOVE_FILE_NOT_YOUR_TOOL] = "specified cell does not contain player's tool";
    messages[BAD_MOVE_FILE_TOOL_CANT_MOVE] = "trying to perform an illegal movement with a tool";
    messages[BAD_MOVE_FILE_CELL_OCCUPIED] = "target cell already contains player's tool";
    messages[BAD_MOVE_FILE_NOT_JOKER] = "cannot change tool type. cell does not contain a joker";
    messages[BAD_MOVE_FILE_INVALID] = "invalid line in Moves input file";
    auto str = messages.find(reason);
    return str != messages.end() ? str->second : "";
}

string getReasonString(endGameMessage endGameMsg){
    map<endGameReason, string> reasons;
    reasons[NO_MORE_FLAGS] = "All flags of the opponent are captured";
    reasons[NO_MOVING_TOOLS] = "All moving PIECEs of the opponent are eaten";
    reasons[BAD_POSITIONING_FILE_INVALID] = "Bad Positioning input file for "+
                                            playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS] = "Bad Positioning input file for "+
                                                     playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[BAD_POSITIONING_FILE_TOO_MANY_TOOLS] = "Bad Positioning input file for "+
                                                   playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION] = "Bad Positioning input file for "+
                                                            playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[BAD_MOVE_FILE_INVALID] = "Bad Moves input file for "+ playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[BAD_MOVE_FILE_NOT_YOUR_TOOL] = "Bad Moves input file for "+
                                           playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[BAD_MOVE_FILE_TOOL_CANT_MOVE] = "Bad Moves input file for "+
                                            playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[BAD_MOVE_FILE_CELL_OCCUPIED] = "Bad Moves input file for "+
                                           playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[BAD_MOVE_FILE_NOT_JOKER] = "Bad Moves input file for "+ playerEnumToString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1);
    reasons[DRAW_NO_MORE_MOVES] = "A tie - both Moves input files done without a winner";
    reasons[DRAW_NO_MOVING_TOOLS] = "A tie - all moving PIECEs are eaten by both players";
    reasons[DRAW_POSITIONING_ENDED_WITH_NO_FLAGS] = "A tie - all flags are eaten by both players in the position files";
    reasons[DRAW_POSITIONING_ENDED_WITH_NO_MOVING_TOOLS] = "A tie - moving PIECEs are eaten by both players in the position files";
    reasons[DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS] = "Bad Positioning input file for both players - player 1: line "+to_string(endGameMsg.errorLine1)+", player 2: line "+to_string(endGameMsg.errorLine2);

    auto str = reasons.find(endGameMsg.mainReason);
    return str != reasons.end() ? str->second : "";
}

endGameMessage createEndGameMessage(endGameReason _mainReason, endGameReason _reason1, endGameReason _reason2, playerEnum _winner, int _errorLine1, int _errorLine2){
    endGameMessage msg;
    msg.mainReason = _mainReason;
    msg.reason1 = _reason1;
    msg.reason2 = _reason2;
    msg.winner = _winner;
    msg.errorLine1 = _errorLine1;
    msg.errorLine2 = _errorLine2;
    return msg;
}

endGameMessage createEndGameMessage(endGameReason reason, playerEnum winner, int _errorLine1, int _errorLine2){
    return createEndGameMessage(reason, NO_WINNER, NO_WINNER, winner, _errorLine1, _errorLine2);
}

endGameMessage createEndGameMessage(endGameReason reason, playerEnum winner){
    return createEndGameMessage(reason, winner, -1, -1);
}


Game::Game():emptyTool(new EmptyPiece(NO_PLAYER)), player1Score(0), player2Score(0), currentPlayer(PLAYER_1){
    player1Tools.reserve(NUM_OF_TOOLS);
    player2Tools.reserve(NUM_OF_TOOLS);

    int toolIndex = 0;
    for(int i = toolIndex; toolIndex<(i+NUM_OF_R); toolIndex++){
        player1Tools.push_back(new RockPiece(PLAYER_1));
        player2Tools.push_back(new RockPiece(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_P); toolIndex++){
        player1Tools.push_back(new PaperPiece(PLAYER_1));
        player2Tools.push_back(new PaperPiece(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_S); toolIndex++){
        player1Tools.push_back(new ScissorsPiece(PLAYER_1));
        player2Tools.push_back(new ScissorsPiece(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_B); toolIndex++){
        player1Tools.push_back(new BombPiece(PLAYER_1));
        player2Tools.push_back(new BombPiece(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_J); toolIndex++){
        player1Tools.push_back(new JokerPiece(PLAYER_1));
        player2Tools.push_back(new JokerPiece(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_F); toolIndex++){
        player1Tools.push_back(new FlagPiece(PLAYER_1));
        player2Tools.push_back(new FlagPiece(PLAYER_2));
    }
}

Game::~Game() {
    for(int i=0; i<NUM_OF_TOOLS; i++){
        delete player1Tools[i];
        delete player2Tools[i];
    }
    delete emptyTool;
}

void Game::setPlayerTools(const vector<PositioningCommand> &commands, playerEnum player){
//    playerEnum oppositePlayer = getOppositePlayer(this->getCurrentPlayer());
    vector<Piece *> *playerTools;
    switch (player){
        case PLAYER_1:
            playerTools = &(this->player1Tools);
            break;
        case PLAYER_2:
            playerTools = &(this->player2Tools);
            break;
        default:
            break;
    }
    //iterating through all commands in "commands" vector
    for(int i=0; i<(int)commands.size(); i++){
        //extracting data from current command
        pieceType _toolType = charToToolType(commands[i].toolType);
        int col = getCol(commands[i].source), row = getRow(commands[i].source);

        //Regular command
        if(commands[i].type == REGULAR_POSITIONING_COMMAND){
            for (Piece *tool:(*playerTools)) {
                //matching tool was found (not positioned, not joker, correct type)
                if (!tool->IsPositioned() && !tool->isJoker() && tool->getType() == _toolType) {
                    this->gameBoard[row][col] = this->battleWinner(tool, this->gameBoard[row][col]);
                    break;
                }
                //a matching tool must be found (commands are valid) thus no "else" statement is needed
            }
        }
        //joker commands
        else{
            //looking for next un-positioned joker
            for (Piece* tool:(*playerTools)) {
                //matching tool was found (not positioned, joker type)
                if (!tool->IsPositioned() && tool->isJoker()) {
                    tool->setJoker(_toolType);
                    tool->placePiece();
                    this->gameBoard[row][col] = this->battleWinner(tool, this->gameBoard[row][col]);
                    break;
                }
                //a matching tool must be found (commands are valid) thus no "else" statement is needed
            }
        }
    }
    //end of commands vector
}

void Game::resetGameBoard(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            gameBoard[i][j] = emptyTool;
        }
    }

    for(Piece *tool: player1Tools)
        tool->removePiece();

    for(Piece *tool: player2Tools)
        tool->removePiece();
}

void Game::setCurrentPlayer(playerEnum player){
    if(player == NO_PLAYER)
        return;
    this->currentPlayer = player;
}



Piece* Game::battleWinner(Piece *source, Piece *target) {
    bool sourceWin = source->canCapture(target), targetWin = target->canCapture(source);
    if(sourceWin && targetWin) {
        source->removePiece();
        target->removePiece();
        return this->emptyTool;
    }
    else if(sourceWin) {
        source->placePiece();
        target->removePiece();
        return source;
    }
    else{
        target->placePiece();
        source->removePiece();
        return target;
    }
}



executeCommandMessage Game::executeJoker(Command cmd){
    //joker command execution
    Cell jokerCell = cmd.joker;
    int jokerRow = getRow(jokerCell), jokerCol = getCol(jokerCell);
    pieceType joker_new_type = charToToolType(cmd.new_type);
    Piece *jokerTool = this->gameBoard[jokerRow][jokerCol];
    return jokerTool->setJoker(joker_new_type);
}

executeCommandMessage Game::executeCommand(Command cmd){
    switch(cmd.steps[cmd.currentStep]){
        case MOVE_COMMAND:
            return executeMove(cmd);
        case JOKER_COMMAND:
            return executeJoker(cmd);
        default:
            return EXECUTE_COMMAND_INVALID;
    }
}

endGameReason Game::playerHasLost(vector<Piece*> playerTools){
    int flagsCount=0;
    int movingToolsCount=0;
    for(Piece *tool:playerTools) {
        if (tool->IsPositioned()) {
            if (tool->getType() == FLAG) {flagsCount++;}
            else if (tool->canMove()) {movingToolsCount++;}
        }
    }
    if(flagsCount==0){return NO_MORE_FLAGS;}
    else if(movingToolsCount==0){return NO_MOVING_TOOLS;}
    else {return NO_WINNER;}
}

endGameMessage Game::checkGameWinner(){
    endGameReason player1LossReason = playerHasLost(this->player1Tools);
    endGameReason player2LossReason = playerHasLost(this->player2Tools);
    //In case of draw
    if(player1LossReason != NO_WINNER && player2LossReason != NO_WINNER){
        //Possible only at end of pos. file reading of both players
        if(player1LossReason == NO_MORE_FLAGS) {return createEndGameMessage(DRAW_POSITIONING_ENDED_WITH_NO_FLAGS, NO_PLAYER); }
        //Possible at both game states (init and play) thus an additional check will be conducted at game init
        else {return createEndGameMessage(DRAW_NO_MOVING_TOOLS, NO_PLAYER);}
    }
    //Single winner
    else if(player1LossReason != NO_WINNER) {return createEndGameMessage(player1LossReason, PLAYER_2);}
    else if(player2LossReason != NO_WINNER) {return createEndGameMessage(player2LossReason, PLAYER_1);}
    //Game is not finished
    else {return createEndGameMessage(NO_WINNER, NO_PLAYER);}
}

void Game::raisePlayerScore(int score, playerEnum player){
    if(player == PLAYER_1) this->player1Score+=score;
    else if(player == PLAYER_2) this->player2Score+=score;
}




