#pragma once
#include <QWidget>

class Piece;

class Tile : public QWidget
{
	Q_OBJECT

public:

	explicit Tile(int coordinate, QWidget* parent = nullptr);
	explicit Tile(int coordinate, Piece* piece, QWidget* parent = nullptr);

	~Tile();
	
	void		setPiece(Piece* piece);
	void		setOccupiedState(bool isOccupied = false);
	bool		isTileOccupied() const;
	Piece*		getPiece() const;
	int			getCoordinate();
	bool		isEmptyTile() const;

	void		mousePressEvent(QMouseEvent *) override;
	void		paintEvent(QPaintEvent *) override;
	void		timerEvent(QTimerEvent *e) override;


private:
	int			m_coordinate;
	Piece*		m_piece;
	bool		m_isOccupied;
};
