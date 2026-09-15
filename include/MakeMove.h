#pragma once

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct ChessBoard ChessBoard; 
typedef struct Move Move;

void makeMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes);
void makeNullMove(ChessBoard* chessBoard, Move* move, TranspositionTableHashes* hashes);