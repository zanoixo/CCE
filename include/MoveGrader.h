#pragma once

#include "Utils.h"
#include "HistoryHeuristic.h"

#define TRANSPOSITION_SCORE 30000
#define QUEEN_PROMOTION_SCORE 20000
#define CAPTURE_SCORE 18000
#define KILLER_MOVE1_SCORE 17000
#define KILLER_MOVE2_SCORE 16900
#define MAX_HISTORY_SCORE 16383
#define MIN_HISOTRY_SCORE -16384
#define KNIGHT_PROMOTION_SCORE -20000
#define ROOK_PROMOTION_SCORE -21000
#define BISHOP_PROMOTION_SCORE -22000 

typedef struct MoveList MoveList;
typedef struct ChessBoard ChessBoard;
typedef struct TranspositionTable TranspositionTable;

typedef struct GradedMove
{
    uint16_t move;
    int16_t grade;
}GradedMove;

typedef struct GradedMoveList
{
    GradedMove* gradedMoves;
    uint16_t nextIndex; 
}GradedMoveList;

void gradeMoves(ChessBoard* chessBoard, TranspositionTable* transpositionTable, MoveList* moveList, GradedMoveList* gradedMoveList, int depth);
void gradeTacticalMoves(ChessBoard* chessBoard, MoveList* moveList, GradedMoveList* gradedMoveList); 
void initCaptureScores();