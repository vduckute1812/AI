#ifndef PIECE_H
#define PIECE_H

#include <QFrame>
#include <QLabel>
//#include "BoardGameWnd.h"


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
    KNIGHT_VALUE =  320,
    BISHOP_VALUE =  350,
    ROOK_VALUE =    500,
    QUEEN_VALUE =   900,
    KING_VALUE =    20000
};


class Move;
class Board;
class Move;
class Piece;
class Tile;

typedef std::vector<Move*> MoveCollection;
typedef unsigned int u32;

struct BoardConfig;
class Piece: public QFrame
{
public:
    explicit Piece(Alliance pieceAlliance, PieceType pieceType, PieceValue pieceValue, QWidget *parent = nullptr, unsigned int position = 0);
    virtual ~Piece();

    virtual bool		isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const = 0;
    virtual bool		isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const = 0;

    virtual int         locationBonus() const;

    virtual             MoveCollection calculateLegalMove(const BoardConfig board) const = 0;

    virtual             PieceValue GetPieceValue() const;

    void                SetPosition(unsigned int position);
    unsigned int        GetPosition() const;

    PieceType			GetPieceType() const;
    Alliance            GetAlliance() const;

    char                GetKeyCharacter() const;

    void                SetVisible(bool isVisible, Tile* tile = nullptr);

    void                SetFirstMove(bool firstMove);
    bool                IsFirstMove() const;


protected:
    unsigned int        m_piecePosition;
    Alliance			m_pieceAlliance;
    PieceType           m_pieceType;
    PieceValue          m_pieceValue;
    QLabel*             m_pieceImg;

    bool                m_isFirstMove;
};

#endif // PIECE_H
