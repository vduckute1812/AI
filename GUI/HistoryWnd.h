#ifndef HISTORYWND_H
#define HISTORYWND_H
#include <QListWidget>
#include "Singleton.h"
#include "Messenger.h"

class HistoryWnd: public QListWidget, public Singleton<HistoryWnd>, public Messenger
{
    public:
    enum TypeMessage
    {
        k_msgType		= 1 << 2
    };
        HistoryWnd(QWidget *parent = nullptr);
        virtual void            Init() override;
        void                    Update();

        virtual void        OnMessageReceived(const Message& msg) override;

    protected:
        QIcon           m_entryIcon;

        int             m_cmdCount;
        int             m_cmdIdx;
};

#endif // HISTORYWND_H
