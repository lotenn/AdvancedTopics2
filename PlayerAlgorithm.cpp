//
// Created by loten on 23/04/2018.
//

#include "PlayerAlgorithm.h"

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    ifstream positioningFile;
    const char* filePath;
    switch(player){
        case PLAYER_1:
            filePath = "../player1.rps_board";
            break;
        default:
            filePath = "../player2.rps_board";
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
        vectorToFill.push_back(_piecePosition);
    }
    positioningFile.close();
}
