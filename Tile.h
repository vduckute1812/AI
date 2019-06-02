#ifndef TILE_H
#define TILE_H
#include <QWidget>

class Piece;
class Tile : public QWidget
{
public:
    explicit Tile(const int coordinate, Piece* piece = nullptr, QWidget* parrent = nullptr);

    int     GetCoordinate();
    bool    HasPieceOnTile();
    Piece*  GetPiece();

    void    mousePressEvent(QMouseEvent *) override;

protected:
    int         m_tileCoordinate;
    QBrush      m_currentColor;
    QBrush      m_defaultColor;
    Piece*      m_piece;
};

#endif // TILE_H
