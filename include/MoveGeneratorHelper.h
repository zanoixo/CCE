#pragma once

int calculateCaptureMoveScore(ChessBoard* chessBoard, uint8_t fromSq, uint8_t toSq);
void addMove(uint64_t from, uint64_t to, uint16_t promotionFlag, uint16_t enPassantFlag, MoveList* moveList, int score);
void generatePawnPromotionMoves(uint64_t from, uint64_t to, MoveList* moveList);
