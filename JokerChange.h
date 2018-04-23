//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_JOKERCHANGE_H
#define ADVANCEDTOPICS2_JOKERCHANGE_H

#include "Point.h"

class JokerChange {
    virtual const Point& getJokerChangePosition() const;
    virtual char getJokerNewRep() const; // R, P, S or B (but NOT J and NOT F)

};


#endif //ADVANCEDTOPICS2_JOKERCHANGE_H
