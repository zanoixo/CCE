#include "Utils.h"
#include "Move.h"
#include "KillerHeuristic.h"

Move killerMoves[KILLER_MOVE_DEPTH][2];

void initKillerMoves(int currentDepth)
{
    for (int i = 0; i < currentDepth; i++)
    {
        killerMoves[i][0] = (Move){0, 0};
        killerMoves[i][1] = (Move){0, 0};
    }
}

void findKillerMoves(MoveList *moveList, int depth)
{
    for (int i = 0; i < moveList->nextIndex; i++)
    {
        if (moveList->moves[i].move == killerMoves[depth][0].move)
        {
            moveList->moves[i].score = 200;
        }

        if (moveList->moves[i].move == killerMoves[depth][1].move)
        {
            moveList->moves[i].score = 100;
        }
        
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