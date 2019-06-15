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

    Move*   execute(BoardState);

    double  min(BoardState board, u32 depth, double highest, double lowest);
    double  max(BoardState board, u32 depth, double highest, double lowest);

    bool    IsEndgame(BoardState board);
    int     CalculateQuiescenceDepth(const Move* moveTransition, int depth);
    void    SetDepth(int depth);
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
    virtual int evaluate(const BoardState board, int depth = 0) = 0;
};

class StandardBoardEvaluator: public Singleton<StandardBoardEvaluator>, public BoardEvaluator
{
public:
    virtual void Init() override;
    virtual int evaluate(const BoardState board, int depth = 0) override;
private:
    int scorePlayer(const BoardState board, const Alliance alliance, int depth);
    int mobility(const BoardState board, const Alliance alliance);
    int mobilityRatio(const BoardState board, const Alliance alliance);
    int check(const BoardState board, const Alliance alliance);
    int kingThreats(const BoardState board, const Alliance alliance, int depth);
    int depthBonus(int depth);
    int pieceValue(const BoardState board, const Alliance alliance);
    int attacks(const BoardState board, const Alliance alliance);
};

#endif // MINIMAX_H
