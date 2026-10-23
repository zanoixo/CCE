#include "Utils.h"
#include "Move.h"
#include "KillerHeuristic.h"

void initKillerMoves(int currentDepth)
{
    for (int i = 0; i < currentDepth; i++)
    {
        killerMoves[i][0] = 0;
        killerMoves[i][1] = 0;
    }
}

void setKillerMove(uint16_t killerMove, int depth)
{
    if (!(killerMoves[depth][0] == killerMove) &&
        !(killerMoves[depth][1] == killerMove))
    {
        killerMoves[depth][1] = killerMoves[depth][0];
        killerMoves[depth][0] = killerMove;
    } 
}