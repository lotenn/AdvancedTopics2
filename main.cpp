#include <iostream>
#include <memory>
#include <utility>
#include "Parser.h"

using namespace std;

int main() {
    Parser parser;
    unique_ptr<PiecePosition> positions = parser.parsePiecePosition("\tJ 2 3 B");

    cout << positions.get()->getPosition().getX() << endl;
    cout << positions.get()->getPosition().getY() << endl;
    cout << positions.get()->getPiece() << endl;
    cout << positions.get()->getJokerRep() << endl;
    return 0;
}