#ifndef BOARDEVALUATOR_H
#define BOARDEVALUATOR_H

class Board;

class BoardEvaluator
{
public:
    BoardEvaluator();
    virtual ~BoardEvaluator();
    virtual int evaluate(const Board* board, int depth) = 0;
};

#endif // BOARDEVALUATOR_H
