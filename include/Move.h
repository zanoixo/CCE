#pragma once

#include <stdint.h>
#include "Utils.h"

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

static const uint8_t promotionFlagToPiece[5] =
{
    [0]               = whitePawn,
    [knightPromotion] = whiteKnight,
    [bishopPromotion] = whiteBishop,
    [rookPromotion]   = whiteRook,
    [queenPromotion]  = whiteQueen
};

static inline uint8_t getPromotionPiece(Move move)
{
    return (move.move & promotionMask) >> promotionPosition;
}

static inline uint8_t getFromSq(uint16_t move)
{
    return (move & fromMask) >> fromPosition;
}

static inline uint8_t getToSq(uint16_t move)
{
    return (move & toMask) >> toPosition;
}

static inline uint64_t getFromBitboard(uint16_t move)
{
    return 1ULL << ((move & fromMask) >> fromPosition);
}

static inline uint64_t getToBitboard(uint16_t move)
{
    return 1ULL << ((move & toMask) >> toPosition);
}

static inline uint8_t isTacticalMove(uint8_t capturedPiece, Move move)
{    
    return (capturedPiece != empty) || getPromotionPiece(move) || move.move & enPassantMask;
}

static inline uint16_t constructMove(uint64_t from, uint64_t to, uint16_t promotionFlag, uint16_t enPassantFlag)
{
    uint16_t move = 0;
    move |= getSqInd(from) << fromPosition;
    move |= getSqInd(to) << toPosition;
    move |= promotionFlag << promotionPosition;
    move |= enPassantFlag << enPassantPosition;

    return move; 
}

static inline void moveToText(char* moveStr, Move move)
{
    int fromSq = getFromSq(move.move);
    int toSq   = getToSq(move.move);

    moveStr[0] = 'a' + (fromSq % 8);
    moveStr[1] = '1' + (fromSq / 8);

    moveStr[2] = 'a' + (toSq % 8);
    moveStr[3] = '1' + (toSq / 8);

    if (getPromotionPiece(move))
    {
        switch (getPromotionPiece(move))
        {
            case queenPromotion:
                moveStr[4] = 'q';
                break;

            case rookPromotion:
                moveStr[4] = 'r';
                break;

            case bishopPromotion:
                moveStr[4] = 'b';
                break;

            case knightPromotion:
                moveStr[4] = 'n';
                break;

            default:
                moveStr[4] = 'q';
                break;
        }

        moveStr[5] = '\0';
    }
    else
    {
        moveStr[4] = '\0';
    }
}