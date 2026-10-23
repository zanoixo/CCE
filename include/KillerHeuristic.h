#pragma once

#define KILLER_MOVE_DEPTH 256

void initKillerMoves(int currentDepth);
void setKillerMove(uint16_t killerMove, int depth);
uint16_t getKillerMove(int depth, int index);