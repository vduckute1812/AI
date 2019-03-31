#ifndef MOVEMGR_H
#define MOVEMGR_H

#include <vector>
#include "Singleton.h"

class Move;

typedef std::vector<Move*> MoveCollection;

class MoveMgr: public Singleton<MoveMgr>
{
public:
    void        Do(Move*);
    void        Undo();

private:
    int                 m_moveIdx;
    MoveCollection      m_trackMoves;
};

#endif // MOVEMGR_H
