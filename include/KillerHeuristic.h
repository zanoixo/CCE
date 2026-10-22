#pragma once

#define KILLER_MOVE_DEPTH 256

void initKillerMoves(int currentDepth);
void findKillerMoves(MoveList *moveList, int depth);
void setKillerMove(Move killerMove, int depth);