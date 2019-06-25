#ifndef PROMOTEWND_H
#define PROMOTEWND_H
#include <QMainWindow>
#include "Singleton.h"
#include "Piece.h"
#include "Messenger.h"

class Tile;
class PromoteWnd: public QMainWindow, public Singleton<PromoteWnd>, public Messenger
{

public:
    enum TypeMessage
    {
        k_msgType		= 1 << 3
    };
    PromoteWnd (QWidget* parent = nullptr);
    virtual void    Init() override;
    void            SetPromoteAlliance(Alliance alliance);

    void            SetPromote(bool yes);
    bool            IsPromote() const;

    void            AddPromotePiece(Piece*);
    void            AddDefaultPromotePiece();

    void            DeletePromotePiece();
    Piece*          GetPromotePiece() const;

    void            SetVisible(bool yes);

private:
    bool                    m_isPromote;
    Alliance                m_promoteAlliance;
    std::vector<Tile*>      m_tiles;
    std::vector<Piece*>     m_whitePieces;
    std::vector<Piece*>     m_blackPieces;

    std::vector<Piece*>     m_promotePieces;

};

#endif // PROMOTEWND_H
