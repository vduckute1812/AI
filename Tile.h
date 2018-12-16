#pragma once

class Piece;

class Tile
{
public:

	explicit Tile(int coordinate);
	explicit Tile(int coordinate, Piece* piece);

	~Tile();
	
	void		setPiece(Piece* piece);
	void		setOccupiedState(bool isOccupied = false);
	bool		isTileOccupied() const;
	Piece*		getPiece() const;
	int			getCoordinate();
	bool		isEmptyTile() const;

private:
	int			m_coordinate;
	Piece*		m_piece;
	bool		m_isOccupied;
};
