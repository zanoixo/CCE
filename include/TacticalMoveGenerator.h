#pragma once

#include "Utils.h"
#include "Move.h"

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct ChessBoard ChessBoard;
typedef struct AttackTables AttackTables; 

void generateTacticalMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);