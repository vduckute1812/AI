#ifndef Minimax_H
#define Minimax_H

class Move;
class Board;
class BoardEvaluator;
class Minimax
{
public:
    Minimax(int searchDepth);
    ~Minimax();

    int     getNumboardsEvaluated();

    Move*   execute(const Board*, int depth);

    double  min(const Board* board, int depth);
    double  max(const Board* board, int depth);

    bool    isEndgame(const Board* board);

private:
    BoardEvaluator* m_boardEvaluator;
    int             m_boardEvaluated;
    int             m_searchDepth;
    double          m_executeTime;

};

#endif // Minimax_H
