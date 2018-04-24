//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_BOARD_H
#define ADVANCEDTOPICS2_BOARD_H

#include "PiecePosition.h"

class Board {
    virtual int getPlayer(const Point& pos) const; // 1 for player 1’s piece, 2 for 2, 0 if empty

};


#endif //ADVANCEDTOPICS2_BOARD_H
