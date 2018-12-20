#pragma once
#include "Piece.h"
#include "BoardController.h"

#include <vector>

class Tile;

class Board
{
public:
	Board(BoardController*);
	~Board();

	const Tile*				getTile(int coordinate) const;
	void					printBoard() const;

	std::vector<Move*>		calculateLegalMoves(const std::vector<Piece*> pieces) const;
	std::vector<Piece*>		calculateActivePieces(const std::vector<Tile*> gameBoard, const Alliance alliance) const;

	std::vector<Piece*>		getPieces() const;

	std::vector<Tile*>		getTiles() const;

	std::vector<Piece*>		getPieces(PieceType type, Alliance alliance) const;

private:
	void			Init();
	void			buildStandardBoard();

	std::vector<Tile*>		m_board;

	std::vector<Piece*>		m_whitePieces;
	std::vector<Piece*>		m_blackPieces;

	std::vector<Move*>		m_blackLegalMoves;
	std::vector<Move*>		m_whiteLegalMoves;

	BoardController*		m_boardController;
};
