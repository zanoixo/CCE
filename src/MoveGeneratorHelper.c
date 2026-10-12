#include "ChessBoard.h"
#include "Move.h"
#include "Utils.h"
#include "Eval.h"

int calculateCaptureMoveScore(ChessBoard* chessBoard, uint8_t fromSq, uint8_t toSq)
{
    int attackerScore = getPieceScore(chessBoard->pieceLookup[fromSq]);
    int capturedScore = getPieceScore(chessBoard->pieceLookup[toSq]);

    int score;

    if (attackerScore < capturedScore + 30 )
    {
        score = 2000 + 10 * capturedScore - attackerScore;
    }
    else
    {
        score = -2000 + 10 * capturedScore - attackerScore;
    }
    
    return score;
}

void addMove(uint64_t from, uint64_t to, uint16_t promotionFlag, uint16_t enPassantFlag, MoveList* moveList, int score)
{
    uint16_t move = constructMove(from, to, promotionFlag, enPassantFlag);
    moveList->moves[moveList->nextIndex] = (Move){ move, score };
    moveList->nextIndex++;
}

void generatePawnPromotionMoves(uint64_t from, uint64_t to, MoveList* moveList)
{
    addMove(from, to, queenPromotion, EMPTY_ENPASSANT_FLAG, moveList, QUEEN_PROMOTION_VALUE);
    addMove(from, to, rookPromotion, EMPTY_ENPASSANT_FLAG, moveList, ROOK_PROMOTION_VALUE);
    addMove(from, to, bishopPromotion, EMPTY_ENPASSANT_FLAG, moveList, BISHOP_PROMOTION_VALUE);
    addMove(from, to, knightPromotion, EMPTY_ENPASSANT_FLAG, moveList, KNIGHT_PROMOTION_VALUE);
}