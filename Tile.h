#pragma once
#include <QWidget>
#include <QBrush>

static const QBrush ODD_COLOR("white");
static const QBrush EVEN_COLOR("brown");
static const QBrush MOVE_COLOR	(QColor(150,150,150,100));
static const QBrush ATTACK_COLOR(QColor(150,0,0,50));
static const QBrush CHOOSE_COLOR(QColor(150,150,0,100));

class Piece;

class Tile : public QWidget
{

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

	void		setCurrentColor(QBrush);
	QBrush		getCurrentColor();

	QBrush		getDefaultColor();

	void		resetColors() const;


private:
	int			m_coordinate;
	Piece*		m_piece;

	QBrush		m_defaultColor;
	QBrush		m_curretColor;

	bool		m_isOccupied;
};
