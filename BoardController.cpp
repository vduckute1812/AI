#include "Defines.h"
#include <QMouseEvent>
#include "BoardController.h"

typedef vec2<int32_t> vec2i;

BoardController::BoardController(QWidget* parent /*= nullptr*/) : QWidget(parent)
{

}

void BoardController::mousePressEvent(QMouseEvent *)
{
//    vec2i pointer2D(event->x(), event->y());
}

void BoardController::SetSelecetedPiece(Piece* piece)
{
    m_piece = piece;
}
