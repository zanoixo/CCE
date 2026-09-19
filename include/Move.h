#pragma once

#include <stdint.h>

typedef struct Move
{
    uint32_t move;
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
    pieceMask                  = 0b011100000000000,
};

enum MovePosition
{
    fromPosition = 0,
    toPosition = 6
};

enum MoveMasks
{
    fromMask = 0b0000000000111111,
    toMask   = 0b0000111111000000
};

enum MoveFlagsPosition
{
    promotionFlagPosition = 0,
    captureFlagPostion = 3,
    enPassantFlagPosition = 6,
    pieceFlagPosition = 11,
};

uint8_t getCapturedPiece(Move move);
uint8_t getPromotionPiece(Move move);
uint8_t getPiece(Move move);
uint32_t constructMove(uint64_t from, uint64_t to);
uint8_t getFromSq(uint32_t move);
uint8_t getToSq(uint32_t move);
uint64_t getFromBitboard(uint32_t move);
uint64_t getToBitboard(uint32_t move);
