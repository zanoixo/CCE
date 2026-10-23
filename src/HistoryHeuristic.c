#include "Move.h"
#include <string.h>

int historyHeuristic[BOARD_SIZE][BOARD_SIZE][PIECE_TYPES]; //clamp and change to int16_t

void penalizeHistoryHeuristic(uint16_t move, uint8_t piece, int remeniningDepth)
{
    historyHeuristic[getFromSq(move)][getToSq(move)][piece] -= remeniningDepth;     
}

void updateHistoryHeuristic(uint16_t move, uint8_t piece, int remeniningDepth)
{
    historyHeuristic[getFromSq(move)][getToSq(move)][piece] += remeniningDepth * remeniningDepth; 
}

int getHistoryHeuristic(uint16_t move, uint8_t piece)
{
    return historyHeuristic[getFromSq(move)][getToSq(move)][piece];
}

void clearHistoryHeuristic()
{
    memset(historyHeuristic, 0, sizeof(historyHeuristic));
}

