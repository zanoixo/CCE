#pragma once

#include "Utils.h"

typedef struct Move Move;

void penalizeHistoryHeuristic(Move move, uint8_t piece, int remeniningDepth);
void updateHistoryHeuristic(Move move, uint8_t piece, int remeniningDepth);
int getHistoryHeuristic(Move move, uint8_t piece);
void clearHistoryHeuristic();