#pragma once
#include <vector>
#include <string>

enum Alliance
{
	WHITE,
	BLACK
};

enum PieceType
{
	ROOK   = 'R',
	KNIGHT = 'K',
	BISHOP = 'B',
	QUEEN  = 'Q',
	KING   = 'K',
	PAWN   = 'P'
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


	virtual char getKeyCharacter() const;

	virtual PieceType getPieceType() const;

	int			getPosistion() const;

	Alliance	getAlliance() const;

	virtual void	 hashCodeKeyValue();

	virtual int		getHash() const;

protected:
	int			m_piecePosition;
	Alliance	m_pieceAlliance;
	PieceType	m_pieceType;
	int			m_hashCode;
};

