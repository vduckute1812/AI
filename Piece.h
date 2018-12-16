#pragma once
#include <vector>

enum Alliance
{
	WHITE,
	BLACK
};

class Move;
class Board;
class Piece
{
public:
	explicit Piece(int piecePos, Alliance pieceAlliance);
	virtual ~Piece();

	virtual const std::vector<Move*> calculateLegalMove(const Board* board) const = 0;

	virtual bool isFirstColumnExclusion(int currentPosition, int candidateOffset) const = 0;
	virtual bool isEightColumnExclusion(int currentPosition, int candidateOffset) const = 0;

	virtual char getKeyCharacter() const = 0;

	int			getPosistion() const;

	Alliance	getAlliance() const;

protected:
	int			m_piecePosition;
	Alliance	m_pieceAlliance;
};

