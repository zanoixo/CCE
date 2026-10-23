#pragma once

#include "Utils.h"

void penalizeHistoryHeuristic(uint16_t move, uint8_t piece, int remeniningDepth);
void updateHistoryHeuristic(uint16_t move, uint8_t piece, int remeniningDepth);
int getHistoryHeuristic(uint16_t move, uint8_t piece);
void clearHistoryHeuristic();