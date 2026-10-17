#include "ChessClock.h"
#include <string.h>
#include <stdlib.h>

static int64_t ExtractValue(char* line, char* key) 
{
    char *ptr = strstr(line, key);
    if (!ptr) {
        return -1;
    }
    return (int64_t)strtoll(ptr + strlen(key), NULL, 10);
}

void ParseTime(char* line, ChessClock* clock) 
{

    clock->movetime  = -1;
    clock->wtime     = -1;
    clock->btime     = -1;
    clock->winc      = -1;
    clock->binc      = -1;

    clock->movetime  = ExtractValue(line, "movetime");
    clock->wtime     = ExtractValue(line, "wtime");
    clock->btime     = ExtractValue(line, "btime");
    clock->winc      = ExtractValue(line, "winc");
    clock->binc      = ExtractValue(line, "binc");

    if (clock->wtime >= 0 && clock->winc < 0) {
        clock->winc = 0;
    }
    if (clock->btime >= 0 && clock->binc < 0) {
        clock->binc = 0;
    }
}

uint64_t GetTimeLimit(uint64_t allocatedTime, uint64_t minTime, uint64_t maxTime) 
{

    if (allocatedTime < minTime)
    {
        return minTime;
    } 
    if (allocatedTime > maxTime)
    {
        return maxTime;
    } 

    return allocatedTime;
}

uint64_t CalculateTime(ChessClock* clock, int isBlack, int moveNumber) 
{

    if (clock->movetime >= 0)
    {
        int64_t moveTime = clock->movetime - LATENCY_BUFFER;
        return GetTimeLimit(moveTime, MIN_MOVE_TIME_MS, moveTime);
    }

    if (clock->wtime >= 0 && clock->btime >= 0) 
    {
        int64_t timeLeft = clock->wtime;
        int64_t increment = clock->winc;

        if (isBlack)
        {
            timeLeft = clock->btime;
            increment = clock->binc;
        }

        if (timeLeft < 0)
        {
            timeLeft = 0;
        } 

        if (increment < 0) 
        {
            increment = 0;
        } 

        int movesLeft = DEFAULT_MOVES_LEFT - moveNumber;

        if (movesLeft < 10) 
        {
            movesLeft = 10;
        }

        double moveTime = ((double)timeLeft / movesLeft) + ((double)increment * INCREMENT_SAFETY_FACTOR) - LATENCY_BUFFER;

        double maxTime = (double)timeLeft * MAX_FRACTION_OF_TIME;

        return GetTimeLimit(moveTime, MIN_MOVE_TIME_MS, maxTime);
    }

    return 10000;
}