#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARD_SIZE 64
#define GENERIC_PIECE_TYPES 6
#define PIECE_TYPES 12
#define COLORS 2
#define MAX_INT 1000000000
#define MIN_INT -1000000000
#define MATED -1000000
#define MATED_TRESHOLD (-MATED - 1000)
#define DRAW 0 

enum ColoredPiece
{
    whitePawn = 0,
    whiteKnight = 1,
    whiteBishop = 2,
    whiteRook = 3,
    whiteQueen = 4,
    whiteKing = 5,

    blackPawn = 6,
    blackKnight = 7,
    blackBishop = 8,
    blackRook = 9,
    blackQueen = 10,
    blackKing = 11,
    empty = 12,
}; 


enum color
{
    white = 0,
    black = 1
};

void showBitBoard(uint64_t bitBoard);
void sendError(char errorMsg[]);

static inline uint8_t getSqInd(uint64_t sq)
{
    return __builtin_ctzll(sq);
}

static inline int countPieces(uint64_t bitboard)
{
    int count = 0;

    while (bitboard)
    {
        count++;
        bitboard &= bitboard - 1;
    }

    return count;
}

#ifdef _WIN32
#include <windows.h>

static inline uint64_t getTimeMs()
{
    return GetTickCount64();
}

#else
#include <time.h>

static inline uint64_t getTimeMs()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (uint64_t)ts.tv_sec * 1000ULL +
           (uint64_t)ts.tv_nsec / 1000000ULL;
}

#endif