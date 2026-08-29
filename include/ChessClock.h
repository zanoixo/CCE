#pragma once

#include <stdint.h>

#define MIN_MOVE_TIME_MS        50
#define DEFAULT_MOVES_LEFT      40
#define MAX_FRACTION_OF_TIME    0.10
#define INCREMENT_SAFETY_FACTOR 0.85
#define LATENCY_BUFFER          100
 
typedef struct ChessClock{
    int64_t movetime;
    int64_t wtime;
    int64_t btime;
    int64_t winc;
    int64_t binc;
} ChessClock;
 
 
void ParseTime(char* line, ChessClock* clock);
 
uint64_t CalculateTime(ChessClock* clock, int isWhiteToMove, int moveNumber);