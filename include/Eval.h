#pragma once

#include <stdint.h>
#include "Utils.h"

typedef struct MoveScore MoveScore;
typedef struct ChessBoard ChessBoard;
typedef struct AttackTables AttackTables;
typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct TranspositionTable TranspositionTable;

#define PAWN_VALUE   100
#define KNIGHT_VALUE 310
#define BISHOP_VALUE 330
#define ROOK_VALUE   500
#define QUEEN_VALUE  900
#define KING_VALUE   0

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
#define ROOK_OPEN_FILE_VALUE 20
#define ROOK_SEMIOPEN_FILE_VALUE 10
#define ROOK_ON_KING_FILE_VALUE 10

int evaluatePosition(ChessBoard* chessBoard, AttackTables* attackTables);
void initPassedPawnMasks();
void initIsolatedPawnMasks();

static const int pieceValues[13] =
{
    [whitePawn]   = PAWN_VALUE,
    [whiteKnight] = KNIGHT_VALUE,
    [whiteBishop] = BISHOP_VALUE,
    [whiteRook]   = ROOK_VALUE,
    [whiteQueen]  = QUEEN_VALUE,
    [whiteKing]   = KING_VALUE,
    
    [blackPawn]   = PAWN_VALUE,
    [blackKnight] = KNIGHT_VALUE,
    [blackBishop] = BISHOP_VALUE,
    [blackRook]   = ROOK_VALUE,
    [blackQueen]  = QUEEN_VALUE,
    [blackKing]   = KING_VALUE,
    [empty]       = 0
};

static inline int getPieceScore(uint8_t piece)
{
    return pieceValues[piece];
}