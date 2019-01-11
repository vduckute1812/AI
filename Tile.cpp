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
	m_defaultColor = (m_coordinate + (m_coordinate / BoardUntils::NUM_TILES_PER_ROW) % 2) % 2 ? ODD_COLOR : EVEN_COLOR;
	m_curretColor = m_defaultColor;
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
		QLabel* label = piece->getRenderImg();
		label->setParent(this);
		label->show();

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


void Tile::mousePressEvent(QMouseEvent *)
{
	int coordinate = this->getCoordinate();
	Piece* piece = BoardController::GetInstance()->getSelectedPiece();
    Player* currentPlayer =BoardController::GetInstance()->getCurrentController();
    if (piece  && BoardUntils::isSameAlliance(piece->getAlliance(), BoardController::GetInstance()->getMoveMaker()))
	{
		for (Move* move : piece->calculateLegalMove(BoardController::GetInstance()->getBoard()))
		{
            if (move->getDestCoordinate() == coordinate && !currentPlayer->checkLegalMove(move))
			{
				BoardController::GetInstance()->movePiece(move);
			}
			delete move;
		}
	}
	BoardController::GetInstance()->setSelectedPiece(this->getPiece());


	// Set colors
	resetColors();

	Piece* pieceColor = BoardController::GetInstance()->getSelectedPiece();
	if (pieceColor  && BoardUntils::isSameAlliance(pieceColor->getAlliance(), BoardController::GetInstance()->getMoveMaker()))
	{
        this->setCurrentColor(CHOOSE_COLOR);
		for (Move* move : pieceColor->calculateLegalMove(BoardController::GetInstance()->getBoard()))
		{
			Tile* tile = BoardController::GetInstance()->getBoard()->getTile(move->getDestCoordinate());
            if(!currentPlayer->checkLegalMove(move))
            {
                if (move->isAttack())
                {
                    tile->setCurrentColor(ATTACK_COLOR);
                }
                else
                {
                    tile->setCurrentColor(MOVE_COLOR);
                }
            }
			delete move;
		}

	}
}
void Tile::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setBrush(m_curretColor);
	painter.drawRect(rect());
}

void Tile::setCurrentColor(QBrush color)
{
	m_curretColor = color;
}

QBrush Tile::getCurrentColor()
{
	return m_curretColor;
}

QBrush Tile::getDefaultColor()
{
	return m_defaultColor;
}

void Tile::resetColors() const
{
	for (Tile* tile: BoardController::GetInstance()->getBoard()->getTiles())
	{
		tile->setCurrentColor(tile->getDefaultColor());
	}
}
