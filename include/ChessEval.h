#pragma once

#include <stdint.h>
#include "ChessMoveGenerator.h"

typedef struct ChessBoard ChessBoard;
typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct TranspositionTable TranspositionTable;
typedef struct TranspositionTableEntry TranspositionTableEntry;

#define KILLER_MOVE_DEPTH 256
#define TIME_CHECK 2047

#define MAX_INT 1000000000
#define MIN_INT -1000000000
#define MATED -1000000
#define MATED_TRESHOLD (-MATED - 1000)
#define DRAW 0 

#define PAWN_VALUE   100
#define KNIGHT_VALUE 310
#define BISHOP_VALUE 330
#define ROOK_VALUE   500
#define QUEEN_VALUE  900
#define KING_VALUE  2000
#define QUEEN_PROMOTION_VALUE 500000
#define ROOK_PROMOTION_VALUE 400000
#define KNIGHT_PROMOTION_VALUE 300000
#define BISHOP_PROMOTION_VALUE 200000
#define INNER_CENTER_VALUE 20
#define OUTER_CENTER_VALUE 10
#define KNIGHT_MOBILITY_VALUE 2
#define BISHOP_MOBILITY_VALUE 2
#define ROOK_MOBILITY_VALUE 2
#define QUEEN_MOBILITY_VALUE 1
#define BISHOP_PAIR_VALUE 30
#define DOUBLED_PAWN_PENALTY 15
#define KING_CASTLED_VALUE 25
#define PASSED_PAWN_SCORE 10
#define ISOLATED_PAWN_PENALTY 10
#define INNER_PAWN_WALL_VALUE 10
#define OUTER_PAWN_WALL_VALUE 6
#define PAWN_WALL_MISSING_PENALTY 12
#define OPEN_FILE_IN_WALL 18
#define KING_SAFETY_CUTOFF 1350

#define NULL_MOVE_SKIP 2


typedef struct MoveScore
{
    int eval;
    Move move;
}MoveScore;


MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, uint64_t timePerMove);
MoveScore negamax(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, int depthSearched, int mateDistance, int alpha, int beta, int side);
MoveScore qsearch(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, int depthSearched, int mateDistance, int alpha, int beta, int side);
void initPassedPawnMasks();
void initIsolatedPawnMasks();
void clearHistoryHeuristic();
