#pragma once
#include <stdint.h>

#define FILE_A_BASE 0x0101010101010101ULL
#define aFile (FILE_A_BASE << 0)
#define bFile (FILE_A_BASE << 1)
#define cFile (FILE_A_BASE << 2)
#define dFile (FILE_A_BASE << 3)
#define eFile (FILE_A_BASE << 4)
#define fFile (FILE_A_BASE << 5)
#define gFile (FILE_A_BASE << 6)
#define hFile (FILE_A_BASE << 7)

static const uint64_t files[8] = {aFile, bFile, cFile, dFile, eFile, fFile, gFile, hFile};

#define line1 (0xFFULL)
#define line2 (0xFFULL << 8)
#define line3 (0xFFULL << 16)
#define line4 (0xFFULL << 24)
#define line5 (0xFFULL << 32)
#define line6 (0xFFULL << 40)
#define line7 (0xFFULL << 48)
#define line8 (0xFFULL << 56)

#define whiteKingSideInnerPawnShield  (0xE0ULL << 8)
#define whiteKingSideOuterPawnShield  (0xE0ULL << 16)
#define whiteKingSideCastleSquares    (0xE0E0ULL)

#define whiteQueenSideInnerPawnShield (0x0EULL << 8)
#define whiteQueenSideOuterPawnShield (0x0EULL << 16)
#define whiteQueenSideCastleSquares   (0x0F0FULL)

#define blackKingSideInnerPawnShield  (0xE0ULL << 48)
#define blackKingSideOuterPawnShield  (0xE0ULL << 40)
#define blackKingSideCastleSquares    ((0xE0ULL << 56) | (0xE0ULL << 48))

#define blackQueenSideInnerPawnShield (0x0EULL << 48)
#define blackQueenSideOuterPawnShield (0x0EULL << 40)
#define blackQueenSideCastleSquares   ((0x0FULL << 56) | (0x0FULL << 48))

#define a1 (1ULL << 0)
#define b1 (1ULL << 1)
#define c1 (1ULL << 2)
#define d1 (1ULL << 3)
#define e1 (1ULL << 4)
#define f1 (1ULL << 5)
#define g1 (1ULL << 6)
#define h1 (1ULL << 7)

#define a8 (1ULL << 56)
#define b8 (1ULL << 57)
#define c8 (1ULL << 58)
#define d8 (1ULL << 59)
#define e8 (1ULL << 60)
#define f8 (1ULL << 61)
#define g8 (1ULL << 62)
#define h8 (1ULL << 63)

#define a1Sq 0
#define b1Sq 1
#define c1Sq 2
#define d1Sq 3
#define e1Sq 4
#define f1Sq 5
#define g1Sq 6
#define h1Sq 7

#define a8Sq 56
#define b8Sq 57
#define c8Sq 58
#define d8Sq 59
#define e8Sq 60
#define f8Sq 61
#define g8Sq 62
#define h8Sq 63