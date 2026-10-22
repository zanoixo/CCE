#include "Move.h"
#include <string.h>

int historyHeuristic[BOARD_SIZE][BOARD_SIZE][PIECE_TYPES];

void penalizeHistoryHeuristic(Move move, uint8_t piece, int remeniningDepth)
{
    historyHeuristic[getFromSq(move.move)][getToSq(move.move)][piece] -= remeniningDepth;     
}

void updateHistoryHeuristic(Move move, uint8_t piece, int remeniningDepth)
{
    historyHeuristic[getFromSq(move.move)][getToSq(move.move)][piece] += remeniningDepth * remeniningDepth; 
}

int getHistoryHeuristic(Move move, uint8_t piece)
{
    return historyHeuristic[getFromSq(move.move)][getToSq(move.move)][piece];
}

void clearHistoryHeuristic()
{
    memset(historyHeuristic, 0, sizeof(historyHeuristic));
}

