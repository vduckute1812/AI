#include "Move.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"

Player::Player(const Board* board, Alliance alliance)
{
	m_pieces = board->calculateActivePieces(board->getTiles(), alliance);
	m_isInCheck = false;
	m_alliance = alliance;
	m_King =  board->getPieces(PieceType::KING, alliance).at(0);

    m_isInCheck = false;
}

Player::~Player()
{
}

std::vector<Move*> Player::calculateActacksOnTile(int piecePosition, std::vector<Move*> moves)
{
    std::vector<Move*> attackMove;
	for (Move* move : moves)
	{
		if (piecePosition == move->getDestCoordinate())
		{
            attackMove.push_back(move);
		}
        else
        {
            delete move;
        }
	}
    return attackMove;
}

bool Player::isInCheck()
{
    m_isInCheck = true;

    std::vector<Move*> moves = BoardController::GetInstance()->getBoard()->calculateAttackMoves(m_alliance == Alliance::WHITE ? Alliance::BLACK: Alliance::WHITE);
    std::vector<Move*> attackedMove = calculateActacksOnTile(m_King->getPosistion(), moves);

	if (attackedMove.empty())
	{
        m_isInCheck = false;
    }
    return m_isInCheck;
}

bool  Player::hasEscapeMoves()
{
    return false;
}

bool Player::isInCheckMate()
{
    return isInCheck() && !hasEscapeMoves();
}

bool Player::checkLegalMove(Move* move)
{
    bool checkState = false;

    Tile* currentTile = BoardController::GetInstance()->getBoard()->getTile( move->getMovePiece()->getPosistion());
    Tile* dstTile = BoardController::GetInstance()->getBoard()->getTile( move->getDestCoordinate());

    Piece* currentPiece = currentTile->getPiece();
    Piece* dstPiece = dstTile->getPiece();

    currentTile->setOccupiedState(false);
    dstTile->setOccupiedState(true);

    Piece* tmp = dstPiece;
    dstTile->setPiece(currentPiece);
    currentTile->setPiece(nullptr);

    if(isInCheck())
    {
        checkState = true;
    }

    //Reset old state
    currentTile->setOccupiedState(true);
    dstTile->setOccupiedState(false);
    currentTile->setPiece(currentPiece);
    dstTile->setPiece(tmp);

    return checkState;
}
