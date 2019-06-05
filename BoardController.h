#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <QWidget>
#include "Singleton.h"
#include "Piece.h"

class BoardController: public Singleton<BoardController>, public QWidget
{
public:
    BoardController(QWidget* parent = nullptr);
    void        mousePressEvent(QMouseEvent *) override;

    void        SetSelecetedPiece(Piece* piece);
    Piece*      GetSelecetedPiece() const {return m_piece;}

    Alliance    GetMoveMaker();
    void        SetMoveMaker(Alliance maker);

private:
    Piece*      m_piece;
    int         m_coordinate;
    Alliance    m_moveMaker;
};

#endif // BOARDCONTROLLER_H
