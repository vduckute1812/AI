#include "HistoryWnd.h"
#include "MainWnd.h"
#include <QString>
#include "Controller/Move.h"
#include "Controller/MoveMgr.h"

HistoryWnd::HistoryWnd(QWidget *parent/* = nullptr*/): QListWidget (parent)
{

}

void HistoryWnd::Init()
{
    m_entryIcon = MainWnd::LoadIcon("history");
    ListenTo(MoveMgr::GetInstance(), k_msgType, msg::HISTORY_UPDATE);
}

void HistoryWnd::Update()
{
    MoveMgr* mgr = MoveMgr::GetInstance();
    if (m_cmdCount == mgr->GetCount() && m_cmdIdx == mgr->GetIndex())
        return;

    m_cmdIdx = mgr->GetIndex();
    m_cmdCount = mgr->GetCount();

    clear();

    setWindowTitle(QString("History: " +  QString::number(m_cmdCount) + "commands"));

    int count = m_cmdCount;//Min(20, m_cmdCount);
    for (int i = count - 1; i >= 0; i--)
    {
        QListWidgetItem* item = new QListWidgetItem();

        Move* move = mgr->GetMove(i);
        QString name = move->GetDescription();
        item->setData(Qt::DisplayRole, name);
        QIcon icon = MainWnd::LoadIcon( QString(move->GetTypePieceMove()) + QString(move->GetAlliancePieceMove()) );
        item->setData(Qt::DecorationRole, icon);

        if (m_cmdIdx <= i)
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

        addItem(item);
    }
    repaint();
}

void HistoryWnd::OnMessageReceived(const Message &msg)
{
    if(msg.Is(msg::HISTORY_UPDATE))
    {
        Update();
    }
}
