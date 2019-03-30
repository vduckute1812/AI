#ifndef TILE_H
#define TILE_H
#include <map>
#include <QBrush>
#include <QWidget>

class Tile;
class Piece;

typedef std::map<int, Tile*> BoardTiles;

static const QBrush ODD_COLOR   ("white");
static const QBrush EVEN_COLOR  ("brown");
static const QBrush MOVE_COLOR	("gray");
static const QBrush ATTACK_COLOR("darkRed");
static const QBrush CHOOSE_COLOR("yellow");

class Tile: public QWidget
{
public:
    Tile(const int coordinate, Piece* piece);
    ~Tile();

    bool            isTileOccupied() const;

    void            setPiece(Piece*);
    Piece*          getPiece() const;

    int             getCoordinate() const;

protected:

    int         m_tileCoordinate;
    Piece*      m_piece;
};

#endif // TILE_H
namespace TILES
{
    BoardTiles   createEmptyTiles();
}
