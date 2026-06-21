#pragma once
#include <stdint.h>

typedef struct ChessBoard ChessBoard;

#define HISTORY_SIZE 256

typedef struct MoveHistory
{
    uint64_t positionHashes[256];
    int size;
}MoveHistory;

int isThreeFoldRepetition(ChessBoard* chessBoard);
void addMoveToHistory(ChessBoard* chessBoard);
void removeMovefromHistory(ChessBoard* chessBoard);