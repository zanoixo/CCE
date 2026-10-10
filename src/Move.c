#include "Move.h"
#include "Utils.h"
#include "ChessBoard.h"



uint16_t constructMove(uint64_t from, uint64_t to, uint16_t promotionFlag, uint16_t enPassantFlag)
{
    uint16_t move = 0;
    move |= getSqInd(from) << fromPosition;
    move |= getSqInd(to) << toPosition;
    move |= promotionFlag << promotionPosition;
    move |= enPassantFlag << enPassantPosition;

    return move; 
}

