#pragma once

#include <stdint.h>

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct ChessBoard ChessBoard; 

void makeMove(ChessBoard *chessBoard, uint16_t move, TranspositionTableHashes* hashes);
void makeNullMove(ChessBoard* chessBoard, TranspositionTableHashes* hashes);