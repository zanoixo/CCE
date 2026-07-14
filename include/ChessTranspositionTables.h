#pragma once

#include <stdint.h>
#include "ChessUtils.h"
#include "ChessEval.h"

#define DIFFERENT_PIECE_COUNT 12
#define CASTLE_RIGHT_COUNT 4
#define ENPASSANT_FILES_COUNT 8
#define TRANSPOSITION_TABLE_NUM_OF_BITS 20
#define TRANSPOSITION_SCORE 10000000
#define UNINITIALIZED -2
#define QSEARCH -1

enum pieceHashes
{
    whitePawnHash = 0,
    whiteKnightHash = 1,
    whiteBishopHash = 2,
    whiteRookHash = 3,
    whiteQueenHash = 4,
    whiteKingHash = 5,

    blackPawnHash = 6,
    blackKnightHash = 7,
    blackBishopHash = 8,
    blackRookHash = 9,
    blackQueenHash = 10,
    blackKingHash = 11,  
};

enum castellingHashes
{
    whiteShortCastleHash = 0,
    whiteLongCastleHash = 1,
    blackShortCastleHash = 2,
    blackLongCastleHash = 3
};

enum flags
{
    alphaCutoff = 0,
    betaCutoff = 1,
    exactCutoff = 2
};

typedef struct TranspositionTableHashes
{
    uint64_t colorHash;
    uint64_t pieceHashes[DIFFERENT_PIECE_COUNT][BOARD_SIZE];
    uint64_t castellingHashes[CASTLE_RIGHT_COUNT];
    uint64_t enPassantHashes[ENPASSANT_FILES_COUNT];
}TranspositionTableHashes;

typedef struct TranspositionTableEntry
{
    uint64_t hash;
    int16_t depth;
    uint8_t flag;
    uint16_t age;
    MoveScore moveScore;
    
}TranspositionTableEntry;

typedef struct TranspositionTable
{
    TranspositionTableEntry transpositions[1 << TRANSPOSITION_TABLE_NUM_OF_BITS];
}TranspositionTable;

TranspositionTableHashes* initTranpositionTableHashes();
TranspositionTable* initTranpositionTable();
void clearTranspositionTable(TranspositionTable* transpositionTable);
TranspositionTableEntry* getTransposition(ChessBoard* chessBoard, TranspositionTable* transpositionTable, int remainingDepth, int isEvalOnly);
void setTransposition(ChessBoard* chessBoard, TranspositionTable* transpositionTable, int remainingDepth, MoveScore* moveScore, int alpha, int beta);
TranspositionTableEntry* checkTranspositionHit(ChessBoard* chessBoard, TranspositionTable* transpositionTable, int remainingDepth, int alpha, int beta);
void setScoreToTranspositionMove(ChessBoard* chessBoard, MoveList* moveList, TranspositionTable* transpositionTable);
void initAge();
void incrementAge();
uint16_t getCurrentAge();
uint64_t getTTMovesSearched();
uint64_t getTTMovesFound();