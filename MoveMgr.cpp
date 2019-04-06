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
    unsigned int currentIndex =  static_cast<unsigned int>(m_moveIdx);
    for (; currentIndex < m_trackMoves.size(); ++currentIndex)
    {
        delete m_trackMoves[currentIndex];
    }

    // after delete pre-move. Set size of available track
    m_trackMoves.resize(static_cast<unsigned int>(m_moveIdx));

    m_moveIdx++;

    Board* board = move->Do();
    m_trackMoves.push_back(move);

    BoardUI::GetInstance()->SetBoard(board);

    BoardUI::GetInstance()->Lock(false);
    BoardUI::GetInstance()->blockSignals(false);

}

bool MoveMgr::HasUndo()
{
    return m_moveIdx > 0;
}

void MoveMgr::Undo()
{
    BoardUI::GetInstance()->Lock(true);
    BoardUI::GetInstance()->blockSignals(true);

    if(HasUndo())
    {
        m_moveIdx--;
        unsigned int currentIdx = static_cast<unsigned int>(m_moveIdx);
        Board* board = m_trackMoves[currentIdx]->Undo();
        BoardUI::GetInstance()->SetBoard(board);
    }

    BoardUI::GetInstance()->Lock(false);
    BoardUI::GetInstance()->blockSignals(false);
}

bool MoveMgr::HasRedo()
{
    return m_moveIdx < static_cast<int>(m_trackMoves.size());
}

void MoveMgr::Redo()
{
    BoardUI::GetInstance()->Lock(true);
    BoardUI::GetInstance()->blockSignals(true);

    if(HasRedo())
    {
        unsigned int currentIdx = static_cast<unsigned int>(m_moveIdx);
        Board* board = m_trackMoves[currentIdx]->Do();
        BoardUI::GetInstance()->SetBoard(board);
        m_moveIdx++;
    }

    BoardUI::GetInstance()->Lock(false);
    BoardUI::GetInstance()->blockSignals(false);
}

int MoveMgr::GetIndex() const
{
    return m_moveIdx;
}

