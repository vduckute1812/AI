#ifndef PROMOTEWND_H
#define PROMOTEWND_H
#include <QDialog>
#include "Singleton.h"
#include "Messenger.h"
#include "Piece/Piece.h"

class Tile;
class PromoteWnd: public QDialog, public Singleton<PromoteWnd>, public Messenger
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

    void            SetPromotePiece(Piece* piece);
    Piece*          GetPromotePiece() const;

    void            SetVisible(bool yes);

private:
    bool                    m_isPromote;
    Alliance                m_promoteAlliance;
    std::vector<Tile*>      m_tiles;
    std::vector<Piece*>     m_whitePieces;
    std::vector<Piece*>     m_blackPieces;

    Piece*                  m_promotePiece;
};

#endif // PROMOTEWND_H
