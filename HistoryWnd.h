#ifndef HISTORYWND_H
#define HISTORYWND_H
#include "Singleton.h"
#include <QListWidget>

class HistoryWnd: public QListWidget, public Singleton<HistoryWnd>
{
    public:
        HistoryWnd(QWidget *parent = nullptr);
        virtual void            Init() override;
        void                    Update();

    protected:
        QIcon				m_entryIcon;

        int        m_cmdCount;
        int        m_cmdIdx;
};

#endif // HISTORYWND_H
