#ifndef MOVEMNG_H
#define MOVEMNG_H

#include <vector>
#include "Singleton.h"

class Move;

typedef std::vector<Move*> MoveCollection;

class MoveMgr
{

public:
    MoveMgr();
    ~MoveMgr();

    void                Do(Move* move);

    bool                HasUndo();
    void                Undo();

    bool                HasRedo();
    void                Redo();

    int                 GetIndex() const;
    static MoveMgr*     GetInstance();
    static void         FreeInstance();


private:
    static MoveMgr*     s_instance;

    int                 m_moveIdx;
    MoveCollection      m_trackMoves;
};

#endif // MOVEMNG_H
