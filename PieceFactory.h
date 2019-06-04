#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include "Piece.h"
#include <QString>

class PieceFactory
{
public:
        static Piece* GeneratePiece(QString pieceStr, Alliance pieceType);
};

#endif // PIECEFACTORY_H
