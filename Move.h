//
// Created by loten on 20/04/2018.
//

#ifndef ADVANCEDTOPICS2_MOVE_H
#define ADVANCEDTOPICS2_MOVE_H

#include "JokerChange.h"

class Move {
public:
    virtual const Point& getFrom() const = 0;
    virtual const Point& getTo() const = 0;
};

class MoveImp: public Move{
private:
    Point from;
    Point to;

public:
    MoveImp(int fromX, int fromY, int toX, int toY): from(PointImp(fromX, fromY)), to(PointImp(toX, toY)){}
    const Point& getFrom() const override {return this->from;}
    const Point& getTo() const override {return this->to;}
};


#endif //ADVANCEDTOPICS2_MOVE_H
