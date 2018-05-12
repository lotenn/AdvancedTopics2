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
void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
    if(player == 1){
        vectorToFill.push_back(make_unique<PiecePositionImp>(2, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 9, 'F', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'J', 'S'));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'J', 'B'));
    }
    else{
        vectorToFill.push_back(make_unique<PiecePositionImp>(2, 5, 'R', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(8, 6, 'R', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(3, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(7, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(4, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'B', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(5, 9, 'F', NO_JOKER_CHANGE_SYMBOL));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'J', 'B'));
        vectorToFill.push_back(make_unique<PiecePositionImp>(6, 8, 'J', 'S'));
//        R 2 5
//        R 8 5
//        P 3 4
//        P 4 4
//        P 5 4
//        P 6 4
//        P 7 4
//        B 4 3
//        B 6 3
//        F 5 2
//        J 5 5 B
//        J 6 5 S
    }
}