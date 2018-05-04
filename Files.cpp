
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

