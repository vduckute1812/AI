#ifndef PROMOTEWND_H
#define PROMOTEWND_H
#include <QMainWindow>
#include "Singleton.h"
#include "Piece.h"

class Tile;
class PromoteWnd: public QMainWindow, public Singleton<PromoteWnd>
{
    Q_OBJECT
public:
    PromoteWnd (QWidget* parent = nullptr);
    virtual void    Init() override;
    void            SetPromoteAlliance(Alliance alliance);

    void            SetPromote(bool yes);
    bool            IsPromote() const;

private:
    bool                    m_isPromote;
    Alliance                m_promoteAlliance;
    std::vector<Tile*>      m_tiles;
    std::vector<Piece*>     m_pieceWhite;
    std::vector<Piece*>     m_pieceBlack;

};

#endif // PROMOTEWND_H
