#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <QWidget>

class Piece;
class BoardController: public QWidget
{
public:
    BoardController(QWidget* parent = nullptr);
    void     mousePressEvent(QMouseEvent *) override;

    void        SetSelecetedPiece(Piece* piece);
    Piece*      GetSelecetedPiece() const {return m_piece;}

private:
    Piece*      m_piece;
    int         m_coordinate;
};

#endif // BOARDCONTROLLER_H
