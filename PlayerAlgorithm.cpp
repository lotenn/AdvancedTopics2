#include "PlayerAlgorithm.h"
//******************************************File Algorithm*****************************************************

void FilePlayerAlgorithm::getInitialPositions(int _player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) {
    ifstream positioningFile;
    const char* filePath;
    switch(_player){
        case PLAYER_1:
            filePath = "../player1.rps_board";
            this->player = PLAYER_1;
            break;
        default:
            filePath = "../player2.rps_board";
            this->player = PLAYER_2;
            break;
    }
    //invalid file or file doesn't exist
    positioningFile.open(filePath, ios::in);
    if (!positioningFile.is_open()) return;

    string line;
    Parser parser;
    unique_ptr<PiecePosition> _piecePosition;
    while (getline(positioningFile, line)) {
        if (line.find_first_not_of(" \t\n\r") == line.npos) continue;
        _piecePosition = parser.parsePiecePosition(line);
        vectorToFill.push_back(move(_piecePosition));
    }
    positioningFile.close();
}

void FilePlayerAlgorithm::getMoves(){
    ifstream movesFile;
    const char* filePath;
    switch(this->player){
        case PLAYER_1:
            filePath = "../player1.rps_moves";
            break;
        default:
            filePath = "../player2.rps_moves";
            break;
    }
    movesFile.open(filePath, ios::in);
    //file is not opened / created
    if(!movesFile.is_open()){
        this->moves.push_back(make_unique<MoveImp>(INVALID_COORD,INVALID_COORD,INVALID_COORD,INVALID_COORD));
        this->jokerChanges.push_back(make_unique<JokerChangeImp>(INVALID_COORD,INVALID_COORD,INVALID_CHAR));
        return;
    }

    Parser parser;
    string line;
    while(getline(movesFile, line)){
        if(line.find_first_not_of(" \t\n\r") == line.npos) {continue;}  //Disregarding all-whitespace lines
        parser.parseMoveCommand(line, this->moves, this->jokerChanges);    //parsing line and push moves to vectors
    }
    movesFile.close();
}

//*******************************************Auto Algorithm*****************************************************
void AutoPlayerAlgorithm::resetKnownBoard(){
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            for(int k=0; k<2; k++)
                knownBoard[i][j][k].reset();
}

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
    if(player == 1){

        vectorToFill.push_back(make_unique<PiecePositionImp>(2, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[5][1][PRIMARY].setIsMovable(true);
        this->knownBoard[5][1][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[5][1][PRIMARY].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[5][7][PRIMARY].setIsMovable(true);
        this->knownBoard[5][7][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[5][7][PRIMARY].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][2][PRIMARY].setIsMovable(true);
        this->knownBoard[6][2][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][2][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][3][PRIMARY].setIsMovable(true);
        this->knownBoard[6][3][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][3][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][4][PRIMARY].setIsMovable(true);
        this->knownBoard[6][4][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][4][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][5][PRIMARY].setIsMovable(true);
        this->knownBoard[6][5][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][5][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][6][PRIMARY].setIsMovable(true);
        this->knownBoard[6][6][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][6][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[7][3][PRIMARY].setIsMovable(false);
        this->knownBoard[7][3][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[7][3][PRIMARY].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[7][5][PRIMARY].setIsMovable(false);
        this->knownBoard[7][5][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[7][5][PRIMARY].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 9, 'F', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[8][4][PRIMARY].setIsMovable(false);
        this->knownBoard[8][4][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[8][4][PRIMARY].setPossiblePiece(pFLAG);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 6, 'J', 'S'));
        this->knownBoard[5][3][PRIMARY].setIsMovable(true);
        this->knownBoard[5][3][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[5][3][PRIMARY].setPossiblePiece(pSCISSORS);
        this->knownBoard[5][3][PRIMARY].setIsJoker(true);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 6, 'J', 'B'));
        this->knownBoard[5][4][PRIMARY].setIsMovable(false);
        this->knownBoard[5][4][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[5][4][PRIMARY].setPossiblePiece(pBOMB);
        this->knownBoard[5][4][PRIMARY].setIsJoker(true);
    }
    else{
        vectorToFill.push_back(make_unique<PiecePositionImp>(2, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[4][1][PRIMARY].setIsMovable(true);
        this->knownBoard[4][1][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[4][1][PRIMARY].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[4][7][PRIMARY].setIsMovable(true);
        this->knownBoard[4][7][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[4][7][PRIMARY].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][2][PRIMARY].setIsMovable(true);
        this->knownBoard[3][2][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][2][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][3][PRIMARY].setIsMovable(true);
        this->knownBoard[3][3][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][3][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][4][PRIMARY].setIsMovable(true);
        this->knownBoard[3][4][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][4][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][5][PRIMARY].setIsMovable(true);
        this->knownBoard[3][5][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][5][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][6][PRIMARY].setIsMovable(true);
        this->knownBoard[3][6][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][6][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 3, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[2][3][PRIMARY].setIsMovable(false);
        this->knownBoard[2][3][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[2][3][PRIMARY].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 3, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[2][5][PRIMARY].setIsMovable(false);
        this->knownBoard[2][5][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[2][5][PRIMARY].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 2, 'F', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[1][4][PRIMARY].setIsMovable(false);
        this->knownBoard[1][4][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[1][4][PRIMARY].setPossiblePiece(pFLAG);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 5, 'J', 'B'));
        this->knownBoard[4][4][PRIMARY].setIsMovable(false);
        this->knownBoard[4][4][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[4][4][PRIMARY].setPossiblePiece(pBOMB);
        this->knownBoard[4][4][PRIMARY].setIsJoker(true);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 5, 'J', 'S'));
        this->knownBoard[4][5][PRIMARY].setIsMovable(false);
        this->knownBoard[4][5][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[4][5][PRIMARY].setPossiblePiece(pSCISSORS);
        this->knownBoard[4][5][PRIMARY].setIsJoker(true);
    }
}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){
    int opponentPlayer = playerEnumToInt(getOpposite(this->player));
    int row, col;

    //finding opponent player & update.
    for(int x=1; x <= M; x++){
        for(int y=1; y <= N; y++){
            PointImp point(x,y);
            if(b.getPlayer(point) == opponentPlayer){
                row = PointUtils::getRow(point);
                col = PointUtils::getCol(point);
                this->knownBoard[row][col][PRIMARY].reset();    //In case current position includes this player's piece
                this->knownBoard[row][col][PRIMARY].setPlayer(getOpposite(this->player));
                this->knownBoard[row][col][PRIMARY].setPossiblePiece(pUNKNOWN);
            }
        }
    }
    /*
     * Iterating through fights vector
     * If this->player won the fight, knownBoard is already updated
     * else, we update known board according to the winner (opponent or both lose)
     */
    int winnerInt;
    char opponentPiece;
    for(int i=0; i < (int)fights.size(); i++){
        winnerInt = fights[i]->getWinner();
        row = PointUtils::getRow(fights[i]->getPosition());
        col = PointUtils::getCol(fights[i]->getPosition());
        opponentPiece = fights[i]->getPiece(opponentPlayer);

        //opponent won
        if(winnerInt == opponentPlayer)
            this->knownBoard[row][col][PRIMARY].setPossiblePiece(charToPossiblePieceType(opponentPiece));
        //both lose
        else if(winnerInt == playerEnumToInt(NO_PLAYER))
            this->knownBoard[row][col][PRIMARY].reset();
        else continue;  //this player won - known board is up2date
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move){
    int fromCol, fromRow, toCol, toRow;
    fromRow = PointUtils::getRow(move.getFrom());
    fromCol = PointUtils::getCol(move.getFrom());
    toRow = PointUtils::getRow(move.getTo());
    toCol = PointUtils::getCol(move.getTo());

    //target point is empty
    if(knownBoard[toRow][toCol][PRIMARY].getPossiblePiece() == pEMPTY){
        knownBoard[toRow][toCol][PRIMARY] = knownBoard[fromRow][fromCol][PRIMARY];
        knownBoard[toRow][toCol][PRIMARY].setIsMovable(true);
    }
    //target point contains this player piece
    else{
        knownBoard[toRow][toCol][SECONDARY] = knownBoard[fromRow][fromCol][PRIMARY];
        knownBoard[toRow][toCol][SECONDARY].setIsMovable(true);
    }
    this->knownBoard[fromRow][fromCol][PRIMARY].reset();
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){
    int thisPlayer, opponentPlayer, col, row;
    thisPlayer = playerEnumToInt(this->player);
    opponentPlayer = playerEnumToInt(getOpposite(this->player));

    char opponentPiece = fightInfo.getPiece(opponentPlayer);
    row = PointUtils::getRow(fightInfo.getPosition());
    col = PointUtils::getCol(fightInfo.getPosition());

    //this player won the fight
    if(fightInfo.getWinner() == thisPlayer){
        if(knownBoard[row][col][PRIMARY].getPlayer() == this->player){
           knownBoard[row][col][SECONDARY].reset();
        }
        else{
            knownBoard[row][col][PRIMARY] = knownBoard[row][col][SECONDARY];
            knownBoard[row][col][SECONDARY].reset();
        }
    }
    //opponent won the fight
    else if(fightInfo.getWinner() == opponentPlayer){
        //primary contains losing piece
        if(knownBoard[row][col][PRIMARY].getPlayer() == this->player){
            knownBoard[row][col][PRIMARY] = this->knownBoard[row][col][SECONDARY];
            knownBoard[row][col][PRIMARY].setPossiblePiece(charToPossiblePieceType(opponentPiece));
            knownBoard[row][col][SECONDARY].reset();
        }
        else    //secondary contains losing piece
            knownBoard[row][col][SECONDARY].reset();
    }
    //both lose
    else{
        knownBoard[row][col][PRIMARY].reset();
        knownBoard[row][col][SECONDARY].reset();
    }
}