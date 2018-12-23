#pragma once
#include "Piece.h"

const static int PAWN_CANDIDATE_MOVE_COORDINATE[] = { 7, 8, 9, 16 };


class Pawn :public Piece
{
public:
	Pawn(int piecePos, Alliance pieceAlliance, QWidget *parent = nullptr);
	~Pawn();

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const;
	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const;

	virtual std::vector<Move*> calculateLegalMove(const Board* board) const;

	int			getDirection() const;

	bool		isFirstMove() const;


private:
	bool		m_isFirstMove;
};

