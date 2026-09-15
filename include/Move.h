#pragma once

#include <stdint.h>

typedef struct Move
{
    uint64_t from;
    uint64_t to;
    uint64_t prevEnPassantSq;
    uint16_t flags;
    int score;
}Move;

typedef struct MoveList
{
    Move* moves;
    int nextIndex;
}MoveList;

typedef struct MoveScore
{
    int eval;
    Move move;
}MoveScore;

enum PromotionPieces
{
    queenPromotion = 1,
    rookPromotion = 2,
    bishopPromotion = 3,
    knightPromotion = 4,
    numOfPromotionPieces = 5
};

enum MoveFlags
{
    promotionPieceMask         = 0b000000000000111,
    capturePieceMask           = 0b000000000111000,
    enPassantMask              = 0b000000001000000,
    removeWhiteShortCastleFlag = 0b000000010000000,
    removeWhiteLongCastleFlag  = 0b000000100000000,
    removeBlackShortCastleFlag = 0b000001000000000,
    removeBlackLongCastleFlag  = 0b000010000000000,
    pieceMask                  = 0b011100000000000,
    castleMask                 = 0b100000000000000
};

enum MoveFlagsPosition
{
    promotionFlagPosition = 0,
    captureFlagPostion = 3,
    enPassantFlagPosition = 6,
    removeWhiteShortCastleFlagPosition = 7,
    removeWhiteLongCastleFlagPosition = 8,
    removeBlackShortCastleFlagPosition = 9,
    removeBlackLongCastleFlagPosition = 10,
    pieceFlagPosition = 11,
    castleFlagPosition = 14
};

uint8_t getCapturedPiece(Move move);
uint8_t getPromotionPiece(Move move);
uint8_t getPiece(Move move);