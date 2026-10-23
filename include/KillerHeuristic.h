#pragma once

#define KILLER_MOVE_DEPTH 256

static uint16_t killerMoves[KILLER_MOVE_DEPTH][2];

void initKillerMoves(int currentDepth);
void setKillerMove(uint16_t killerMove, int depth);