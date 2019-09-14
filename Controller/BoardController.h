#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <QWidget>
#include "Messenger.h"
#include "Piece/Piece.h"

class Player;
typedef std::vector<Piece*> CollectPieces;
class BoardController: public Messenger
{
public:

    BoardController();

    void        SetSelecetedPiece(Piece* piece);
    Piece*      GetSelecetedPiece() const {return m_piece;}

    void        MoveSelectedPiece(unsigned int coordinate);

    Alliance    GetMoveMaker();
    Alliance    GetMoveMaker(const BoardConfig& board) const;

    void        MovePiece(Move* move);

    bool                IsTileOccupied(const BoardConfig& board, u32 tilePosition) const;
    void                SetPieceOnBoard(BoardConfig& board, u32 piecePosition, Piece* piece);
    Piece*              GetPieceOnBoard(const BoardConfig& board, u32 piecePosition) const;
    CollectPieces       GetPiecesOnBoard(BoardConfig board, Alliance alliance) const;

    u32                 GetKingPosition( BoardConfig board, Alliance player) const;
    MoveCollection      GetMoveCollections(BoardConfig board, Alliance player) const;

    bool                IsKingThreat( const BoardConfig& board, Alliance player) const;
    bool                IsCheckMate(const BoardConfig& board, Alliance player) const;

    void                PrintBoard(const BoardConfig& board) const;

private:
    Piece*          m_piece;
    Player*         m_currentPlayer;       // Black player is AI default mode
};

#endif // BOARDCONTROLLER_H
