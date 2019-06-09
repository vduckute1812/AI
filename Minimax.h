#ifndef MINIMAX_H
#define MINIMAX_H
#include "Singleton.h"

class BoardEvaluator;
class Minimax: public Singleton<Minimax>
{
public:
    virtual void Init() override;

private:
    BoardEvaluator* boardEluvator;
};

class BoardState;
class BoardEvaluator: public Singleton<BoardEvaluator>
{
public:
    virtual void Init() override;
    virtual int evaluate(BoardState board, int depth = 0) = 0;
};

class StandardBoard

#endif // MINIMAX_H
