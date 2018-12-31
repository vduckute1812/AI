#include "Pawn.h"
#include "Piece.h"
#include "BoardUntils.h"
#include <QPainter>
#include <QtWidgets>

Piece::Piece(int piecePos, Alliance pieceAlliance, PieceType type, QWidget *parent) :QFrame(parent)
{
	m_piecePosition = piecePos;
	m_pieceAlliance = pieceAlliance;
	m_pieceType		= type;
	m_isDestroy		= false;

	m_icon = new QLabel(this);
	m_icon->setPixmap(QPixmap(QString("Resources/") + QString(type) + QString(pieceAlliance) + QString(".svg")));
	m_icon->resize(QSize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE));
	m_icon->setAlignment(Qt::AlignCenter);
	m_icon->setAttribute(Qt::WA_DeleteOnClose);

	hashCodeKeyValue();
}

Piece::~Piece()
{
}

void Piece::setPosition(int position)
{
	m_piecePosition = position;
}

int Piece::getPosistion() const
{
	return m_piecePosition;
}

Alliance Piece::getAlliance() const
{
	return m_pieceAlliance;
}

PieceType Piece::getPieceType() const
{
	return m_pieceType;
}

char Piece::getKeyCharacter() const
{
	return m_pieceType;
}

void Piece::hashCodeKeyValue()
{

	std::hash<char> hash_fn;

	const int prime = 31;
	int result = static_cast<int>(hash_fn(m_pieceType));

	result = prime * result + static_cast<int>(hash_fn(m_pieceAlliance));
	result = prime * result + m_piecePosition;

	if (m_pieceType == PieceType::PAWN)
	{
		Pawn* pawn = static_cast<Pawn*> (this);
		result = prime * result + (pawn->isFirstMove() ? 1: 0);
	}

	m_hashCode = result;
}

int  Piece::getHash() const
{
	return m_hashCode;
}

QLabel*	Piece::getRenderImg()
{
	return m_icon;
}

void Piece::diedState(bool yes)
{
	m_isDestroy = yes;
}

bool Piece::isDestroy()
{
	return m_isDestroy;
}
