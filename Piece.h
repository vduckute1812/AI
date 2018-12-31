#pragma once
#include <vector>
#include <string>
#include <QFrame>
#include <QLabel>

enum Alliance
{
	WHITE = 'w',
	BLACK = 'b'
};

enum PieceType
{
	ROOK	= 'R',
	KNIGHT	= 'K',
	BISHOP	= 'B',
	QUEEN	= 'Q',
	KING	= 'Z',
	PAWN	= 'P'
};

class Move;
class Board;
class Piece: public QFrame
{
public:
	explicit Piece(int piecePos, Alliance pieceAlliance, PieceType type, QWidget *parent = nullptr);
	virtual ~Piece();

	virtual	std::vector<Move*> calculateLegalMove(const Board* board) const = 0;

	virtual bool		isFirstColumnExclusion(int currentPosition, int candidateOffset) const = 0;
	virtual bool		isEightColumnExclusion(int currentPosition, int candidateOffset) const = 0;

	virtual char		getKeyCharacter() const;

	PieceType			getPieceType() const;

	void				setPosition(int position);
	int					getPosistion() const;

	Alliance			getAlliance() const;

	void				hashCodeKeyValue();

	int					getHash() const;

	QLabel*				getRenderImg();

	void				diedState(bool yes = true);
	bool				isDestroy();

protected:
	int					m_piecePosition;
	Alliance			m_pieceAlliance;
	PieceType			m_pieceType;
	int					m_hashCode;

	QLabel*				m_icon;
	QRect				m_rect;

	bool				m_isDestroy;
};