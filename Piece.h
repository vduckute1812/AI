#ifndef PIECE_H
#define PIECE_H

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

enum PieceValue
{
    PAWN_VALUE =    100,
    KNIGHT_VALUE =  300,
    BISHOP_VALUE =  300,
    ROOK_VALUE =    500,
    QUEEN_VALUE =   900,
    KING_VALUE =    1000
};

class Move;
class Board;
class Move;

typedef std::vector<Move*> MoveCollection;

class Piece: public QFrame
{
public:
    explicit Piece(Alliance pieceAlliance, int position, PieceType pieceType, PieceValue pieceValue, QWidget *parent = nullptr);
    virtual ~Piece();

    virtual bool		isFirstColumnExclusion(int currentPosition, int candidateOffset) const = 0;
    virtual bool		isEightColumnExclusion(int currentPosition, int candidateOffset) const = 0;

    virtual             MoveCollection calculateLegalMove(const Board* board) const = 0;

    virtual             PieceValue getPieceValue() const;

    void                setPosition(int position);
    int                 getPosition() const;

    PieceType			getPieceType() const;
    Alliance            getAlliance() const;

    char                getKeyCharacter() const;

    QLabel*             getRenderImg() const;

    void                setFirstMove(bool firstMove);
    bool                isFirstMove() const;

protected:
    int                 m_piecePosition;
    Alliance			m_pieceAlliance;
    PieceType           m_pieceType;
    PieceValue          m_pieceValue;
    QLabel*             m_pieceImg;

    bool                m_isFirstMove;
};

#endif // PIECE_H
