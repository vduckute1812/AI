#pragma once
#include "Piece.h"

enum MoveStatus
{
	DONE,
	ILLEGAL_MOVE
};

class Board;
class Move
{
public:
	Move(const Board* board, const Piece* piece, const Piece* attackPiece, int destinate);
	~Move();

	const Piece*			getMovePiece() const;
	int						getDestCoordinate();
	bool					isAttack();

	int						GetHash() const;

	bool					isDone(MoveStatus status) const;

private:
	const Board*	m_board;
	const Piece*	m_movePiece;
	const Piece*	m_attackPiece;

	int				m_destCoordinate;
	bool			m_isAttack;
};

