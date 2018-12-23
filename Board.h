#pragma once
#include "Piece.h"
#include "Player.h"
#include "BoardController.h"

#include <vector>

class Tile;

class Board : public QWidget
{
public:
	Board(BoardController*, QWidget *parent = nullptr);
	~Board();

	const Tile*				getTile(int coordinate) const;
	void					printBoard() const;

	std::vector<Move*>		calculateLegalMoves(const std::vector<Piece*> pieces) const;

	std::vector<Move*>		calculateAttackMoves(const std::vector<Move*> moves, const Alliance alliance) const;

	std::vector<Piece*>		calculateActivePieces(const std::vector<Tile*> gameBoard, const Alliance alliance) const;

	std::vector<Piece*>		getPieces() const;

	std::vector<Tile*>		getTiles() const;

	std::vector<Piece*>		getPieces(PieceType type, Alliance alliance) const;

	void					updateBoard();

protected:
	void			paintEvent(QPaintEvent *);

private:
	void			Init();
	void			buildStandardBoard();

	std::vector<Tile*>		m_board;

	std::vector<Piece*>		m_whitePieces;
	std::vector<Piece*>		m_blackPieces;

	std::vector<Move*>		m_blackLegalMoves;
	std::vector<Move*>		m_whiteLegalMoves;

	BoardController*		m_boardController;

	Player*					m_player;
};
