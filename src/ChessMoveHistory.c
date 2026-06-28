#include "ChessMoveHistory.h"
#include "ChessBoard.h"
#include "ChessMoveGenerator.h"

int isThreeFoldRepetition(ChessBoard* chessBoard)
{
    int repetitionCounter = 0;

    int index = chessBoard->history.size - 1;

    for (int i = index; i >= chessBoard->history.lastIrreversableIndex[index]; i -= 2)
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

void addMoveToHistory(ChessBoard* chessBoard, Move* move)
{
    int index = chessBoard->history.size;

    chessBoard->history.positionHashes[index] = chessBoard->positionHash;

    uint8_t piece = getPiece(move->flags);

    if (getCapturedPiece(move->flags) || piece == pawn)
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