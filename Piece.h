#ifndef ADVANCEDTOPICS2_PIECE_H
#define ADVANCEDTOPICS2_PIECE_H
#include "Point.h"
#include "Game.h"
#include <vector>

//************************Semantic Parsing tools*******************************************
bool isNumInRange(char* str, int rangeStart, int rangeEnd);

bool isValidPieceType(char Piece);

bool isCharArrValidPieceType(char *c);

bool isValidJokerPieceType(char tool);

bool isCharArrValidJokerPieceType(char *c);

//*************************Piece Class********************************************************

enum pieceType {
    ROCK ,
    PAPER,
    SCISSORS,
    BOMB,
    FLAG,
    EMPTY,
};

pieceType charToPieceType(char c);

class Piece{
private:
    pieceType type;
    playerEnum player;
    bool joker;
    bool isPositioned;

public:
    Piece(pieceType _type, playerEnum _player, bool _joker, bool _isPositioned):
            type(_type),
            player(_player),
            joker(_joker),
            isPositioned(_isPositioned){}

    Piece(pieceType _type, playerEnum _player, bool _joker):
            type(_type),
            player(_player),
            joker(_joker),
            isPositioned(false){}

    virtual ~Piece() = default;
    pieceType getType() const {return this->type;}
    playerEnum getPlayer() const {return this->player;}
    virtual bool canMove() const = 0;
    virtual bool canMove(unique_ptr<Point>& source, unique_ptr<Point>& target) const = 0;
    bool isJoker() const {return this->joker;}
    virtual vector<pieceType> getWeakerPieces() const = 0;
    bool canCapture(Piece *other);
    executeCommandMessage setJoker(pieceType joker_new_rep){
        if(this->isJoker()){
            this->type = joker_new_rep;
            return EXECUTE_COMMAND_SUCCESS;
        }
        return EXECUTE_COMMAND_NOT_JOKER;
    }
    void placeTool(){this->isPositioned = true;}
    virtual void removeTool(){this->isPositioned = false;}
    bool IsPositioned() const {return this->isPositioned;}
    virtual char toChar() const = 0;
};

class ScissorsPiece : public Piece{
public:
    ScissorsPiece(playerEnum _player): Piece(SCISSORS, _player, false) {}

    bool canMove() const override {return true;}

    bool canMove(unique_ptr<Point>& source, unique_ptr<Point>& target) const override {
        int sourceRow = PointUtils::getRow(*source), sourceCol = PointUtils::getCol(*source),
                targetRow = PointUtils::getRow(*target), targetCol = PointUtils::getCol(*target);
        int vertical = abs(sourceRow - targetRow), horizonal = abs(sourceCol - targetCol);
        return (vertical && !horizonal) || (horizonal && !vertical);
    }
    vector<pieceType> getWeakerPieces() const override{
        vector<pieceType> weakerTools = {SCISSORS, PAPER, BOMB, FLAG, EMPTY};
        return weakerTools;
    }
    char toChar() const override{
        if(this->getPlayer() == PLAYER_1) {return 'S';}
        else{return 's';}
    }
};

class RockPiece : public Piece{
public:
    RockPiece(playerEnum _player): Piece(ROCK, _player, false) {}
    bool canMove() const override {return true;}
    bool canMove(unique_ptr<Point>& source, unique_ptr<Point>& target) const override {
        int sourceRow = PointUtils::getRow(*source), sourceCol = PointUtils::getCol(*source),
                targetRow = PointUtils::getRow(*target), targetCol = PointUtils::getCol(*target);
        int vertical = abs(sourceRow - targetRow), horizontal = abs(sourceCol - targetCol);
        return (vertical && !horizontal) || (horizontal && !vertical);
    }
    vector<pieceType> getWeakerPieces() const override{
        vector<pieceType> weakerTools = {ROCK, SCISSORS, BOMB, FLAG, EMPTY};
        return weakerTools;
    }
    char toChar() const override{
        if(this->getPlayer() == PLAYER_1) {return 'R';}
        else{return 'r';}
    }
};

class PaperPiece : public Piece{
public:
    PaperPiece(playerEnum _player): Piece(PAPER, _player, false) {}
    bool canMove() const override {return true;}
    bool canMove(unique_ptr<Point>& source, unique_ptr<Point>& target) const override {
        int sourceRow = PointUtils::getRow(*source), sourceCol = PointUtils::getCol(*source),
                targetRow = PointUtils::getRow(*target), targetCol = PointUtils::getCol(*target);
        int vertical = abs(sourceRow - targetRow), horizontal = abs(sourceCol - targetCol);
        return (vertical && !horizontal) || (horizontal && !vertical);
    }
    vector<pieceType> getWeakerPieces() const override{
        vector<pieceType> weakerTools = {PAPER, ROCK, BOMB, FLAG, EMPTY};
        return weakerTools;
    }
    char toChar() const override{
        if(this->getPlayer() == PLAYER_1) {return 'P';}
        else{return 'p';}
    }
};

class BombPiece : public Piece{
public:
    BombPiece(playerEnum _player): Piece(BOMB, _player, false) {}
    bool canMove() const override {return false;}
    bool canMove(unique_ptr<Point>& source, unique_ptr<Point>& target) const override {
        //mock check
        if(source->getX() ==0 && target->getX() ==0) return this->canMove();
        return this->canMove();
    }
    vector<pieceType> getWeakerPieces() const override{
        vector<pieceType> weakerTools = {PAPER, ROCK, SCISSORS, BOMB, FLAG, EMPTY};
        return weakerTools;
    }
    char toChar() const override{
        if(this->getPlayer() == PLAYER_1) {return 'B';}
        else{return 'b';}
    }
};

class FlagPiece : public Piece{
public:
    FlagPiece(playerEnum _player): Piece(FLAG, _player, false) {}
    bool canMove() const override {return false;}
    bool canMove(unique_ptr<Point>& source, unique_ptr<Point>& target) const override {
        //mock check
        if(source->getX()==0 && target->getX()==0) return this->canMove();
        return this->canMove();
    }
    vector<pieceType> getWeakerPieces() const override{
        vector<pieceType> weakerTools = {FLAG, EMPTY};
        return weakerTools;
    }
    char toChar() const override{
        if(this->getPlayer() == PLAYER_1) {return 'F';}
        else{return 'f';}
    }
};

class EmptyPiece : public Piece{
public:
    EmptyPiece(): Piece(EMPTY, NO_PLAYER, false, false) {}
    bool canMove() const override {return false;}
    bool canMove(unique_ptr<Point>& source, unique_ptr<Point>& target) const override {
        //mock check
        if(source->getX() ==0 && target->getX() ==0) return this->canMove();
        return this->canMove();
    }
    vector<pieceType> getWeakerPieces() const override {
        vector<pieceType> weakerTools = {EMPTY};
        return weakerTools;
    }
    void removeTool() override {}
    char toChar() const override{return ' ';}
};

class JokerPiece : public Piece{
public:
    JokerPiece(playerEnum _player): Piece(EMPTY, _player, true) {}
    bool canMove() const override {
        switch(this->getType()){
            case(SCISSORS):
                return (ScissorsPiece(NO_PLAYER).canMove());
            case(ROCK):
                return (RockPiece(NO_PLAYER).canMove());
            case(PAPER):
                return (PaperPiece(NO_PLAYER).canMove());
            case(BOMB):
                return (BombPiece(NO_PLAYER).canMove());
            default:
                return (EmptyPiece().canMove());
        }
    }
    bool canMove(unique_ptr<Point>& source, unique_ptr<Point>& target) const override {
        switch(this->getType()){
            case(SCISSORS):
                return (ScissorsPiece(NO_PLAYER).canMove(source, target));
            case(ROCK):
                return (RockPiece(NO_PLAYER).canMove(source, target));
            case(PAPER):
                return (PaperPiece(NO_PLAYER).canMove(source, target));
            case(BOMB):
                return (BombPiece(NO_PLAYER).canMove(source, target));
            default:
                return (EmptyPiece().canMove(source, target));
        }
    }
    vector<pieceType> getWeakerPieces() const override{
        switch(this->getType()){
            case(SCISSORS):
                return (ScissorsPiece(NO_PLAYER).getWeakerPieces());
            case(ROCK):
                return (RockPiece(NO_PLAYER).getWeakerPieces());
            case(PAPER):
                return (PaperPiece(NO_PLAYER).getWeakerPieces());
            case(BOMB):
                return (BombPiece(NO_PLAYER).getWeakerPieces());
            default:
                return (EmptyPiece().getWeakerPieces());
        }
    }
    char toChar() const override{
        if(this->getPlayer() == PLAYER_1) {return 'J';}
        else{return 'j';}
    }
};

#endif //ADVANCEDTOPICS2_PIECE_H
