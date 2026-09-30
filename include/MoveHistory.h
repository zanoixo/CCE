#pragma once
#include <stdint.h>

typedef struct ChessBoard ChessBoard;
typedef struct MoveData MoveData;
typedef struct Move Move;

#define HISTORY_SIZE 1024

typedef struct MoveHistory
{
    uint64_t positionHashes[HISTORY_SIZE];
    uint64_t enPassantList[HISTORY_SIZE];
    int lastIrreversableIndex[HISTORY_SIZE];
    int size;
}MoveHistory;

int isThreeFoldRepetition(ChessBoard* chessBoard);
void addMoveToHistory(ChessBoard* chessBoard, MoveData* moveData, uint8_t piece);
void removeMovefromHistory(ChessBoard* chessBoard);