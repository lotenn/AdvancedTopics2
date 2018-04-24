//
// Created by loten on 23/04/2018.
//

#include "PlayerAlgorithm.h"

unique_ptr<Move> FilePlayerAlgorithm::getMove() {
    int fromX = moves[currentMove].getFrom().getX();
    int fromY = moves[currentMove].getFrom().getY();
    int toX = moves[currentMove].getTo().getX();
    int toY = moves[currentMove].getTo().getY();
    return make_unique<MoveImp>(fromX, fromY, toX, toY);
}