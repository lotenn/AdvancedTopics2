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
void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
    if(player == 1){

        vectorToFill.push_back(make_unique<PiecePositionImp>(2, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[1][5].setIsMovable(true);
        this->knownBoard[1][5].setPlayer(PLAYER_1);
        this->knownBoard[1][5].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[7][5].setIsMovable(true);
        this->knownBoard[7][5].setPlayer(PLAYER_1);
        this->knownBoard[7][5].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[2][6].setIsMovable(true);
        this->knownBoard[2][6].setPlayer(PLAYER_1);
        this->knownBoard[2][6].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][6].setIsMovable(true);
        this->knownBoard[3][6].setPlayer(PLAYER_1);
        this->knownBoard[3][6].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[4][6].setIsMovable(true);
        this->knownBoard[4][6].setPlayer(PLAYER_1);
        this->knownBoard[4][6].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[5][6].setIsMovable(true);
        this->knownBoard[5][6].setPlayer(PLAYER_1);
        this->knownBoard[5][6].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][6].setIsMovable(true);
        this->knownBoard[6][6].setPlayer(PLAYER_1);
        this->knownBoard[6][6].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][7].setIsMovable(false);
        this->knownBoard[3][7].setPlayer(PLAYER_1);
        this->knownBoard[3][7].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[5][7].setIsMovable(false);
        this->knownBoard[5][7].setPlayer(PLAYER_1);
        this->knownBoard[5][7].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 9, 'F', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[4][8].setIsMovable(false);
        this->knownBoard[4][8].setPlayer(PLAYER_1);
        this->knownBoard[4][8].setPossiblePiece(pFLAG);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'J', 'S'));
        this->knownBoard[5][7].setIsMovable(true);
        this->knownBoard[5][7].setPlayer(PLAYER_1);
        this->knownBoard[5][7].setPossiblePiece(pSCISSORS);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'J', 'B'));
        this->knownBoard[5][7].setIsMovable(true);
        this->knownBoard[5][7].setPlayer(PLAYER_1);
        this->knownBoard[5][7].setPossiblePiece(pROCK);
    }
    else{
        vectorToFill.push_back(make_unique<PiecePositionImp>(2, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 3, 'B', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 3, 'B', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 2, 'F', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 5, 'J', 'B'));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 5, 'J', 'S'));
    }
}