#ifndef PROMOTEWND_H
#define PROMOTEWND_H
#include <QWidget>
#include "Singleton.h"

class Tile;
class PromoteWnd: public QWidget, public Singleton<PromoteWnd>
{
public:
    PromoteWnd(QWidget* parent = nullptr);
    virtual void    Init() override;

private:
    std::vector<Tile*>       m_tiles;
};

#endif // PROMOTEWND_H
