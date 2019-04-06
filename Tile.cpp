#include "Tile.h"
#include <QPainter>
#include "Move.h"
#include "Piece.h"
#include "BoardUI.h"
#include "BoardUntils.h"
#include "BoardController.h"

Tile::Tile(const int coordinate, Piece* piece, QWidget* parrent): QWidget (parrent)
{
    m_tileCoordinate = coordinate;
    m_piece = piece;
    resize(BoardUntils::TILE_ROW_SIZE, BoardUntils::TILE_COL_SIZE);
    m_defaultColor = (m_tileCoordinate + (m_tileCoordinate / BoardUntils::NUM_TILES_PER_ROW) % 2) % 2 ? ODD_COLOR : EVEN_COLOR;
    m_currentColor = m_defaultColor;
}

int Tile::getCoordinate() const
{
    return m_tileCoordinate;
}

void Tile::resetColors() const
{
    BoardTiles boardTiles = BoardUI::GetInstance()->GetTiles();
    BoardTiles::iterator tilePtr;

    for (tilePtr = boardTiles.begin(); tilePtr!= boardTiles.end(); ++tilePtr)
    {
        Tile* tile = tilePtr->second;
        tile->setCurrentColor(tile->getDefaultColor());
    }
}


bool Tile::isTileOccupied() const
{
    if(m_piece == nullptr)
        return false;
    else
        return true;
}

void Tile::setPiece(Piece *piece)
{
    if(m_piece != nullptr)
        m_piece->getRenderImg()->hide();

    m_piece = piece;
    if(piece != nullptr)
    {
        m_piece->setPosition(m_tileCoordinate);
        m_piece->setParent(this);
        m_piece->getRenderImg()->setParent(this);
        m_piece->getRenderImg()->show();
    }
}

Piece* Tile::getPiece() const
{
    return m_piece;
}

void Tile::setCurrentColor(QBrush color)
{
    m_currentColor = color;
}

QBrush Tile::getDefaultColor() const
{
    return m_defaultColor;
}

void Tile::mousePressEvent(QMouseEvent *)
{
    // Make move Piece
    int coordinate = this->getCoordinate();
    Piece* piece = BoardController::GetInstance()->getSelecetedPiece();
    Alliance currentMoveMaker = BoardController::GetInstance()->getMoveMaker();
    if (piece  && BoardUntils::isSameAlliance(piece->getAlliance(), currentMoveMaker))
    {
        for (Move* move : piece->calculateLegalMove(BoardUI::GetInstance()->GetCurrentBoard()))
        {
             if (move->getDestCoordinate() == coordinate)
             {
                 BoardController::GetInstance()->movePiece(move);
             }
             else
             {
                 delete move;
             }
        }
    }

    BoardController::GetInstance()->setSelectedPiece(this->getPiece());

    // Set colors on Board. Render posible move
    resetColors();
    Piece* pieceColor = BoardController::GetInstance()->getSelecetedPiece();

    if (pieceColor  && BoardUntils::isSameAlliance(pieceColor->getAlliance(), BoardController::GetInstance()->getMoveMaker()))
    {
        this->setCurrentColor(CHOOSE_COLOR);
        for (Move* move : pieceColor->calculateLegalMove(BoardUI::GetInstance()->GetCurrentBoard()))
        {
            Tile* tile = BoardUI::GetInstance()->GetTiles().at(move->getDestCoordinate());
            if(move->isAttackMove())
            {
                tile->setCurrentColor(ATTACK_COLOR);
            }
            else {
                tile->setCurrentColor(MOVE_COLOR);
            }
            delete move;
        }
    }
}

void Tile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(m_currentColor);
    painter.drawRect(rect());
}

namespace TILES
{
    BoardTiles createEmptyTiles()
    {
        BoardTiles tableTiles;
        Piece* NULL_PIECE = nullptr;

        for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
        {
            tableTiles.insert(std::pair<int, Tile*>(i,  new Tile(i, NULL_PIECE)));
        }

        return tableTiles;
    }
}
