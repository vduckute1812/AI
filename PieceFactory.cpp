#include "PieceFactory.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

Piece *PieceFactory::GeneratePiece(QString pieceStr, Alliance pieceType)
{
         if(pieceStr == "Rook")         return new Rook(pieceType);
    else if(pieceStr == "Knight")       return new Knight(pieceType);
    else if(pieceStr == "Bishop")       return new Bishop(pieceType);
    else if(pieceStr == "Queen")        return new Queen(pieceType);
    else if(pieceStr == "King")         return new King(pieceType);
    else if(pieceStr == "Pawn")         return new Pawn(pieceType);

    else                                return nullptr;
}
