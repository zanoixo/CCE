#pragma once
#include <stdint.h>

typedef struct ChessBoard ChessBoard;
typedef struct Move Move;

#define HISTORY_SIZE 1024

typedef struct MoveHistory
{
    uint64_t positionHashes[HISTORY_SIZE];
    int lastIrreversableIndex[HISTORY_SIZE];
    int size;
}MoveHistory;

int isThreeFoldRepetition(ChessBoard* chessBoard);
void addMoveToHistory(ChessBoard* chessBoard, Move* move);
void removeMovefromHistory(ChessBoard* chessBoard);