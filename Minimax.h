#ifndef Minimax_H
#define Minimax_H

const static int MAX_QUIESCENCE = 5000;


class Move;
class Board;
class BoardEvaluator;
class Minimax
{
public:
    Minimax(int searchDepth);
    ~Minimax();

    int     getNumboardsEvaluated();

    Move*   execute(const Board*);

    double  min(const Board* board, int depth, double highest, double lowest);
    double  max(const Board* board, int depth, double highest, double lowest);

    bool    isEndgame(const Board* board);
    int     calculateQuiescenceDepth(const Move* moveTransition, int depth);

private:
    BoardEvaluator* m_boardEvaluator;
    int             m_boardEvaluated;
    int             m_searchDepth;
    double          m_executeTime;

    int             m_quiescenceCount;

};

#endif // Minimax_H
