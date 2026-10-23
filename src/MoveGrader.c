#include "ChessBoard.h"
#include "Move.h"
#include "MoveGrader.h"
#include "Eval.h"
#include "TranspositionTables.h"
#include "HistoryHeuristic.h"
#include "KillerHeuristic.h"

static int16_t captureScores[PIECE_TYPES][PIECE_TYPES];
static const int16_t promotionToScore[5] = {
    [0]               = 0,
    [queenPromotion]  = QUEEN_PROMOTION_SCORE,
    [rookPromotion]   = ROOK_PROMOTION_SCORE,
    [knightPromotion] = KNIGHT_PROMOTION_SCORE,
    [bishopPromotion] = BISHOP_PROMOTION_SCORE,
}; 

void initCaptureScores()
{
    for (int attackerPiece = 0; attackerPiece < PIECE_TYPES; attackerPiece++)
    {
        for (int capturedPiece = 0; capturedPiece < PIECE_TYPES; capturedPiece++)
        {

            int attackerPieceScore = pieceValues[attackerPiece];
            int capturedPieceScore = pieceValues[capturedPiece];

            int score;

            if (attackerPieceScore < capturedPieceScore + 30 )
            {
                score = CAPTURE_SCORE + 10 * capturedPieceScore - attackerPieceScore;
            }
            else
            {
                score = -CAPTURE_SCORE + 10 * capturedPieceScore - attackerPieceScore;
            }
            
            captureScores[attackerPiece][capturedPiece] = score;
        }
        
    }
    
}

void gradeMoves(ChessBoard* chessBoard, TranspositionTable* transpositionTable, MoveList* moveList, GradedMoveList* gradedMoveList, int depth)
{
    gradedMoveList->nextIndex = moveList->nextIndex;

    TranspositionTableEntry* transpositionTableEntry = getTransposition(chessBoard, transpositionTable, 0, 1);
    uint16_t TTMove = 0;

    if (transpositionTableEntry != NULL)
    {
        TTMove = transpositionTableEntry->moveScore.move;
    }
    
    uint16_t killerMove1 = killerMoves[depth][0];
    uint16_t killerMove2 = killerMoves[depth][1];

    for (int moveInd = 0; moveInd < moveList->nextIndex; moveInd++)
    {
        uint16_t selectedMove = moveList->moves[moveInd];

        gradedMoveList[moveInd].gradedMoves->move = selectedMove;

        if (TTMove == selectedMove)
        {
            gradedMoveList[moveInd].gradedMoves->grade = TRANSPOSITION_SCORE;
            continue;
        }

        if (selectedMove & promotionMask)
        {
            uint8_t promotion = (selectedMove & promotionMask) >> promotionPosition;
            gradedMoveList[moveInd].gradedMoves->grade = promotionToScore[promotion];
            continue;
        }

        uint8_t capturedPiece = chessBoard->pieceLookup[getToSq(selectedMove)];

        if (capturedPiece != empty)
        {
            uint8_t attackerPiece = chessBoard->pieceLookup[getFromSq(selectedMove)];
            gradedMoveList[moveInd].gradedMoves->grade = captureScores[attackerPiece][capturedPiece];
            continue;
        }
        
        if (selectedMove == killerMove1)
        {
            gradedMoveList[moveInd].gradedMoves->grade = KILLER_MOVE1_SCORE;
            continue;
        }

        if (selectedMove == killerMove2)
        {
            gradedMoveList[moveInd].gradedMoves->grade = KILLER_MOVE2_SCORE;
            continue;
        }
        
        gradedMoveList[moveInd].gradedMoves->grade = getHistoryHeuristic(moveList->moves[moveInd], chessBoard->pieceLookup[getFromSq(selectedMove)]) >> 1;
    }
    
} 