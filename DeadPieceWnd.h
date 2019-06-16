#ifndef DEADPIECEWND_H
#define DEADPIECEWND_H
#include <QWidget>
#include <vector>
#include <QGridLayout>
#include <QVBoxLayout>
#include "Singleton.h"
#include "Piece.h"

class Tile;
class Piece;
class DeadPieceWnd: public Singleton<DeadPieceWnd>, public QWidget
{
public:
    virtual void            Init() override;
    DeadPieceWnd(QWidget* parent = nullptr);
    virtual ~DeadPieceWnd() override;

    void                AddDeadPiece(QChar, QChar);
    void                RemoveDeadPiece(QChar);

    void                Update();

private:
    QVBoxLayout*        m_parentLayout;
    QGridLayout*        m_gridWhiteDeadPiece;
    QGridLayout*        m_gridBlackDeadPiece;
    unsigned int        m_whiteIdx;
    unsigned int        m_blackIdx;

    std::vector<Tile*>       m_whiteTiles;
    std::vector<Tile*>       m_blackTiles;
    std::vector<QLabel*>        m_deadWhitePiece;
    std::vector<QLabel*>        m_deadBlackPiece;

};

#endif // DEADPIECEWND_H
