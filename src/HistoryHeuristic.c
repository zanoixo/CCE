#include "Move.h"
#include "HistoryHeuristic.h"
#include <string.h>

int16_t historyHeuristic[BOARD_SIZE][BOARD_SIZE][PIECE_TYPES];

void penalizeHistoryHeuristic(uint16_t move, uint8_t piece, int remeniningDepth)
{
    int newScore = historyHeuristic[getFromSq(move)][getToSq(move)][piece] - remeniningDepth;
    historyHeuristic[getFromSq(move)][getToSq(move)][piece] = newScore < MIN_HISOTRY_SCORE ? MIN_HISOTRY_SCORE : newScore;     
}

void updateHistoryHeuristic(uint16_t move, uint8_t piece, int remeniningDepth)
{
    int newScore = historyHeuristic[getFromSq(move)][getToSq(move)][piece] + remeniningDepth * remeniningDepth;
    historyHeuristic[getFromSq(move)][getToSq(move)][piece] = newScore > MAX_HISTORY_SCORE ? MAX_HISTORY_SCORE : newScore;
}

int getHistoryHeuristic(uint16_t move, uint8_t piece)
{
    return historyHeuristic[getFromSq(move)][getToSq(move)][piece];
}

void clearHistoryHeuristic()
{
    memset(historyHeuristic, 0, sizeof(historyHeuristic));
}