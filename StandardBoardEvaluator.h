#ifndef STANDARDBOARDEVALUATOR_H
#define STANDARDBOARDEVALUATOR_H

class Board;
class StandardBoardEvaluator
{
public:
    StandardBoardEvaluator();
private:
    int scorePlayer(const Board* board, int depth);
    static int pieceValue(const Board* board);
};

#endif // STANDARDBOARDEVALUATOR_H
