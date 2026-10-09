#pragma once

#include <stdint.h>

#define EMPTY_PROMOTION_FLAG 0
#define EMPTY_ENPASSANT_FLAG 0

#define ENPASSANT_PRESENT_FLAG 1

typedef struct Move
{
    uint16_t move;
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

enum MovePosition
{
    fromPosition = 0,
    toPosition = 6,
    promotionPosition = 12,
    enPassantPosition = 15,
};

enum MoveMasks
{
    fromMask      = 0b0000000000111111,
    toMask        = 0b0000111111000000,
    promotionMask = 0b0111000000000000,
    enPassantMask = 0b1000000000000000,
};

uint8_t getPromotionPiece(Move move);
uint16_t constructMove(uint64_t from, uint64_t to, uint16_t promotionFlag, uint16_t enPassantFlag);
uint8_t getFromSq(uint16_t move);
uint8_t getToSq(uint16_t move);
uint64_t getFromBitboard(uint16_t move);
uint64_t getToBitboard(uint16_t move);
