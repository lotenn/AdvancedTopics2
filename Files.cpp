
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

