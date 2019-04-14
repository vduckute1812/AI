#ifndef STANDARDBOARDEVALUATOR_H
#define STANDARDBOARDEVALUATOR_H
#include "Piece.h"
#include "BoardEvaluator.h"

class Board;

class StandardBoardEvaluator: public BoardEvaluator
{
public:
    StandardBoardEvaluator();
    virtual int evaluate(const Board* board, int depth);

private:
    static int scorePlayer(const Board* board, const Alliance alliance, int depth);
    static int mobility(const Board* board, const Alliance alliance);
    static int mobilityRatio(const Board* board, const Alliance alliance);
    static int check(const Board* board, const Alliance alliance);
    static int kingThreats(const Board* board, const Alliance alliance, int depth);
    static int depthBonus(int depth);
    static int pieceValue(const Board* board, const Alliance alliance);
    static int attacks(const Board* board, const Alliance alliance);

    const static int CHECK_BONUS = 50;
    const static int CHECK_MATE_BONUS = 1000;
    const static int DEPTH_BONUS = 100;
    const static int MOBILITY_MULTIPLIER = 2;
    const static int ATTACK_MULTIPLIER = 2;
};

#endif // STANDARDBOARDEVALUATOR_H
