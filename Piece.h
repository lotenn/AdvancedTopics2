////
//// Created by loten on 20/04/2018.
////
//
//#ifndef ADVANCEDTOPICS2_PIECE_H
//#define ADVANCEDTOPICS2_PIECE_H
//#include "Point.h"
//#include <vector>
//
//
//enum pieceType {
//    ROCK ,
//    PAPER,
//    SCISSORS,
//    BOMB,
//    FLAG,
//    EMPTY,
//};
//
//pieceType charToPieceType(char c);
//
//class Piece{
//private:
//    pieceType type;
//    playerEnum player;
//    bool joker;
//    bool isPositioned;
//
//public:
//    Piece(pieceType _type, playerEnum _player, bool _joker, bool _isPositioned):
//            type(_type),
//            player(_player),
//            joker(_joker),
//            isPositioned(_isPositioned){}
//
//    Piece(pieceType _type, playerEnum _player, bool _joker):
//            type(_type),
//            player(_player),
//            joker(_joker),
//            isPositioned(false){}
//
//    virtual ~Piece() = default;
//    pieceType getType() const {return this->type;}
//    playerEnum getPlayer() const {return this->player;}
//    virtual bool canMove() const = 0;
//    virtual bool canMove(Point source, Point target) const = 0;
//    bool isJoker() const {return this->joker;}
//    virtual vector<pieceType> getWeakerTools() const = 0;
//    bool canCapture(Piece *other);
//    executeCommandMessage setJoker(pieceType joker_new_rep){
//        if(this->isJoker()){
//            this->type = joker_new_rep;
//            return EXECUTE_COMMAND_SUCCESS;
//        }
//        return EXECUTE_COMMAND_NOT_JOKER;
//    }
//    void placeTool(){this->isPositioned = true;}
//    virtual void removeTool(){this->isPositioned = false;}
//    bool IsPositioned() const {return this->isPositioned;}
//    virtual char toChar() const = 0;
//};
//
//class ScissorsTool : public Piece{
//public:
//    ScissorsTool(playerEnum _player): Piece(SCISSORS, _player, false) {}
//    bool canMove() const override {return true;}
//    bool canMove(Point source, Point target) const override {
//        int sourceRow = getRow(source), sourceCol = getCol(source),
//                targetRow = getRow(target), targetCol = getCol(target);
//        int vertical = abs(sourceRow - targetRow), horizonal = abs(sourceCol - targetCol);
//        return (vertical && !horizonal) || (horizonal && !vertical);
//    }
//    vector<pieceType> getWeakerTools() const override{
//        vector<pieceType> weakerTools = {SCISSORS, PAPER, BOMB, FLAG, EMPTY};
//        return weakerTools;
//    }
//    char toChar() const override{
//        if(this->getPlayer() == PLAYER_1) {return 'S';}
//        else{return 's';}
//    }
//};
//
//class RockTool : public Piece{
//public:
//    RockTool(playerEnum _player): Piece(ROCK, _player, false) {}
//    bool canMove() const override {return true;}
//    bool canMove(Point source, Point target) const override {
//        int sourceRow = getRow(source), sourceCol = getCol(source),
//                targetRow = getRow(target), targetCol = getCol(target);
//        int vertical = abs(sourceRow - targetRow), horizonal = abs(sourceCol - targetCol);
//        return (vertical && !horizonal) || (horizonal && !vertical);
//    }
//    vector<pieceType> getWeakerTools() const override{
//        vector<pieceType> weakerTools = {ROCK, SCISSORS, BOMB, FLAG, EMPTY};
//        return weakerTools;
//    }
//    char toChar() const override{
//        if(this->getPlayer() == PLAYER_1) {return 'R';}
//        else{return 'r';}
//    }
//};
//
//class PaperTool : public Piece{
//public:
//    PaperTool(playerEnum _player): Piece(PAPER, _player, false) {}
//    bool canMove() const override {return true;}
//    bool canMove(Point source, Point target) const override {
//        int sourceRow = getRow(source), sourceCol = getCol(source),
//                targetRow = getRow(target), targetCol = getCol(target);
//        int vertical = abs(sourceRow - targetRow), horizonal = abs(sourceCol - targetCol);
//        return (vertical && !horizonal) || (horizonal && !vertical);
//    }
//    vector<pieceType> getWeakerTools() const override{
//        vector<pieceType> weakerTools = {PAPER, ROCK, BOMB, FLAG, EMPTY};
//        return weakerTools;
//    }
//    char toChar() const override{
//        if(this->getPlayer() == PLAYER_1) {return 'P';}
//        else{return 'p';}
//    }
//};
//
//class BombTool : public Piece{
//public:
//    BombTool(playerEnum _player): Piece(BOMB, _player, false) {}
//    bool canMove() const override {return false;}
//    bool canMove(Point source, Point target) const override {
//        if(source.x ==0 && target.x ==0) return this->canMove();
//        return this->canMove();
//    }
//    vector<pieceType> getWeakerTools() const override{
//        vector<pieceType> weakerTools = {PAPER, ROCK, SCISSORS, BOMB, FLAG, EMPTY};
//        return weakerTools;
//    }
//    char toChar() const override{
//        if(this->getPlayer() == PLAYER_1) {return 'B';}
//        else{return 'b';}
//    }
//};
//
//class FlagTool : public Piece{
//public:
//    FlagTool(playerEnum _player): Piece(FLAG, _player, false) {}
//    bool canMove() const override {return false;}
//    bool canMove(Point source, Point target) const override {
//        if(source.x ==0 && target.x ==0) return this->canMove();
//        return this->canMove();
//    }
//    vector<pieceType> getWeakerTools() const override{
//        vector<pieceType> weakerTools = {FLAG, EMPTY};
//        return weakerTools;
//    }
//    char toChar() const override{
//        if(this->getPlayer() == PLAYER_1) {return 'F';}
//        else{return 'f';}
//    }
//};
//
//class EmptyTool : public Piece{
//public:
//    EmptyTool(playerEnum _player): Piece(EMPTY, _player, false, false) {}
//    bool canMove() const override {return false;}
//    bool canMove(Point source, Point target) const override {
//        if(source.x ==0 && target.x ==0) return this->canMove();
//        return this->canMove();
//    }
//    vector<pieceType> getWeakerTools() const override {
//        vector<pieceType> weakerTools = {EMPTY};
//        return weakerTools;
//    }
//    void removeTool() override {}
//    char toChar() const override{return ' ';}
//};
//
//class JokerTool : public Piece{
//public:
//    JokerTool(playerEnum _player): Piece(EMPTY, _player, true) {}
//    bool canMove() const override {
//        switch(this->getType()){
//            case(SCISSORS):
//                return (ScissorsTool(NO_PLAYER).canMove());
//            case(ROCK):
//                return (RockTool(NO_PLAYER).canMove());
//            case(PAPER):
//                return (PaperTool(NO_PLAYER).canMove());
//            case(BOMB):
//                return (BombTool(NO_PLAYER).canMove());
//            default:
//                return (EmptyTool(NO_PLAYER).canMove());
//        }
//    }
//    bool canMove(Point source, Point target) const override {
//        switch(this->getType()){
//            case(SCISSORS):
//                return (ScissorsTool(NO_PLAYER).canMove(source, target));
//            case(ROCK):
//                return (RockTool(NO_PLAYER).canMove(source, target));
//            case(PAPER):
//                return (PaperTool(NO_PLAYER).canMove(source, target));
//            case(BOMB):
//                return (BombTool(NO_PLAYER).canMove(source, target));
//            default:
//                return (EmptyTool(NO_PLAYER).canMove(source, target));
//        }
//    }
//    vector<pieceType> getWeakerTools() const override{
//        switch(this->getType()){
//            case(SCISSORS):
//                return (ScissorsTool(NO_PLAYER).getWeakerTools());
//            case(ROCK):
//                return (RockTool(NO_PLAYER).getWeakerTools());
//            case(PAPER):
//                return (PaperTool(NO_PLAYER).getWeakerTools());
//            case(BOMB):
//                return (BombTool(NO_PLAYER).getWeakerTools());
//            default:
//                return (EmptyTool(NO_PLAYER).getWeakerTools());
//        }
//    }
//    char toChar() const override{
//        if(this->getPlayer() == PLAYER_1) {return 'J';}
//        else{return 'j';}
//    }
//};
//
//
//
//#endif //ADVANCEDTOPICS2_PIECE_H
