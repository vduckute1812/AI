#include <QPainter>
#include "Tile.h"
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

Tile::~Tile()
{

}

int Tile::getCoordinate() const
{
    return m_tileCoordinate;
}

void Tile::resetColors() const
{
    BoardTiles boardTiles;
    BoardTiles::iterator tilePtr;

    for (tilePtr = boardTiles.begin(); tilePtr!= boardTiles.end(); ++tilePtr)
    {
        Tile* tile = tilePtr->second;
        tile->setCurrentColor(m_defaultColor);
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
    m_piece = piece;

    if(m_piece)
    {
        m_piece->setPosition(m_tileCoordinate);
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
    int coordinate = this->getCoordinate();
    BoardTiles tiles = BoardUI::GetInstance()->GetEmptyTiles();
    Piece* piece = BoardController::GetInstance()->getSelecetedPiece();
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
//        BoardController::GetInstance()->setSelectedPiece(this->getPiece());


//        // Set colors
//        resetColors();

//        Piece* pieceColor = BoardController::GetInstance()->getSelectedPiece();
//        if (pieceColor  && BoardUntils::isSameAlliance(pieceColor->getAlliance(), BoardController::GetInstance()->getMoveMaker()))
//        {
//            this->setCurrentColor(CHOOSE_COLOR);
//            for (Move* move : pieceColor->calculateLegalMove(BoardController::GetInstance()->getBoard()))
//            {
//                Tile* tile = BoardController::GetInstance()->getBoard()->getTile(move->getDestCoordinate());
//                if(!currentPlayer->checkLegalMove(move))
//                {
//                    if (move->isAttack())
//                    {
//                        tile->setCurrentColor(ATTACK_COLOR);
//                    }
//                    else
//                    {
//                        tile->setCurrentColor(MOVE_COLOR);
//                    }
//                }
//                delete move;
//            }

//    }
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
