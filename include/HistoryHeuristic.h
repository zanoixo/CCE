#pragma once

#include "Utils.h"

#define MAX_HISTORY_SCORE 16383
#define MIN_HISOTRY_SCORE -16384

void penalizeHistoryHeuristic(uint16_t move, uint8_t piece, int remeniningDepth);
void updateHistoryHeuristic(uint16_t move, uint8_t piece, int remeniningDepth);
int getHistoryHeuristic(uint16_t move, uint8_t piece);
void clearHistoryHeuristic();