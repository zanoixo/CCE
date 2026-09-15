#include "Move.h"

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