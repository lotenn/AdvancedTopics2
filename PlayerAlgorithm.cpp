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
        this->knownBoard[5][1][PRIMARY].setOptFlag(false);
        this->knownBoard[5][1][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[5][1][PRIMARY].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[5][7][PRIMARY].setOptFlag(false);
        this->knownBoard[5][7][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[5][7][PRIMARY].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][2][PRIMARY].setOptFlag(false);
        this->knownBoard[6][2][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][2][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][3][PRIMARY].setOptFlag(false);
        this->knownBoard[6][3][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][3][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][4][PRIMARY].setOptFlag(false);
        this->knownBoard[6][4][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][4][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][5][PRIMARY].setOptFlag(false);
        this->knownBoard[6][5][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][5][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][6][PRIMARY].setOptFlag(false);
        this->knownBoard[6][6][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[6][6][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[7][3][PRIMARY].setOptFlag(false);
        this->knownBoard[7][3][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[7][3][PRIMARY].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[7][5][PRIMARY].setOptFlag(false);
        this->knownBoard[7][5][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[7][5][PRIMARY].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 9, 'F', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[8][4][PRIMARY].setOptFlag(true);
        this->knownBoard[8][4][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[8][4][PRIMARY].setPossiblePiece(pFLAG);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 6, 'J', 'S'));
        this->knownBoard[5][3][PRIMARY].setOptFlag(false);
        this->knownBoard[5][3][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[5][3][PRIMARY].setPossiblePiece(pSCISSORS);
        this->knownBoard[5][3][PRIMARY].setIsJoker(true);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 6, 'J', 'B'));
        this->knownBoard[5][4][PRIMARY].setOptFlag(false);
        this->knownBoard[5][4][PRIMARY].setPlayer(PLAYER_1);
        this->knownBoard[5][4][PRIMARY].setPossiblePiece(pBOMB);
        this->knownBoard[5][4][PRIMARY].setIsJoker(true);
    }
    else{
        vectorToFill.push_back(make_unique<PiecePositionImp>(2, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[4][1][PRIMARY].setOptFlag(false);
        this->knownBoard[4][1][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[4][1][PRIMARY].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[4][7][PRIMARY].setOptFlag(false);
        this->knownBoard[4][7][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[4][7][PRIMARY].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][2][PRIMARY].setOptFlag(false);
        this->knownBoard[3][2][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][2][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][3][PRIMARY].setOptFlag(false);
        this->knownBoard[3][3][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][3][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][4][PRIMARY].setOptFlag(false);
        this->knownBoard[3][4][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][4][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][5][PRIMARY].setOptFlag(false);
        this->knownBoard[3][5][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][5][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][6][PRIMARY].setOptFlag(false);
        this->knownBoard[3][6][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[3][6][PRIMARY].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 3, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[2][3][PRIMARY].setOptFlag(false);
        this->knownBoard[2][3][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[2][3][PRIMARY].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 3, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[2][5][PRIMARY].setOptFlag(false);
        this->knownBoard[2][5][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[2][5][PRIMARY].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 2, 'F', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[1][4][PRIMARY].setOptFlag(true);
        this->knownBoard[1][4][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[1][4][PRIMARY].setPossiblePiece(pFLAG);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 5, 'J', 'B'));
        this->knownBoard[4][4][PRIMARY].setOptFlag(false);
        this->knownBoard[4][4][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[4][4][PRIMARY].setPossiblePiece(pBOMB);
        this->knownBoard[4][4][PRIMARY].setIsJoker(true);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 5, 'J', 'S'));
        this->knownBoard[4][5][PRIMARY].setOptFlag(false);
        this->knownBoard[4][5][PRIMARY].setPlayer(PLAYER_2);
        this->knownBoard[4][5][PRIMARY].setPossiblePiece(pSCISSORS);
        this->knownBoard[4][5][PRIMARY].setIsJoker(true);
    }
}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){
    int opponentPlayer_int = playerEnumToInt(getOpposite(this->player));
    int row, col;

    //finding opponent player & update.
    for(int x=1; x <= M; x++){
        for(int y=1; y <= N; y++){
            PointImp point(x,y);
            if(b.getPlayer(point) == opponentPlayer_int){
                row = PointUtils::getRow(point);
                col = PointUtils::getCol(point);
                knownBoard[row][col][PRIMARY].reset();    //In case current position includes this player's piece
                knownBoard[row][col][PRIMARY].setPlayer(getOpposite(this->player));
                knownBoard[row][col][PRIMARY].setPossiblePiece(pUNKNOWN);
            }
        }
    }
    /*
     * Iterating through fights vector
     * If this->player won the fight, knownBoard is already updated
     * else, we update known board according to the winner (opponent or both lose)
     */
    int winner_int;
    char opponentPiece_char;
    for(int i=0; i < (int)fights.size(); i++){
        winner_int = fights[i]->getWinner();
        row = PointUtils::getRow(fights[i]->getPosition());
        col = PointUtils::getCol(fights[i]->getPosition());
        opponentPiece_char = fights[i]->getPiece(opponentPlayer_int);

        //opponent won
        if(winner_int == opponentPlayer_int) {
            knownBoard[row][col][PRIMARY].reset();
            knownBoard[row][col][PRIMARY].setPlayer(getOpposite(this->player));
            knownBoard[row][col][PRIMARY].setPossiblePiece(charToPossiblePieceType(opponentPiece_char));
            knownBoard[row][col][PRIMARY].setOptFlag(false);
        }
        //both lose
        else if(winner_int == playerEnumToInt(NO_PLAYER))
            knownBoard[row][col][PRIMARY].reset();
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
        knownBoard[toRow][toCol][PRIMARY].setOptFlag(false);
    }
    //target point contains this player piece
    else{
        knownBoard[toRow][toCol][SECONDARY] = knownBoard[fromRow][fromCol][PRIMARY];
        knownBoard[toRow][toCol][SECONDARY].setOptFlag(false);
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
            knownBoard[row][col][PRIMARY].setOptFlag(false);
            knownBoard[row][col][SECONDARY].reset();
        }
        else    //secondary contains losing piece
            knownBoard[row][col][PRIMARY].setOptFlag(false);
            knownBoard[row][col][SECONDARY].reset();
    }
    //both lose
    else{
        knownBoard[row][col][PRIMARY].reset();
        knownBoard[row][col][SECONDARY].reset();
    }
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove(){
    //looking for a possible flag
    for(int i=0; i<N; i++) {
        for (int j = 0; j < M; j++) {
            if (knownBoard[i][j][PRIMARY].getPlayer() == this->player) {
                vector<PointImp> possibleTargets;
                PointImp from(j+1,i+1);
                getPossibleTargets(from, possibleTargets);
                for(const auto &possibleTarget : possibleTargets){
                    int targetRow, targetCol;
                    targetRow = PointUtils::getRow(possibleTarget);
                    targetCol = PointUtils::getCol(possibleTarget);
                    if(knownBoard[targetRow][targetCol][PRIMARY].isOptFlag()) {
                        performPlayerMove(from, possibleTarget);
                        return move(make_unique<MoveImp>(from.getX(), from.getY(),
                                                         possibleTarget.getX(), possibleTarget.getY()));
                    }
                }
            }
        }
    }

}

void AutoPlayerAlgorithm::performPlayerMove(const PointImp &from, const PointImp &to) {
    int fromRow = PointUtils::getRow(from), fromCol = PointUtils::getCol(from);
    int targetRow = PointUtils::getRow(to), targetCol = PointUtils::getCol(to);
    int key = knownBoard[targetRow][targetCol][PRIMARY].getPossiblePiece() == pEMPTY ?
              PRIMARY : SECONDARY;
    knownBoard[targetRow][targetCol][key] = knownBoard[fromRow][fromCol][PRIMARY];
}

void AutoPlayerAlgorithm::getPossibleTargets(const PointImp& point, vector<PointImp>& targetsToFill){
    int row, col;
    row = PointUtils::getRow(point);
    col = PointUtils::getCol(point);

    //check if the piece can actually move
    if(!canMove(knownBoard[row][col]->getPossiblePiece()))
        return;

    //left target
    if(col != LEFTMOST_COL){
        if(knownBoard[row][col-1]->getPlayer() != this->player)
            targetsToFill.emplace_back(point.getX()-1, point.getY());
    }
    //right target
    if(col != RIGHTMOST_COL){
        if(knownBoard[row][col+1]->getPlayer() != this->player)
            targetsToFill.emplace_back(point.getX()+1, point.getY());
    }
    //upper target
    if(row != UPMOST_ROW){
        if(knownBoard[row+1][col]->getPlayer() != this->player)
            targetsToFill.emplace_back(point.getX(), point.getY()+1);
    }
    //lower target
    if(row != DOWNMOST_ROW){
        if(knownBoard[row-1][col]->getPlayer() != this->player)
            targetsToFill.emplace_back(point.getX(), point.getY()-1);
    }
}

bool AutoPlayerAlgorithm::canMove(possiblePieceType p_pieceType){
    if(p_pieceType == pROCK || p_pieceType == pSCISSORS || p_pieceType == pPAPER)
        return true;
    return false;
}