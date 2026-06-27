#include "ChessMoveHistory.h"
#include "ChessBoard.h"

int isThreeFoldRepetition(ChessBoard* chessBoard)
{
    int repetitionCounter = 0;

    for (int i = chessBoard->history.size - 1; i >= 0; i -= 2)
    {
        if (chessBoard->history.positionHashes[i] == chessBoard->positionHash)
        {
            repetitionCounter++;

            if (repetitionCounter == 3)
            {
                return 1;
            }
        }
        
    }
    
    return 0;
}

void addMoveToHistory(ChessBoard* chessBoard)
{
    chessBoard->history.positionHashes[chessBoard->history.size] = chessBoard->positionHash;
    chessBoard->history.size++;
}

void removeMovefromHistory(ChessBoard* chessBoard)
{
    chessBoard->history.size--;
}