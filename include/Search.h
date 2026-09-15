#pragma once

#include <stdint.h>
#include "MoveGenerator.h"

typedef struct ChessBoard ChessBoard;
typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct TranspositionTable TranspositionTable;
typedef struct TranspositionTableEntry TranspositionTableEntry;

#define KILLER_MOVE_DEPTH 256
#define TIME_CHECK 2047

#define NULL_MOVE_SKIP 2

MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, uint64_t timePerMove);
MoveScore negamax(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, int depthSearched, int mateDistance, int alpha, int beta, int side);
MoveScore qsearch(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, int depthSearched, int mateDistance, int alpha, int beta, int side);
void clearHistoryHeuristic();
