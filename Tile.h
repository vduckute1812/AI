#ifndef TILE_H
#define TILE_H
#include "map"

class Tile;
class Piece;

typedef std::map<int, Tile*> BoardTiles;

class Tile
{
public:
    Tile(const int coordinate, Piece* piece);
    ~Tile();

    bool            isTileOccupied() const;

    void            setPiece(Piece*);
    Piece*          getPiece() const;

    int             getCoordinate() const;

    static Tile*            GetEmptyTiles(const int indx);
    static BoardTiles       EMPTY_TILES;
    static const BoardTiles     createEmptyTiles();

protected:
    int         m_tileCoordinate;
    Piece*      m_piece;

};

#endif // TILE_H
