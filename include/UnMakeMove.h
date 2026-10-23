#pragma once

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct ChessBoard ChessBoard; 

void unMakeMove(ChessBoard *chessBoard, uint16_t move);
void unMakeNullMove(ChessBoard* chessBoard);