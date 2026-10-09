#include "Move.h"
#include "Utils.h"
#include "ChessBoard.h"

uint8_t getPromotionPiece(Move move)
{
    return (move.move & promotionMask) >> promotionPosition;
}

uint16_t constructMove(uint64_t from, uint64_t to, uint16_t promotionFlag, uint16_t enPassantFlag)
{
    uint16_t move = 0;
    move |= getSqInd(from) << fromPosition;
    move |= getSqInd(to) << toPosition;
    move |= promotionFlag << promotionPosition;
    move |= enPassantFlag << enPassantPosition;

    return move; 
}

uint8_t getFromSq(uint16_t move)
{
    return (move & fromMask) >> fromPosition;
}

uint8_t getToSq(uint16_t move)
{
    return (move & toMask) >> toPosition;
}

uint64_t getFromBitboard(uint16_t move)
{
    return 1ULL << ((move & fromMask) >> fromPosition);
}

uint64_t getToBitboard(uint16_t move)
{
    return 1ULL << ((move & toMask) >> toPosition);
}