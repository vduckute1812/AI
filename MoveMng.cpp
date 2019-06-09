#include "MoveMng.h"
#include "Move.h"
#include "BoardGameWnd.h"

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


// Use for generate board after move

void MoveMgr::Do(Move *move)
{
    if(!move || BoardGameWnd::GetInstance()->IsLocked())
        return;

    BoardGameWnd::GetInstance()->Lock(true);
    BoardGameWnd::GetInstance()->blockSignals(true);


    // remove pre-move
    unsigned int currentIndex =  m_moveIdx;
    for (; currentIndex < m_trackMoves.size(); ++currentIndex)
    {
        delete m_trackMoves[currentIndex];
    }

    // after delete pre-move. Set size of available track
    m_trackMoves.resize(m_moveIdx);

    m_moveIdx++;

    BoardState board = move->Execute();
    m_trackMoves.push_back(move);

    BoardGameWnd::GetInstance()->SetBoard(board);

    BoardGameWnd::GetInstance()->Lock(false);
    BoardGameWnd::GetInstance()->blockSignals(false);

}


// Undo and redo just use in GUI
bool MoveMgr::HasUndo()
{
    return m_moveIdx > 0;
}

void MoveMgr::Undo()
{
    if(BoardGameWnd::GetInstance()->IsLocked())
        return;

    BoardGameWnd::GetInstance()->Lock(true);
    BoardGameWnd::GetInstance()->blockSignals(true);

    if(HasUndo())
    {
        m_moveIdx--;
        unsigned int currentIdx = static_cast<unsigned int>(m_moveIdx);
        BoardState board = m_trackMoves[currentIdx]->Undo();
        BoardGameWnd::GetInstance()->SetBoard(board);
    }

    BoardGameWnd::GetInstance()->Lock(false);
    BoardGameWnd::GetInstance()->blockSignals(false);
}

bool MoveMgr::HasRedo()
{
    return m_moveIdx < m_trackMoves.size();
}

void MoveMgr::Redo()
{
    if(BoardGameWnd::GetInstance()->IsLocked())
        return;

    BoardGameWnd::GetInstance()->Lock(true);
    BoardGameWnd::GetInstance()->blockSignals(true);

    if(HasRedo())
    {
        unsigned int currentIdx = static_cast<unsigned int>(m_moveIdx);
        BoardState board = m_trackMoves[currentIdx]->Redo();
        BoardGameWnd::GetInstance()->SetBoard(board);
        m_moveIdx++;
    }

    BoardGameWnd::GetInstance()->Lock(false);
    BoardGameWnd::GetInstance()->blockSignals(false);
}


unsigned int MoveMgr::GetIndex() const
{
    return m_moveIdx;
}
