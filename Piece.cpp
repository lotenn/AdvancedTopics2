//
// Created by loten on 20/04/2018.
//

#include "Piece.h"

pieceType charToPieceType(char c) {
    switch (c) {
        case 'R':
            return ROCK;
        case 'P':
            return PAPER;
        case 'S':
            return SCISSORS;
        case 'B':
            return BOMB;
        case 'F':
            return FLAG;
        default:
            return EMPTY;
    }
}




bool isNumInRange(char* str, int rangeStart, int rangeEnd) {
    if (str == NULL || strlen(str)==0) {
        return false;
    }
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
        //not valid digits
        if (!('0' <= str[i] && str[i] <= '9')) return false;
    }
    //str in a number
    int num = atoi(str);

    return (num >= rangeStart && num <= rangeEnd);
}

bool isValidPieceType(char Piece){
    switch (Piece) {
        case 'R':
        case 'P':
        case 'S':
        case 'B':
        case 'F':
        case 'J':
            return true;
        default:
            return false;
    }
}

bool isCharArrValidPieceType(char *c) {
    if(c == NULL) return false;
    if(strlen(c)==1){
        char tool = *c;
        return isValidPieceType(tool);
    }
    return false;
}

bool isValidJokerPieceType(char tool){
    switch (tool) {
        case 'R':
        case 'P':
        case 'S':
        case 'B':
            return true;
        default:
            return false;
    }
}

bool isCharArrValidJokerPieceType(char *c) {
    if(c == NULL) return false;
    if(strlen(c)==1){
        char tool = *c;
        return isValidJokerPieceType(tool);
    }
    return false;
}