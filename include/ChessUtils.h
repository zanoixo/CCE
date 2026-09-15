#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARD_SIZE 64
#define MAX_INT 1000000000
#define MIN_INT -1000000000
#define MATED -1000000
#define MATED_TRESHOLD (-MATED - 1000)
#define DRAW 0 

enum Piece
{
    pawn = 1,
    knight = 2,
    bishop = 3,
    rook = 4,
    queen = 5,
    king = 6
};

enum color
{
    white = 0,
    black = 1
};

void showBitBoard(uint64_t bitBoard);
void sendError(char errorMsg[]);
uint64_t getTimeMs();
uint8_t getSqInd(uint64_t sq);
