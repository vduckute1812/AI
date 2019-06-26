#ifndef BONUSSYSTEM_H
#define BONUSSYSTEM_H

#include "Piece.h"

struct BonusSystem
{
public:
    static int pawnBonus(const u32 position, Alliance alliance);
    static int rookBonus(const u32 position, Alliance alliance);
    static int knightBonus(const u32 position, Alliance alliance);
    static int bishopBonus(const u32 position, Alliance alliance);
    static int queenBonus(const u32 position, Alliance alliance);
    static int kingBonus(const u32 position, Alliance alliance);

private:
    static const int WHITE_PAWN_PREFERRED_COORDINATES[];
    static const int BLACK_PAWN_PREFERRED_COORDINATES[];
    static const int WHITE_ROOK_PREFERRED_COORDINATES[];
    static const int BLACK_ROOK_PREFERRED_COORDINATES[];
    static const int WHITE_KNIGHT_PREFERRED_COORDINATES[];
    static const int BLACK_KNIGHT_PREFERRED_COORDINATES[];
    static const int WHITE_BISHOP_PREFERRED_COORDINATES[];
    static const int BLACK_BISHOP_PREFERRED_COORDINATES[];
    static const int WHITE_QUEEN_PREFERRED_COORDINATES[];
    static const int BLACK_QUEEN_PREFERRED_COORDINATES[];
    static const int WHITE_KING_PREFERRED_COORDINATES[];
    static const int BLACK_KING_PREFERRED_COORDINATES[];
};



int BonusSystem::pawnBonus(const u32 position, Alliance alliance)
{
    int score = 0;
    switch (alliance)
    {
    case Alliance::WHITE:
        score = WHITE_PAWN_PREFERRED_COORDINATES[position];
        break;
    case Alliance::BLACK:
        score = BLACK_PAWN_PREFERRED_COORDINATES[position];
        break;
    }

    return score;
}

int BonusSystem::rookBonus(const u32 position, Alliance alliance)
{
    int score = 0;
    switch (alliance)
    {
    case Alliance::WHITE:
        score = WHITE_ROOK_PREFERRED_COORDINATES[position];
        break;
    case Alliance::BLACK:
        score = BLACK_ROOK_PREFERRED_COORDINATES[position];
        break;
    }

    return score;
}

int BonusSystem::knightBonus(const u32 position, Alliance alliance)
{
    int score = 0;
    switch (alliance)
    {
    case Alliance::WHITE:
        score = WHITE_KNIGHT_PREFERRED_COORDINATES[position];
        break;
    case Alliance::BLACK:
        score = BLACK_KNIGHT_PREFERRED_COORDINATES[position];
        break;
    }

    return score;
}

int BonusSystem::bishopBonus(const u32 position, Alliance alliance)
{
    int score = 0;
    switch (alliance)
    {
    case Alliance::WHITE:
        score = WHITE_BISHOP_PREFERRED_COORDINATES[position];
        break;
    case Alliance::BLACK:
        score = BLACK_BISHOP_PREFERRED_COORDINATES[position];
        break;
    }

    return score;
}

int BonusSystem::queenBonus(const u32 position, Alliance alliance)
{
    int score = 0;
    switch (alliance)
    {
    case Alliance::WHITE:
        score = WHITE_QUEEN_PREFERRED_COORDINATES[position];
        break;
    case Alliance::BLACK:
        score = BLACK_QUEEN_PREFERRED_COORDINATES[position];
        break;
    }

    return score;
}

int BonusSystem::kingBonus(const u32 position, Alliance alliance)
{
    int score = 0;
    switch (alliance)
    {
    case Alliance::WHITE:
        score = WHITE_KING_PREFERRED_COORDINATES[position];
        break;
    case Alliance::BLACK:
        score = BLACK_KING_PREFERRED_COORDINATES[position];
        break;
    }

    return score;
}


/*//////////////////////////////////////////////////////////*/

const int BonusSystem::WHITE_PAWN_PREFERRED_COORDINATES[] =
{
        0,  0,  0,  0,  0,  0,  0,  0,
        75, 75, 75, 75, 75, 75, 75, 75,
        25, 25, 29, 29, 29, 29, 25, 25,
        5,  5, 10, 25, 25, 10,  5,  5,
        0,  0,  0, 20, 20,  0,  0,  0,
        5, -5,-10,  0,  0,-10, -5,  5,
        5, 10, 10,-20,-20, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
};

const int BonusSystem::BLACK_PAWN_PREFERRED_COORDINATES[] =
{
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10,-20,-20, 10, 10,  5,
        5, -5,-10,  0,  0,-10, -5,  5,
        0,  0,  0, 20, 20,  0,  0,  0,
        5,  5, 10, 25, 25, 10,  5,  5,
        25, 25, 29, 29, 29, 29, 25, 25,
        75, 75, 75, 75, 75, 75, 75, 75,
        0,  0,  0,  0,  0,  0,  0,  0
};

const int BonusSystem::WHITE_KNIGHT_PREFERRED_COORDINATES[] =
{
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
};

const int BonusSystem::BLACK_KNIGHT_PREFERRED_COORDINATES[] =
{
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50,
};

const int BonusSystem::WHITE_BISHOP_PREFERRED_COORDINATES[] =
{
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
};

const int BonusSystem::BLACK_BISHOP_PREFERRED_COORDINATES[] =
{
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -20,-10,-10,-10,-10,-10,-10,-20,
};

const int BonusSystem::WHITE_ROOK_PREFERRED_COORDINATES[] =
{
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 20, 20, 20, 20, 20, 20,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
};

const int BonusSystem::BLACK_ROOK_PREFERRED_COORDINATES[] =
{
        0,  0,  0,  5,  5,  0,  0,  0,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        5, 20, 20, 20, 20, 20, 20,  5,
        0,  0,  0,  0,  0,  0,  0,  0,
};

const int BonusSystem::WHITE_QUEEN_PREFERRED_COORDINATES[] =
{
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
         -5,  0,  5,  5,  5,  5,  0, -5,
          0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
};

const int BonusSystem::BLACK_QUEEN_PREFERRED_COORDINATES[] =
{
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -10,  5,  5,  5,  5,  5,  0,-10,
          0,  0,  5,  5,  5,  5,  0, -5,
          0,  0,  5,  5,  5,  5,  0, -5,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
};

const int BonusSystem::WHITE_KING_PREFERRED_COORDINATES[] =
{
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
         20, 20,  0,  0,  0,  0, 20, 20,
         20, 30, 10,  0,  0, 10, 30, 20
};

const int BonusSystem::BLACK_KING_PREFERRED_COORDINATES[] =
{
         20, 30, 10,  0,  0, 10, 30, 20,
         20, 20,  0,  0,  0,  0, 20, 20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30
};



#endif // BONUSSYSTEM_H
