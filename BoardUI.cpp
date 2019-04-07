#include "Tile.h"
#include "Piece.h"
#include "Board.h"
#include "BoardUI.h"
#include "BoardUntils.h"
#include "BoardController.h"
#include "MoveMgr.h"
#include <QKeyEvent>

BoardUI::~BoardUI()
{
    BoardController::GetInstance()->freeGame();
    BoardController::GetInstance()->FreeInstance();
}

void BoardUI::InitBoardGame()
{    
    m_isLocked = false;

    m_tiles = TILES::createEmptyTiles();
    Board* initBoard = BOARD::createStandardBoard();
    SetBoard(initBoard);

    // set default board
    m_standardBoard = initBoard;

    setFixedSize(BoardUntils::TILE_ROW_SIZE * BoardUntils::NUM_TILES_PER_ROW,
                 BoardUntils::TILE_COL_SIZE * BoardUntils::NUM_TILES_PER_ROW);

    // Set parrent and move tiles to their coordinate
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = tilePtr->second;
        tile->setParent(this);
        tile->move(tile->getCoordinate() % BoardUntils::NUM_TILES_PER_ROW * BoardUntils::TILE_ROW_SIZE,
            tile->getCoordinate() / BoardUntils::NUM_TILES_PER_ROW * BoardUntils::TILE_COL_SIZE);
    }

    // Set piece on board
    BoardConfig boardConfig = m_board->getBoardConfig();
    BoardConfig::iterator piecePtr;
    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        const int location = piecePtr->first;
        Tile* tile = m_tiles.at(location);        
        Piece* piece = boardConfig.at(location);
        if(piece != nullptr)
            piece->setParent(tile);
    }

    // Set move maker
    BoardController::GetInstance()->setMoveMaker(Alliance::WHITE);
//    show();
    startTimer(100);
}

BoardTiles BoardUI::GetTiles()
{
    return m_tiles;
}

void BoardUI::ResetTiles()
{
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = tilePtr->second;
        tile->setPiece(nullptr);
    }
}

void BoardUI::ResetColorTiles()
{
    BoardTiles::iterator tilePtr;

    for (tilePtr = m_tiles.begin(); tilePtr!= m_tiles.end(); ++tilePtr)
    {
        Tile* tile = tilePtr->second;
        tile->setCurrentColor(tile->getDefaultColor());
    }
}

const Board* BoardUI::GetCurrentBoard()
{
    return m_board;
}

void BoardUI::SetBoard(Board *board)
{
    BoardUI::GetInstance()->ResetColorTiles();

    if(m_board != nullptr)
    {
        delete m_board;
    }
    m_board = board;
    ResetTiles();
    BoardConfig config = m_board->getBoardConfig();
    BoardConfig::iterator tileConfig;

    for (tileConfig = config.begin(); tileConfig!=config.end(); ++tileConfig)
    {
        const int coordinate = tileConfig->first;
        Piece* piece = tileConfig->second;
        m_tiles.at(coordinate)->setPiece(piece);
    }

    m_board->printBoard();
}

void BoardUI::FreeBoardGame()
{
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tileRelease = tilePtr->second;
        delete tileRelease;
    }

    BoardConfig boardConfig = m_standardBoard->getBoardConfig();
    BoardConfig::iterator piecePtr;

    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
        Piece* piece = piecePtr->second;
        delete piece;
    }
}

void BoardUI::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    repaint();
}

void BoardUI::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Left)
    {
        MoveMgr::GetInstance()->Undo();
    }
    else if (event->key() == Qt::Key::Key_Right)
    {
        MoveMgr::GetInstance()->Redo();
    }

}

