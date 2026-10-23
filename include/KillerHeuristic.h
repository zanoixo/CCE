#pragma once

#define KILLER_MOVE_DEPTH 256

typedef struct Move Move;

static Move killerMoves[KILLER_MOVE_DEPTH][2];

void initKillerMoves(int currentDepth);
void setKillerMove(Move killerMove, int depth);