#include "Move.h"
#include "Tile.h"
#include "Board.h"
#include "Piece.h"
#include <QPainter>
#include <QMouseEvent>
#include "BoardUntils.h"
#include "BoardController.h"

Tile::Tile(int coordinate, QWidget* parent) :QWidget(parent)
{
	m_coordinate = coordinate;
	m_isOccupied = false;
	resize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE);
	startTimer(50);
}

Tile::Tile(int coordinate, Piece* piece, QWidget* parent) : QWidget(parent)
{
	m_coordinate = coordinate;
	m_piece = piece;
	m_isOccupied = true;
	(coordinate + (coordinate / BoardUntils::NUM_TILES_PER_ROW) % 2) % 2 ? setStyleSheet("background-color:rgb(100,0,0);") : setStyleSheet("background-color:rgb(0,100,0);");
	resize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE);
}

Tile::~Tile()
{
	if (m_isOccupied)
	{
		delete m_piece;
	}
}

void Tile::setPiece(Piece* piece)
{
	m_piece = piece;
	if (piece)
	{
		piece->setParent(this);
		piece->setPosition(m_coordinate);

		m_isOccupied = true;
	}
	else
	{
		m_isOccupied = false;
	}
}

void Tile::setOccupiedState(bool isOccupied)
{
	m_isOccupied = isOccupied;
}

Piece* Tile::getPiece() const
{
	return m_piece;
}

bool Tile::isTileOccupied() const
{
	return m_isOccupied;
}

int Tile::getCoordinate()
{
	return m_coordinate;
}

bool Tile::isEmptyTile() const
{
	if (m_piece)
	{
		return false;
	}
	return true;
}


void Tile::mousePressEvent(QMouseEvent *event)
{
	int coordinate = this->getCoordinate();
	Piece* piece = BoardController::GetInstance()->getSelectedPiece();
	if (piece)
	{
		for (Move* move : piece->calculateLegalMove(BoardController::GetInstance()->getBoard()))
			if (move->getDestCoordinate() == coordinate)
			{
				BoardController::GetInstance()->movePiece(move);
			}
		BoardController::GetInstance()->setSelectedPiece(nullptr);
	}
	else
	{
		BoardController::GetInstance()->setSelectedPiece(this->getPiece());
	}
}

void Tile::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	(m_coordinate + (m_coordinate / BoardUntils::NUM_TILES_PER_ROW) % 2) % 2 ? painter.setBrush(QBrush("red")) : painter.setBrush(QBrush("green"));
	painter.drawRect(rect());

	Piece* piece = BoardController::GetInstance()->getSelectedPiece();
	if (piece)
	{
		for (Move* move : piece->calculateLegalMove(BoardController::GetInstance()->getBoard()))
		{
			Tile* tile = BoardController::GetInstance()->getBoard()->getTile(move->getDestCoordinate());
			QPainter painter(tile);
			painter.setBrush(QBrush("yellow"));
			painter.drawRect(tile->rect());
		}
	}
}

void Tile::timerEvent(QTimerEvent *e) {
	Q_UNUSED(e);
	repaint();
}