#include "Move.h"
#include "BoardUI.h"
#include "MoveMgr.h"

MoveMgr* MoveMgr::s_instance = nullptr;

//////////////////////////////////////////////////////////////////////////

MoveMgr::MoveMgr()
{
    m_moveIdx = 0;
}

//////////////////////////////////////////////////////////////////////////

MoveMgr::~MoveMgr()
{
    for (unsigned int i = 0; i < m_trackMoves.size(); i++)
        delete m_trackMoves[i];

    m_trackMoves.resize(0);
    m_moveIdx = 0;
}

//////////////////////////////////////////////////////////////////////////

MoveMgr* MoveMgr::GetInstance()
{
    if (!s_instance)
        s_instance = new MoveMgr();

    return s_instance;
}

//////////////////////////////////////////////////////////////////////////


void MoveMgr::FreeInstance()
{
    delete s_instance;
    s_instance = nullptr;
}

//////////////////////////////////////////////////////////////////////////

void MoveMgr::Do(Move *move)
{
    if(!move)
        return;

    BoardUI::GetInstance()->Lock(true);
    BoardUI::GetInstance()->blockSignals(true);

    // remove pre-move
    unsigned int idx;
    for (idx = m_moveIdx; idx < m_trackMoves.size(); ++idx)
    {
        delete m_trackMoves[idx];
    }

    // after delete pre-move. Set size of available track
    m_trackMoves.resize(m_moveIdx);

    m_moveIdx++;

    move->Do();
    m_trackMoves.push_back(move);

    BoardUI::GetInstance()->Lock(false);
    BoardUI::GetInstance()->blockSignals(false);

}

bool MoveMgr::HasUndo()
{
    return m_moveIdx > 0;
}

void MoveMgr::Undo()
{
    if(HasUndo())
    {
        m_moveIdx--;
        m_trackMoves[m_moveIdx]->Undo();
    }
}

unsigned int MoveMgr::GetIndex() const
{
    return m_moveIdx;
}

