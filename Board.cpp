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

#include <iostream>

Board::Board(BoardController* controller)
{
	Init();
	m_boardController = controller;
	m_boardController->setBoard(m_board);
	m_boardController->setMoveMaker(Alliance::WHITE);
	buildStandardBoard();

	this->m_blackPieces = calculateActivePieces(m_board, Alliance::BLACK);
	this->m_whitePieces = calculateActivePieces(m_board, Alliance::WHITE);

	this->m_blackLegalMoves = calculateLegalMoves(this->m_blackPieces);
	this->m_whiteLegalMoves = calculateLegalMoves(this->m_whitePieces);
}

Board::~Board()
{
}

//Create emtpy tile board
void Board::Init()
{
	for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
	{
		m_board.push_back(new Tile(i));
	}
}

void Board::buildStandardBoard()
{
	m_boardController->GetInstance()->setPiece(  new Rook   (0 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Knight (1 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Bishop (2 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Queen  (3 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new King   (4 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Bishop (5 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Knight (6 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Rook   (7 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (8 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (9 , Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (10, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (11, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (12, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (13, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (14, Alliance::BLACK));
	m_boardController->GetInstance()->setPiece(  new Pawn   (15, Alliance::BLACK));

	m_boardController->GetInstance()->setPiece(  new Rook   (63, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Knight (62, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Bishop (61, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new King   (60, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Queen  (59, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Bishop (58, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Knight (57, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Rook   (56, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (55, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (54, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (53, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (52, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (51, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (50, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (49, Alliance::WHITE));
	m_boardController->GetInstance()->setPiece(  new Pawn   (48, Alliance::WHITE));

	for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
	{
		if (!m_board.at(i)->isEmptyTile())
		{
			std::cout << "Hash : " << m_board.at(i)->getPiece()->getKeyCharacter() << " : " << m_board.at(i)->getPiece()->getHash() << std::endl;
		}
	}

	Move* move = new Move(this, m_board.at(48)->getPiece(), nullptr, 45);
	m_boardController->GetInstance()->movePiece(move);

	std::cout << "Hash : " << move->getMovePiece()->getHash() << " MOVE " << move->GetHash() << std::endl;

	delete move;
}

std::vector<Piece*>	Board::calculateActivePieces(const std::vector<Tile*> gameBoard, const Alliance alliance) const
{
	std::vector<Piece*> activePieces;
	for (Tile* tile: gameBoard)
	{
		if (tile->isTileOccupied())
		{
			if (tile->getPiece()->getAlliance() == alliance)
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


const Tile* Board::getTile(int coordinate) const
{
	return m_board[coordinate];
}

std::vector<Tile*>	Board::getTiles() const
{
	return m_board;
}


void Board::printBoard() const
{
	char key = 'x';
	for (int i = 0; i < BoardUntils::NUM_TILES; ++i)
	{

		if (i % 8 == 0)
			std::cout << std::endl;

		key = m_board.at(i)->isEmptyTile() ? 'x' : m_board.at(i)->getPiece()->getKeyCharacter();
		
		if (!m_board.at(i)->isEmptyTile() && m_board.at(i)->getPiece()->getAlliance() == Alliance::BLACK)
		{
			key = key + 'a' - 'A';
		}
		std::cout << " " << key;
	}
	std::cout << std::endl;
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
