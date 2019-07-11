#ifndef BOARDUNTILS_H
#define BOARDUNTILS_H
#include "Defines.h"
#include "Piece.h"
#include "Move.h"


enum CheckColumn
{
    FIRST   = 1,
    SECOND  = 2,
    NEAR_END_OF_COL = NUM_TILES_PER_COL - 1,
    END_OF_COL      = NUM_TILES_PER_COL
};

struct BoardUntils
{

    static u32 getMaxTiles() {return NUM_TILES_PER_ROW * NUM_TILES_PER_COL;}

    static bool IsNumColumn(u32 numColumn , u32 coordinate)
    {
        u32 firstColum = numColumn - 1;
        while(firstColum < getMaxTiles())
        {
            if(firstColum == coordinate)
                return true;

            firstColum += NUM_TILES_PER_COL;
        }
        return false;
    }

    static bool IsValidTileCandidate(int coordinate)
    {
        if(coordinate < 0 || coordinate >= int(getMaxTiles()))
        {
            return false;
        }
        return true;
    }

    static bool IsSameAlliance(Alliance piece1, Alliance piece2)
    {
        if ((piece1 == Alliance::BLACK && piece2 == Alliance::BLACK)
            || (piece1 == Alliance::WHITE && piece2 == Alliance::WHITE))
        {
            return true;
        }
    return false;
    }


    static int mvvlva(const Move* move)
    {
        const Piece* movingPiece = move->GetMovedPiece();
        if(move->IsAttackMove())
        {
            const Piece* attackedPiece = move->GetAttackedPiece();
            return (attackedPiece->GetPieceValue() - movingPiece->GetPieceValue() +  PieceValue::KING_VALUE) * 100;
        }
        return PieceValue::KING_VALUE - movingPiece->GetPieceValue();
    }

    static Alliance OpponentPlayer(const Alliance player)
    {
        return player == Alliance::WHITE? Alliance::BLACK : Alliance::WHITE;
    }
};



#endif // BOARDUNTILS_H
