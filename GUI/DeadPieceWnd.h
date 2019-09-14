#ifndef DEADPIECEWND_H
#define DEADPIECEWND_H
#include <QWidget>
#include <vector>
#include <QGridLayout>
#include <QVBoxLayout>
#include "Singleton.h"
#include "Messenger.h"
#include "Piece/Piece.h"


class Tile;
class Piece;
class DeadPieceWnd: public QWidget, public Singleton<DeadPieceWnd>, public Messenger
{

public:
    enum TypeMessage
    {
        k_msgType		= 1 << 1
    };

    virtual void            Init() override;
    DeadPieceWnd(QWidget* parent = nullptr);
    virtual ~DeadPieceWnd() override;

    void                AddDeadPiece(QChar, QChar);
    void                RemoveDeadPiece(QChar);

//    void                Update();

    virtual void        OnMessageReceived(const Message& msg) override;

private:
    QVBoxLayout*        m_parentLayout;
    QGridLayout*        m_gridWhiteDeadPiece;
    QGridLayout*        m_gridBlackDeadPiece;
    unsigned int        m_whiteIdx;
    unsigned int        m_blackIdx;

    std::vector<Tile*>          m_whiteTiles;
    std::vector<Tile*>          m_blackTiles;
    std::vector<QLabel*>        m_deadWhitePiece;
    std::vector<QLabel*>        m_deadBlackPiece;

};

#endif // DEADPIECEWND_H
