#include "Move.h"
#include "Utils.h"

uint8_t getCapturedPiece(Move move)
{
    return (move.flags & capturePieceMask) >> captureFlagPostion;
}

uint8_t getPromotionPiece(Move move)
{
    return (move.flags & promotionPieceMask) >> promotionFlagPosition;
}

uint8_t getPiece(Move move)
{
    return (move.flags & pieceMask) >> pieceFlagPosition;
}

uint32_t constructMove(uint64_t from, uint64_t to)
{
    uint32_t move = 0;
    move |= getSqInd(from) << fromPosition;
    move |= getSqInd(to) << toPosition;
    return move; 
}

uint8_t getFromSq(uint32_t move)
{
    return (move & fromMask) >> fromPosition;
}

uint8_t getToSq(uint32_t move)
{
    return (move & toMask) >> toPosition;
}

uint64_t getFromBitboard(uint32_t move)
{
    return 1ULL << ((move & fromMask) >> fromPosition);
}

uint64_t getToBitboard(uint32_t move)
{
    return 1ULL << ((move & toMask) >> toPosition);
}