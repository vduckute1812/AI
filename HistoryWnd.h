#ifndef HISTORYWND_H
#define HISTORYWND_H
#include "Singleton.h"
#include <QWidget>

class HistoryWnd: public QWidget, public Singleton<HistoryWnd>
{
    public:
        HistoryWnd(QWidget *parent = nullptr);
        virtual void Init() override;
    private:

};

#endif // HISTORYWND_H
