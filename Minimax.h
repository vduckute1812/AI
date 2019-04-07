#ifndef Minimax_H
#define Minimax_H

class Move;
class Board;
class BoardEvaluator;
class Minimax
{
public:
    Minimax();
    ~Minimax();

    int     getNumboardsEvaluated();

    Move*   execute(const Board*, int depth);

    double  min(const Board* board, int depth) const;
    double  max(const Board* board, int depth) const;

private:
    BoardEvaluator* m_boardEvaluator;
    double m_boardEvaluated;
    double m_executeTime;

};

#endif // Minimax_H
