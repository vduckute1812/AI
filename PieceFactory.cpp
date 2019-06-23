#include "PieceFactory.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

Piece *PieceFactory::GeneratePiece(QString pieceStr, Alliance alliance)
{
    Piece* piece = nullptr;
        if(pieceStr == "Rook")         piece = new Rook(alliance);
    else if(pieceStr == "Knight")      piece = new Knight(alliance);
    else if(pieceStr == "Bishop")      piece = new Bishop(alliance);
    else if(pieceStr == "Queen")       piece = new Queen(alliance);
    else if(pieceStr == "King")        piece = new King(alliance);
    else if(pieceStr == "Pawn")        piece = new Pawn(alliance);

    return piece;
}

Piece *PieceFactory::GeneratePiece(PieceType pieceType, Alliance alliance)
{
    Piece* piece = nullptr;
    switch (pieceType) {
    case PieceType::KING:
        piece = new King(alliance);
        break;
    case PieceType::ROOK:
        piece = new Rook(alliance);
        break;
    case PieceType::BISHOP:
        piece = new Bishop(alliance);
        break;
    case PieceType::QUEEN:
        piece = new Queen(alliance);
        break;
    case PieceType::PAWN:
        piece = new Pawn(alliance);
        break;
    case PieceType::KNIGHT:
        piece = new Knight(alliance);
        break;
    }

    return piece;
}
