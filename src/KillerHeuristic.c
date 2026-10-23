#include "Utils.h"
#include "Move.h"
#include "KillerHeuristic.h"

void initKillerMoves(int currentDepth)
{
    for (int i = 0; i < currentDepth; i++)
    {
        killerMoves[i][0] = (Move){0, 0};
        killerMoves[i][1] = (Move){0, 0};
    }
}

void setKillerMove(Move killerMove, int depth)
{
    if (!(killerMoves[depth][0].move == killerMove.move) &&
        !(killerMoves[depth][1].move == killerMove.move))
    {
        killerMoves[depth][1] = killerMoves[depth][0];
        killerMoves[depth][0] = killerMove;
    } 
}