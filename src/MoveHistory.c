#include "MoveHistory.h"
#include "ChessBoard.h"
#include "MoveGenerator.h"

int isThreeFoldRepetition(ChessBoard* chessBoard)
{
    int repetitionCounter = 0;

    int index = chessBoard->history.size - 1;

    for (int i = index; i >= chessBoard->history.lastIrreversableIndex[index]; i -= 2)
    {
        if (chessBoard->history.positionHashes[i] == chessBoard->positionHash)
        {
            repetitionCounter++;

            if (repetitionCounter == 2)
            {
                return 1;
            }
        }
        
    }
    
    return 0;
}

void addMoveToHistory(ChessBoard* chessBoard, MoveData* moveData, uint8_t piece)
{
    int index = chessBoard->history.size;

    chessBoard->history.positionHashes[index] = chessBoard->positionHash;

    if (moveData->capturedPiece || piece == pawn)
    {
        chessBoard->history.lastIrreversableIndex[index] = index;
    }
    else
    {
        if (index != 0)
        {
            chessBoard->history.lastIrreversableIndex[index] = chessBoard->history.lastIrreversableIndex[index - 1];
        }

    }

    chessBoard->history.size++;
}

void removeMovefromHistory(ChessBoard* chessBoard)
{
    chessBoard->history.size--;
}