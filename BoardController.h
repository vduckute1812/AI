#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <QWidget>
#include "Piece.h"

class BoardController: public QWidget
{
    Q_OBJECT
public:
    enum EditModeDef
    {
        HUMAN_HUMAN,
        HUMAN_AI,
        NONE
    };

    BoardController(QWidget* parent = nullptr);
    void        mousePressEvent(QMouseEvent *) override;

    void        SetSelecetedPiece(Piece* piece);
    Piece*      GetSelecetedPiece() const {return m_piece;}

    void        MoveSelectedPiece(unsigned int coordinate);

    Alliance    GetMoveMaker();

    void        MovePiece(Move* move);

    void        SetModePlayer(EditModeDef modePlayer);
    EditModeDef GetModePlayer() const;

    bool        IsTileOccupied(const BoardConfig& board, u32 tilePosition);
    void        SetPieceOnBoard(BoardConfig& board, u32 piecePosition, Piece* piece);
    Piece*      GetPieceOnBoard(const BoardConfig& board, u32 piecePosition) const;

    u32                     GetKingPosition( BoardConfig board, Alliance player) const;
    MoveCollection          GetMoveCollections(BoardConfig board, Alliance player);

signals:
    void        PromotePiece(PieceType, Alliance);

private:
    Piece*          m_piece;
    EditModeDef     m_modePlayer;       // Black player is AI default mode
};

#endif // BOARDCONTROLLER_H
