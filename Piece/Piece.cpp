#include "Piece.h"
#include "Defines.h"
#include "BoardUntils.h"
#include <QFileInfo>
#include "GUI/Tile.h"
#include "GUI/BoardGameWnd.h"

Piece::Piece(Alliance pieceAlliance, PieceType pieceType, PieceValue pieceValue, QWidget *parent, unsigned int position): QFrame(parent)
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
    m_pieceImg->resize(QSize(TILE_ROW_SIZE, TILE_COL_SIZE));
    m_pieceImg->setAlignment(Qt::AlignCenter);
    m_pieceImg->setAttribute(Qt::WA_DeleteOnClose);
    m_pieceImg->show();
}

Piece::~Piece()
{
    delete m_pieceImg;
    m_pieceImg = nullptr;
}

int Piece::locationBonus() const
{
    int score = 0;
    return score;
}

PieceType Piece::GetPieceType() const
{
    return m_pieceType;
}

PieceValue Piece::GetPieceValue() const
{
    return m_pieceValue;
}

Alliance Piece::GetAlliance() const
{
    return m_pieceAlliance;
}

void Piece::SetPosition(unsigned int position)
{
    m_piecePosition = position;
}

unsigned int Piece::GetPosition() const
{
    return m_piecePosition;
}

char Piece::GetKeyCharacter() const
{
    return m_pieceType;
}

void Piece::SetVisible(bool isVisible, Tile* tile)
{
    if(tile)
    {
        m_pieceImg->setParent(tile);
    }

    if(m_pieceImg)     // this piece hasn't been detroyed
    {
        isVisible ? m_pieceImg->show(): m_pieceImg->hide();
    }
}

bool Piece::IsFirstMove() const
{
    return m_isFirstMove;
}

void Piece::SetFirstMove(bool firstMove)
{
    m_isFirstMove = firstMove;
}

//bool BoardState::IsTileOccupied(BoardState boarValue, unsigned int position)
//{
//    BoardConfig::iterator piecePtr;
//    for (piecePtr = boarValue.m_boardValue.begin(); piecePtr != boarValue.m_boardValue.end(); ++piecePtr)
//    {
//        if(piecePtr->first == position && piecePtr->second != nullptr)
//        {
//            return true;
//        }
//    }
//    return false;
//}

//Piece* BoardState::GetPieceOnBoard(BoardState boardValue, unsigned int position)
//{
//    return boardValue.m_boardValue[position].second;
//}

//void BoardState::SetPiece(unsigned int position, Piece *piece)
//{
//    BoardConfig::iterator piecePtr;

//    for (piecePtr = m_boardValue.begin(); piecePtr != m_boardValue.end(); ++piecePtr)
//    {
//        if(piecePtr->first == position)
//        {
//            piecePtr->second = piece;
//        }
//    }
//    if(piece!=nullptr)
//    {
//        piece->SetPosition(position);
//    }
//}

//MoveCollection BoardState::GetMoveCollection(Alliance player)
//{
//    MoveCollection moveCollection;
//    BoardConfig::iterator piecePtr = m_boardValue.begin();
//    for (; piecePtr != m_boardValue.end(); ++piecePtr)
//    {
//        Piece* piece = piecePtr->second;
//        if(piece != nullptr && BoardUntils::IsSameAlliance(piece->GetAlliance(), player))
//        {
//            for (Move* move: piece->calculateLegalMove(*this))
//            {
//                moveCollection.push_back(move);
//            }
//        }
//    }
//    return moveCollection;
//}

//unsigned int BoardState::GetKingPosition(Alliance player)
//{
//    unsigned int kingPosition = BoardUntils::getMaxTiles();
//    BoardConfig::iterator piecePtr = m_boardValue.begin();
//    for (;piecePtr!=m_boardValue.end();++piecePtr)
//    {
//        Piece* piece = piecePtr->second;
//        if(piece!=nullptr && BoardUntils::IsSameAlliance(piece->GetAlliance(), player))
//        {
//            if(piece->GetPieceType() == PieceType::KING)
//            {
//                kingPosition = piece->GetPosition();
//                break;
//            }
//        }
//    }
//    return kingPosition;
//}
