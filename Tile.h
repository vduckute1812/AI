#ifndef TILE_H
#define TILE_H
#include <QWidget>

class Tile;
class Piece;
typedef std::vector<Tile*> BoardTiles;

static const QBrush ODD_COLOR   ("white");
static const QBrush EVEN_COLOR  ("brown");
static const QBrush MOVE_COLOR	("gray");
static const QBrush ATTACK_COLOR(QColor(255, 100, 0 , 200));    // orangle
static const QBrush CHOOSE_COLOR("yellow");


class Tile : public QWidget
{
public:
    explicit Tile(unsigned int coordinate, Piece* piece = nullptr, QWidget* parrent = nullptr);

    void            SetPiece(Piece*);
    Piece*          GetPiece();

    unsigned int    GetCoordinate();
    bool            HasPieceOnTile();

    void            SetCurrentColor(QBrush color);
    QBrush          GetDefaultColor() const;

    void            mousePressEvent(QMouseEvent *) override;
    void            paintEvent(QPaintEvent *) override;

    void            SetCanTouch(bool yes);
    bool            CanTouch() const;

private:
    const unsigned int  m_tileCoordinate;
    QBrush              m_currentColor;
    QBrush              m_defaultColor;

    Piece*              m_piece;
    bool                m_canTouch;
};

#endif // TILE_H
