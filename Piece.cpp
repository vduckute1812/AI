#include "Piece.h"
#include "BoardUntils.h"

Piece::Piece(Alliance pieceAlliance, int position, PieceType pieceType, PieceValue pieceValue, QWidget *parent): QFrame(parent)
{
    m_isFirstMove = true;

    // Set attribute
    m_piecePosition = position;
    m_pieceAlliance = pieceAlliance;
    m_pieceType = pieceType;
    m_pieceValue = pieceValue;

    // Set image
    m_pieceImg = new QLabel(this);
    m_pieceImg->setPixmap(QPixmap(QString("Resources/") + QString(pieceType) + QString(pieceAlliance) + QString(".svg")));
    m_pieceImg->resize(QSize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE));
    m_pieceImg->setAlignment(Qt::AlignCenter);
    m_pieceImg->setAttribute(Qt::WA_DeleteOnClose);
    m_pieceImg->show();
}

Piece::~Piece()
{
    delete m_pieceImg;
}

PieceType Piece::getPieceType() const
{
    return m_pieceType;
}

PieceValue Piece::getPieceValue() const
{
    return m_pieceValue;
}

Alliance Piece::getAlliance() const
{
    return m_pieceAlliance;
}

void Piece::setPosition(int position)
{
    m_piecePosition = position;
}

int Piece::getPosition() const
{
    return m_piecePosition;
}

char Piece::getKeyCharacter() const
{
    return m_pieceType;
}

QLabel* Piece::getRenderImg() const
{
    return m_pieceImg;
}

bool Piece::isFirstMove() const
{
    return m_isFirstMove;
}

void Piece::setFirstMove(bool firstMove)
{
    m_isFirstMove = firstMove;
}
