#pragma once

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct ChessBoard ChessBoard; 
typedef struct Move Move;

void unMakeMove(ChessBoard *chessBoard, Move *move);
void unMakeNullMove(ChessBoard* chessBoard);