#ifndef MINIMAX_H
#define MINIMAX_H
#include "Piece.h"
#include "Singleton.h"
#include "Defines.h"

const static int CHECK_BONUS = 50;
const static int CHECK_MATE_BONUS = 1000;
const static int DEPTH_BONUS = 100;
const static int MOBILITY_MULTIPLIER = 2;
const static int ATTACK_MULTIPLIER = 2;

class BoardEvaluator;
class Minimax: public Singleton<Minimax>
{
public:
    virtual void Init() override;

    Move*   execute(BoardConfig);

    double  min(BoardConfig board, u32 depth, double highest, double lowest);
    double  max(BoardConfig board, u32 depth, double highest, double lowest);

    bool    IsEndgame(BoardConfig board);
    int     CalculateQuiescenceDepth(const Move* moveTransition, int depth);
    void    SetDepth(u32 depth);
    bool    SortMoveFollowValue(std::vector<Move*> moves);

private:
    BoardEvaluator* m_boardEvaluator;
    unsigned int    m_boardEvaluated;
    unsigned int    m_searchDepth;
    double          m_executeTime;
    int             m_quiescenceCount;
};

class BoardEvaluator
{
public:
    BoardEvaluator();
    virtual ~BoardEvaluator();
    virtual int evaluate(const BoardConfig board, int depth = 0) = 0;
};

class StandardBoardEvaluator: public Singleton<StandardBoardEvaluator>, public BoardEvaluator
{
public:
    virtual void Init() override;
    virtual int evaluate(const BoardConfig board, int depth = 0) override;
private:
    int scorePlayer(const BoardConfig board, const Alliance alliance, int depth);
    int mobility(const BoardConfig board, const Alliance alliance);
    int mobilityRatio(const BoardConfig board, const Alliance alliance);
    int check(const BoardConfig board, const Alliance alliance);
    int kingThreats(const BoardConfig board, const Alliance alliance, int depth);
    int depthBonus(int depth);
    int pieceValue(const BoardConfig board, const Alliance alliance);
    int attacks(const BoardConfig board, const Alliance alliance);
};

#endif // MINIMAX_H
