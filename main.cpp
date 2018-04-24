#include <iostream>
#include <memory>
#include <utility>
#include "Parser.h"


using namespace std;



int main() {
    Parser parser;
//    unique_ptr<PiecePosition> positions = parser.parsePiecePosition("\tJ 2 3 B");
//
//    cout << positions.get()->getPosition().getX() << endl;
//    cout << positions.get()->getPosition().getY() << endl;
//    cout << positions.get()->getPiece() << endl;
//    cout << positions.get()->getJokerRep() << endl;

    vector<unique_ptr<Move>> moves;
    vector<unique_ptr<JokerChange>> jokerChanges;

//    moves.push_back(make_unique<MoveImp>(1,2,3,4));
//    jokerChanges.push_back(make_unique<JokerChangeImp>(1,2,'S'));

    parser.parseMoveCommand("1 2 3 4 ad ", moves, jokerChanges);
    cout << moves[0].get()->getTo().getX()<< endl;
    cout << jokerChanges[0].get()->getJokerNewRep()<< endl;

    return 0;
}