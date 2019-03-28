#include "Board.h"
#include "Tile.h"
#include "BoardUntils.h"
#include "Move.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"

#include <QTextStream>
#include <QPainter>
#include <QKeyEvent>

Board::Board(BoardController* controller, QWidget *parent)
{
    Init();
	m_boardController = controller;
	m_boardController->GetInstance()->setBoard(this);
	m_boardController->GetInstance()->setMoveMaker(Alliance::WHITE);
	buildStandardBoard();

	this->m_blackPieces = calculateActivePieces(m_board, Alliance::BLACK);
	this->m_whitePieces = calculateActivePieces(m_board, Alliance::WHITE);

	this->m_blackLegalMoves = calculateLegalMoves(this->m_blackPieces);
	this->m_whiteLegalMoves = calculateLegalMoves(this->m_whitePieces);

	for (Tile* tile : m_board)
	{
		tile->move(tile->getCoordinate() % BoardUntils::NUM_TILES_PER_ROW * BoardUntils::TILE_ROW_SIZE,
			tile->getCoordinate() / BoardUntils::NUM_TILES_PER_ROW * BoardUntils::TILE_COL_SIZE);
	}

    m_blackPlayer = new BlackPlayer(this);
    m_whitePlayer = new WhitePlayer(this);

    // Stupid code
    switch (m_boardController->GetInstance()->getMoveMaker())
    {
        case Alliance::BLACK:
            m_currentPlayer = m_blackPlayer;
            break;
        case Alliance::WHITE:
            m_currentPlayer = m_whitePlayer;
    }
    startTimer(50);

    printBoard();
}

Board::~Board()
{
    //Delete tiles
    for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
    {
        delete m_board.at(i);
    }

    // Delete players
    delete m_blackPlayer;
    delete m_whitePlayer;

    //Delete pieces
    for (Piece* piece: m_blackPieces) {
        delete piece;
    }
    for (Piece* piece: m_whitePieces) {
        delete piece;
    }
}

//Create emtpy tile board
void Board::Init()
{
    for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
	{
		m_board.push_back(new Tile(i, this));
		m_board.at(i)->setPiece(nullptr);
	}	
}

void Board::buildStandardBoard()
{
    QTextStream out(stdout);

	m_boardController->GetInstance()->setPiece(	 new Rook	(0 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(	 new Knight (1 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Bishop (2 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Queen  (3 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new King   (4 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Bishop (5 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Knight (6 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Rook   (7 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (8 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (9 , Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (10, Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (11, Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (12, Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (13, Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (14, Alliance::BLACK ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (15, Alliance::BLACK ));

	m_boardController->GetInstance()->setPiece(  new Rook   (63, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Knight (62, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Bishop (61, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new King   (60, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Queen  (59, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Bishop (58, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Knight (57, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Rook   (56, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (55, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (54, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (53, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (52, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (51, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (50, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (49, Alliance::WHITE ));
	m_boardController->GetInstance()->setPiece(  new Pawn   (48, Alliance::WHITE ));
}

std::vector<Piece*>	Board::calculateActivePieces( const std::vector<Tile*> gameBoard,const Alliance alliance) const
{
	std::vector<Piece*> activePieces;

    for (Tile* tile: gameBoard)
	{
		if (tile->isTileOccupied())
		{
			if (BoardUntils::isSameAlliance(tile->getPiece()->getAlliance(), alliance))
			{
				activePieces.push_back(tile->getPiece());
			}
		}
	}
	return activePieces;
}

std::vector<Move*> Board::calculateLegalMoves(const std::vector<Piece*> pieces) const
{
	std::vector<Move*> legalMoves;
	for (Piece* piece : pieces)
	{
		for (Move* move : piece->calculateLegalMove(this))
		{
			legalMoves.push_back(move);
		}
	}

	return legalMoves;
}


std::vector<Move*> Board::calculateAttackMoves(const Alliance alliance) const
{
	std::vector<Move*> moves;
	std::vector<Piece*> pieces = calculateActivePieces(m_board, alliance);
	for (Piece* piece: pieces)
	{
		std::vector<Move*> candidateMove;
		candidateMove = piece->calculateLegalMove(this);
		for (Move* move : candidateMove)
		{
			moves.push_back(move);
		}
	}

	std::vector<Move*> attackMoves;
	for (Move* move : moves)
	{
		if (move->isAttack())
		{
			attackMoves.push_back(move);
		}
        else
        {
            delete move;
        }
	}
	return attackMoves;
}

Tile* Board::getTile(unsigned int coordinate) const
{
	return m_board[coordinate];
}

std::vector<Tile*>	Board::getTiles() const
{
	return m_board;
}


void Board::printBoard() const
{
    QTextStream out(stdout);
    char key = 'x';
    for (unsigned int i = 0; i < BoardUntils::NUM_TILES; ++i)
	{

		if (i % 8 == 0)
            out << endl;

        key = !m_board.at(i)->isTileOccupied() ? 'x' : m_board.at(i)->getPiece()->getKeyCharacter();
		
        if (m_board.at(i)->isTileOccupied() && m_board.at(i)->getPiece()->getAlliance() == Alliance::BLACK)
		{
			key = key + 'a' - 'A';
		}
		out << " " << key;
	}
	out << endl;
}

Player* Board::getCurrentPlayer()
{
    // Stupid code
    switch (m_boardController->GetInstance()->getMoveMaker())
    {
        case Alliance::BLACK:
            m_currentPlayer = m_blackPlayer;
            break;
        case Alliance::WHITE:
            m_currentPlayer = m_whitePlayer;
    }

    return m_currentPlayer;
}


std::vector<Piece*>	Board::getPieces(PieceType type, Alliance alliance) const
{
	std::vector<Piece*> activePiece = alliance == Alliance::WHITE ? this->m_whitePieces : this->m_blackPieces;
	std::vector<Piece*> result;
	for (Piece* piece : activePiece)
	{
		if (piece->getPieceType() == type)
		{
			result.push_back(piece);
		}
	}

	return result;
}


void Board::timerEvent(QTimerEvent *e) 
{
	Q_UNUSED(e);
	repaint();
}

void Board::keyPressEvent(QKeyEvent* e)
{
    QTextStream out(stdout);
    out << "Key: " << e->key() << endl;
    //16777234
    //16777236
}
