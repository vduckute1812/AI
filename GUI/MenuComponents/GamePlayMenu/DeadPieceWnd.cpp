#include "DeadPieceWnd.h"
#include <QLabel>
#include "MainWnd.h"
#include "Tile.h"
#include "Piece/Piece.h"


DeadPieceWnd::DeadPieceWnd(QWidget* parent /*= nullptr*/): QWidget(parent)
{
    u32 messageMask = msg::KILL | msg::REVIVAL;
    ListenTo(MainWnd::GetInstance(), k_msgType, messageMask);
}

DeadPieceWnd::~DeadPieceWnd()
{
    delete m_parentLayout;
    delete m_gridWhiteDeadPiece;
    delete m_gridBlackDeadPiece;
    m_deadBlackPiece.clear();
    m_deadWhitePiece.clear();

    m_parentLayout = nullptr;
    m_gridWhiteDeadPiece = nullptr;
    m_gridBlackDeadPiece = nullptr;
}


void DeadPieceWnd::AddDeadPiece(QChar type, QChar alliance)
{
    QLabel* label = new QLabel(this);
    QPixmap pixmap = MainWnd::LoadPixmap(type + QString(alliance));
    label->setPixmap(pixmap);
    Tile* tile = nullptr;
    if(alliance == Alliance::WHITE)
    {
        tile = m_whiteTiles.at(m_whiteIdx);
        m_deadWhitePiece.push_back(label);
        m_whiteIdx++;
    }
    else {
        tile = m_blackTiles.at(m_blackIdx);
        m_deadBlackPiece.push_back(label);
        m_blackIdx++;
    }
    label->setParent(tile);
    label->show();
}


void DeadPieceWnd::RemoveDeadPiece(QChar alliance)
{
    QLabel* pieceLabel = nullptr;
    if(alliance == Alliance::WHITE)
    {
        m_whiteIdx--;
        pieceLabel = m_deadWhitePiece.at(m_whiteIdx);
        m_deadWhitePiece.pop_back();
    }
    else
    {
        m_blackIdx--;
        pieceLabel = m_deadBlackPiece.at(m_blackIdx);
        m_deadBlackPiece.pop_back();
    }
    pieceLabel->hide();
    delete pieceLabel;
}

//void DeadPieceWnd::Update()
//{

//}

void DeadPieceWnd::OnMessageReceived(const Message &msg)
{
//    if(msg.)
}

void DeadPieceWnd::Init()
{
    m_blackIdx = 0;
    m_whiteIdx = 0;

    m_parentLayout = new QVBoxLayout();
    m_gridWhiteDeadPiece = new QGridLayout();
    m_gridBlackDeadPiece = new QGridLayout();

    for (int i = 0; i < 16; ++i)    //4x4
    {
        Tile* blackTile = new Tile(i);
        blackTile->setFixedSize(TILE_ROW_SIZE, TILE_COL_SIZE);
        blackTile->SetCurrentColor(QBrush("white"));
        m_blackTiles.push_back(blackTile);
        m_gridBlackDeadPiece->addWidget(blackTile, i / 4, i % 4);

        Tile* whiteTile = new Tile(NUM_TILES - i);
        whiteTile->setFixedSize(TILE_ROW_SIZE, TILE_COL_SIZE);
        whiteTile->SetCurrentColor(QBrush("white"));
        m_whiteTiles.push_back(whiteTile);
        m_gridWhiteDeadPiece->addWidget(whiteTile, i / 4, i % 4);
    }

    m_parentLayout->addLayout(m_gridWhiteDeadPiece);
    m_parentLayout->addLayout(m_gridBlackDeadPiece);

    setLayout(m_parentLayout);
}
