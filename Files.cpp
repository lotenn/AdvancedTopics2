#include "Files.h"

void validatePositioningFile(const char                         *filePath,
                             vector<unique_ptr<PiecePosition>>&  piecePositions,
                             GameStatus&                          gameStatus)
{
    ifstream positioningFile;
    positioningFile.open(filePath, ios::in);
    if (!positioningFile.is_open()) {
        gameStatus.setMainReason(NO_POSITIONING_FILE);
        gameStatus.setGameOff();
        return;
    }

    int lineNumber = 1;
    bool alreadyPositioned[N][M];
    memset(alreadyPositioned, 0, sizeof(bool) * M * N);
    int rockCounter = NUM_OF_R, scissorsCounter = NUM_OF_S, paperCounter = NUM_OF_P, flagCounter = NUM_OF_F, bombCounter = NUM_OF_B, jokerCounter = NUM_OF_J;

    string line;
    Parser parser;
    unique_ptr<PiecePosition> _piecePosition;
    while (getline(positioningFile, line)) {
        if (line.find_first_not_of(" \t\n\r") == line.npos) continue;
        _piecePosition = parser.parsePiecePosition(line);
        //bad syntax
        if (_piecePosition == nullptr) {
            positioningFile.close();
            gameStatus.setMainReason(BAD_POSITIONING_FILE_INVALID);
            gameStatus.setErrorLine1(lineNumber);
            gameStatus.setGameOff();
            return;
        }
        Point position = _piecePosition->getPosition();
        int row = PointUtils::getRow(position), col = PointUtils::getCol(position);

        //current point already contains same winner's tool
        if (alreadyPositioned[row][col]) {
            positioningFile.close();
            gameStatus.setMainReason(BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION);
            gameStatus.setErrorLine1(lineNumber);
            gameStatus.setGameOff();
            return;
        }
        //regular command
        if (_piecePosition->getJokerRep() == NO_JOKER_CHANGE_SYMBOL) {
            switch (_piecePosition->getPiece()) {
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
                positioningFile.close();
                gameStatus.setMainReason(BAD_POSITIONING_FILE_TOO_MANY_TOOLS);
                gameStatus.setErrorLine1(lineNumber);
                gameStatus.setGameOff();
                return;
            }
        }
            //joker command
        else {
            jokerCounter--;
            //out of tools
            if (jokerCounter < 0) {
                positioningFile.close();
                gameStatus.setMainReason(BAD_POSITIONING_FILE_TOO_MANY_TOOLS);
                gameStatus.setErrorLine1(lineNumber);
                gameStatus.setGameOff();
                return;
            }
            piecePositions.push_back(_piecePosition);
            alreadyPositioned[row][col] = true;
            lineNumber++;
        }
        //not enough flags positioned
        if (flagCounter != 0) {
            positioningFile.close();
            gameStatus.setMainReason(BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS);
            gameStatus.setErrorLine1(lineNumber);
            gameStatus.setGameOff();
            return;
        }
        positioningFile.close();
        return;
    }
}

void parsingMoveFile(const char                      *filePath,
                     vector<unique_ptr<Move>>&        moves,
                     vector<unique_ptr<JokerChange>>& jokerChanges,
                     GameStatus&                      gameStatus)
{
    ifstream movesFile;
    movesFile.open(filePath, ios::in);
    //file is not opened / created
    if(!movesFile.is_open()){
        gameStatus.setMainReason(NO_MOVE_FILE) ;
        gameStatus.setGameOff();
        return;
    }
    Parser parser;
    string line;
    while(getline(movesFile, line)){
        if(line.find_first_not_of(" \t\n\r") == line.npos) {continue;}  //Disregarding all-whitespace lines
        parser.parseMoveCommand(line, moves, jokerChanges);             //parsing line
    }
    movesFile.close();
    return;
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

