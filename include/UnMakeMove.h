#pragma once

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct ChessBoard ChessBoard; 
typedef struct Move Move;

void unMakeMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes);
void unMakeNullMove(ChessBoard* chessBoard, Move* move, TranspositionTableHashes* hashes);