#include "ChessBoard.h"
#include "Move.h"
#include "Utils.h"
#include "Eval.h"

void addMove(uint64_t from, uint64_t to, uint16_t promotionFlag, uint16_t enPassantFlag, MoveList* moveList)
{
    moveList->moves[moveList->nextIndex] = constructMove(from, to, promotionFlag, enPassantFlag);
    moveList->nextIndex++;
}

void generatePawnPromotionMoves(uint64_t from, uint64_t to, MoveList* moveList)
{
    addMove(from, to, queenPromotion, EMPTY_ENPASSANT_FLAG, moveList);
    addMove(from, to, rookPromotion, EMPTY_ENPASSANT_FLAG, moveList);
    addMove(from, to, bishopPromotion, EMPTY_ENPASSANT_FLAG, moveList);
    addMove(from, to, knightPromotion, EMPTY_ENPASSANT_FLAG, moveList);
}