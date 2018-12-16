#pragma once

class Board;
class Piece;
class Move
{
public:
	Move(const Board* board, const Piece* piece, const Piece* attackPiece, int destinate);
	~Move();
private:
	const Board*	m_board;
	const Piece*	m_movePiece;
	const Piece*	m_attackPiece;

	int				m_destCoordinate;

	bool			m_isAttack;
};

