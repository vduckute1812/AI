#ifndef Minimax_H
#define Minimax_H
#include "Singleton.h"
#include "Move.h"
#include <vector>

const static int MAX_QUIESCENCE = 5000;

typedef std::vector<int> EVALUATE_TABLE;

class Move;
class Board;
class BoardEvaluator;
class Minimax: public Singleton<Minimax>
{
public:
    Minimax();
    ~Minimax();

    int     getNumboardsEvaluated();

    Move*   execute(const Board*);

    double  min(const Board* board, int depth, double highest, double lowest);
    double  max(const Board* board, int depth, double highest, double lowest);

    bool    isEndgame(const Board* board);
    int     calculateQuiescenceDepth(const Move* moveTransition, int depth);

    void    setDepth(int depth);

    bool    sortMoveFollowValue(std::vector<Move*> moves);

private:
    BoardEvaluator* m_boardEvaluator;
    int             m_boardEvaluated;
    int             m_searchDepth;
    double          m_executeTime;

    int             m_quiescenceCount;
    EVALUATE_TABLE  m_table;
};

#endif // Minimax_H
