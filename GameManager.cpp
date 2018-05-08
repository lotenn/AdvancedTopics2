#include "GameManager.h"
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

GameManager::GameManager(playerMode player1Mode, playerMode player2Mode){
    //creating the players
    if(player1Mode == FILE_PLAYER) {this->player1 = make_unique<FilePlayerAlgorithm>();}
    else{}//todo: creating auto player algorithm

    if(player2Mode == FILE_PLAYER){this->player2 = make_unique<FilePlayerAlgorithm>();}
    else{}//todo: creating auto player algorithm

    //creating the game pieces
    int toolIndex = 0;
    for(int i=toolIndex; toolIndex < (i+NUM_OF_R); toolIndex++){
        player1Pieces.push_back(make_shared<RockPiece>(PLAYER_1));
        player1Pieces.push_back(make_shared<RockPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_P); toolIndex++){
        player1Pieces.push_back(make_shared<PaperPiece>(PLAYER_1));
        player1Pieces.push_back(make_shared<PaperPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_S); toolIndex++){
        player1Pieces.push_back(make_shared<ScissorsPiece>(PLAYER_1));
        player1Pieces.push_back(make_shared<ScissorsPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_B); toolIndex++){
        player1Pieces.push_back(make_shared<BombPiece>(PLAYER_1));
        player1Pieces.push_back(make_shared<BombPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_J); toolIndex++){
        player1Pieces.push_back(make_shared<JokerPiece>(PLAYER_1));
        player1Pieces.push_back(make_shared<JokerPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_F); toolIndex++){
        player1Pieces.push_back(make_shared<FlagPiece>(PLAYER_1));
        player1Pieces.push_back(make_shared<FlagPiece>(PLAYER_2));
    }
}

bool GameManager::performBattle(const Point& point, shared_ptr<Piece> source, shared_ptr<Piece> target){
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

void generateOutputFile(const char *outputFilePath, string winner, string reason, string board){
    ofstream outputFile;
    outputFile.open(outputFilePath);
    if(outputFile.is_open()) {
        outputFile << "Winner: " << winner << endl;
        outputFile << "Reason: " << reason << endl;
        outputFile << endl;
        outputFile << board << endl;
        outputFile.close();
    }
    else cout<<"Error: Failed to open output file '" << outputFilePath << "'" <<endl;

}

void GameManager::initGame(){
    player1Score = player2Score = 0;
    currentPlayer = PLAYER_1;
    gameStatus.reset();
    board.clearBoard();
    for(shared_ptr<Piece> piece: player1Pieces)
        piece->removePiece();
    for(shared_ptr<Piece> piece: player2Pieces)
        piece->removePiece();
}

void GameManager::setPlayerPieces(const vector<unique_ptr<PiecePosition>> &piecePositions, playerEnum player,
                                  vector<unique_ptr<FightInfo>>& fights){
    vector<shared_ptr<Piece>> *playerPieces;
    if(player == PLAYER_1){playerPieces = &player1Pieces;}
    else{playerPieces = &player2Pieces;}

    for(int i=0; i < (int)piecePositions.size(); i++){
        pieceType _pieceType = charToPieceType(piecePositions[i]->getPiece());
        int row = PointUtils::getRow(piecePositions[i]->getPosition());
        int col = PointUtils::getCol(piecePositions[i]->getPosition());
        bool wasFight = false;
        if(piecePositions[i]->getJokerRep() != NO_JOKER_CHANGE_SYMBOL){
            for(shared_ptr<Piece> piece: *(playerPieces)){
                if(!piece->IsPositioned() && !piece->isJoker() && piece->getType() == _pieceType){
                    wasFight = performBattle(piecePositions[i]->getPosition(), piece,
                                             board.getPiece(piecePositions[i]->getPosition()));
                    if(wasFight)
                        fights.push_back(make_unique<FightInfoImp>(piecePositions[i]->getPosition(),
                                                                   fightInfo.getPiece(PLAYER_1),
                                                                   fightInfo.getPiece(PLAYER_2),
                                                                   fightInfo.getWinner()));
                }
                break;
            }
        }
        else{
            for(shared_ptr<Piece> piece: *(playerPieces)){
                if(!piece->IsPositioned() && piece->isJoker()){
                    piece->setJoker(_pieceType, gameStatus);
                    piece-> placePiece();
                    wasFight = performBattle(piecePositions[i]->getPosition(), piece,
                                             board.getPiece(piecePositions[i]->getPosition()));
                    if(wasFight)
                        fights.push_back(make_unique<FightInfoImp>(piecePositions[i]->getPosition(),
                                                                   fightInfo.getPiece(PLAYER_1),
                                                                   fightInfo.getPiece(PLAYER_2),
                                                                   fightInfo.getWinner()));
                }
                break;
            }
        }
    }
}

bool GameManager::containsMovingPieces(vector<shared_ptr<Piece>>& playerPieces){
    for(shared_ptr<Piece> piece: playerPieces) {
        if (piece->IsPositioned() && piece->canMove())
            return true;
    }
    return false;
}

bool GameManager::containsFlags(vector<shared_ptr<Piece>>& playerPieces){
    for(shared_ptr<Piece> piece: playerPieces) {
        if (piece->IsPositioned() && piece->getType() == FLAG)
            return true;
    }
    return false;
}



void GameManager::positioningStage(vector<unique_ptr<FightInfo>>& fights){
    vector<unique_ptr<PiecePosition>> player1PiecePosition, player2PiecePosition;
    player1->getInitialPositions(PLAYER_1, player1PiecePosition);
    player2->getInitialPositions(PLAYER_2, player2PiecePosition);
    validatePositioningVector(PLAYER_1, player1PiecePosition);
    validatePositioningVector(PLAYER_2, player2PiecePosition);
    if(!gameStatus.isGameOn()){
        //if there was a problematic positioning file and the game ended.
        if(gameStatus.getReason1() != NO_REASON && gameStatus.getReason2() != NO_REASON) {
            gameStatus.setMainReason(DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS);
            return;
        }
        else if(gameStatus.getReason1() != NO_REASON){
            gameStatus.setMainReason(gameStatus.getReason1());
            gameStatus.setWinner(PLAYER_2);
            gameStatus.setLoser(PLAYER_1);
            return;
        }
        else{
            gameStatus.setMainReason(gameStatus.getReason2());
            gameStatus.setWinner(PLAYER_1);
            gameStatus.setLoser(PLAYER_2);
            return;
        }
    }
    setPlayerPieces(player1PiecePosition, PLAYER_1, fights);
    setPlayerPieces(player2PiecePosition, PLAYER_2, fights);

    bool player1HasFlags, player2HasFlags, player1HasMovingPieces, player2HasMovingPieces, player1Loss, player2Loss;
    player1HasFlags = containsFlags(player1Pieces);
    player1HasMovingPieces = containsMovingPieces(player1Pieces);
    player2HasFlags = containsFlags(player2Pieces);
    player2HasMovingPieces = containsMovingPieces(player2Pieces);
    player1Loss = !player1HasFlags || !player1HasMovingPieces;
    player2Loss = !player2HasFlags || !player2HasMovingPieces;

    // in case of draw
    if(player1Loss && player2Loss){
        gameStatus.setGameOff();
        if(!player1HasFlags){
            gameStatus.setMainReason(DRAW_POSITIONING_ENDED_WITH_NO_FLAGS);
            gameStatus.setReason1(NO_MORE_FLAGS);
            gameStatus.setReason2(NO_MORE_FLAGS);
            return;
        }
        else{
            gameStatus.setMainReason(DRAW_POSITIONING_ENDED_WITH_NO_MOVING_TOOLS);
            gameStatus.setReason1(NO_MOVING_TOOLS);
            gameStatus.setReason2(NO_MOVING_TOOLS);
            return;
        }
    }
    //single winner
    else if(player1Loss) {
        return createEndGameMessage(player1LossReason, PLAYER_2);
    }
}