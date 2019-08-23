#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include "Piece.h"
#include <QString>

class PieceFactory
{
public:
    static Piece* GeneratePiece(QString pieceStr, Alliance alliance);
    static Piece* GeneratePiece(PieceType pieceType, Alliance alliance);
};

#endif // PIECEFACTORY_H
