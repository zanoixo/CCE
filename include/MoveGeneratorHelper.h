#pragma once

void addMove(uint64_t from, uint64_t to, uint16_t promotionFlag, uint16_t enPassantFlag, MoveList* moveList);
void generatePawnPromotionMoves(uint64_t from, uint64_t to, MoveList* moveList);
