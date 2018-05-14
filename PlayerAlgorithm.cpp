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
        this->knownBoard[5][1].setIsMovable(true);
        this->knownBoard[5][1].setPlayer(PLAYER_1);
        this->knownBoard[5][1].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[5][7].setIsMovable(true);
        this->knownBoard[5][7].setPlayer(PLAYER_1);
        this->knownBoard[5][7].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][2].setIsMovable(true);
        this->knownBoard[6][2].setPlayer(PLAYER_1);
        this->knownBoard[6][2].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][3].setIsMovable(true);
        this->knownBoard[6][3].setPlayer(PLAYER_1);
        this->knownBoard[6][3].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][4].setIsMovable(true);
        this->knownBoard[6][4].setPlayer(PLAYER_1);
        this->knownBoard[6][4].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][5].setIsMovable(true);
        this->knownBoard[6][5].setPlayer(PLAYER_1);
        this->knownBoard[6][5].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[6][6].setIsMovable(true);
        this->knownBoard[6][6].setPlayer(PLAYER_1);
        this->knownBoard[6][6].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[7][3].setIsMovable(false);
        this->knownBoard[7][3].setPlayer(PLAYER_1);
        this->knownBoard[7][3].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[7][5].setIsMovable(false);
        this->knownBoard[7][5].setPlayer(PLAYER_1);
        this->knownBoard[7][5].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 9, 'F', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[8][4].setIsMovable(false);
        this->knownBoard[8][4].setPlayer(PLAYER_1);
        this->knownBoard[8][4].setPossiblePiece(pFLAG);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 6, 'J', 'S'));
        this->knownBoard[5][3].setIsMovable(true);
        this->knownBoard[5][3].setPlayer(PLAYER_1);
        this->knownBoard[5][3].setPossiblePiece(pSCISSORS);
        this->knownBoard[5][3].setIsJoker(true);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 6, 'J', 'B'));
        this->knownBoard[5][4].setIsMovable(false);
        this->knownBoard[5][4].setPlayer(PLAYER_1);
        this->knownBoard[5][4].setPossiblePiece(pBOMB);
        this->knownBoard[5][4].setIsJoker(true);
    }
    else{
        vectorToFill.push_back(make_unique<PiecePositionImp>(2, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[4][1].setIsMovable(true);
        this->knownBoard[4][1].setPlayer(PLAYER_2);
        this->knownBoard[4][1].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[4][7].setIsMovable(true);
        this->knownBoard[4][7].setPlayer(PLAYER_2);
        this->knownBoard[4][7].setPossiblePiece(pROCK);
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][2].setIsMovable(true);
        this->knownBoard[3][2].setPlayer(PLAYER_2);
        this->knownBoard[3][2].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][3].setIsMovable(true);
        this->knownBoard[3][3].setPlayer(PLAYER_2);
        this->knownBoard[3][3].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][4].setIsMovable(true);
        this->knownBoard[3][4].setPlayer(PLAYER_2);
        this->knownBoard[3][4].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][5].setIsMovable(true);
        this->knownBoard[3][5].setPlayer(PLAYER_2);
        this->knownBoard[3][5].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 4, 'P', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[3][6].setIsMovable(true);
        this->knownBoard[3][6].setPlayer(PLAYER_2);
        this->knownBoard[3][6].setPossiblePiece(pPAPER);
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 3, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[2][3].setIsMovable(false);
        this->knownBoard[2][3].setPlayer(PLAYER_2);
        this->knownBoard[2][3].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 3, 'B', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[2][5].setIsMovable(false);
        this->knownBoard[2][5].setPlayer(PLAYER_2);
        this->knownBoard[2][5].setPossiblePiece(pBOMB);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 2, 'F', NO_JOKER_CHANGE_SYMBOL));
        this->knownBoard[1][4].setIsMovable(false);
        this->knownBoard[1][4].setPlayer(PLAYER_2);
        this->knownBoard[1][4].setPossiblePiece(pFLAG);
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 5, 'J', 'B'));
        this->knownBoard[4][4].setIsMovable(false);
        this->knownBoard[4][4].setPlayer(PLAYER_2);
        this->knownBoard[4][4].setPossiblePiece(pBOMB);
        this->knownBoard[4][4].setIsJoker(true);
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 5, 'J', 'S'));
        this->knownBoard[4][5].setIsMovable(false);
        this->knownBoard[4][5].setPlayer(PLAYER_2);
        this->knownBoard[4][5].setPossiblePiece(pSCISSORS);
        this->knownBoard[4][5].setIsJoker(true);
    }
}