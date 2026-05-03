#include <stdio.h>
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"

const uint64_t hFile = 0b10000000ULL << 56 |
                       0b10000000ULL << 48 |
                       0b10000000ULL << 40 |
                       0b10000000ULL << 32 |
                       0b10000000ULL << 24 |
                       0b10000000ULL << 16 |
                       0b10000000ULL << 8  |
                       0b10000000ULL;

const uint64_t aFile = 0b00000001ULL << 56 |
                       0b00000001ULL << 48 |
                       0b00000001ULL << 40 |
                       0b00000001ULL << 32 |
                       0b00000001ULL << 24 |
                       0b00000001ULL << 16 |
                       0b00000001ULL << 8  |
                       0b00000001ULL;

const uint64_t gFile = 0b01000000ULL << 56 |
                       0b01000000ULL << 48 |
                       0b01000000ULL << 40 |
                       0b01000000ULL << 32 |
                       0b01000000ULL << 24 |
                       0b01000000ULL << 16 |
                       0b01000000ULL << 8  |
                       0b01000000ULL;

const uint64_t bFile = 0b00000010ULL << 56 |
                       0b00000010ULL << 48 |
                       0b00000010ULL << 40 |
                       0b00000010ULL << 32 |
                       0b00000010ULL << 24 |
                       0b00000010ULL << 16 |
                       0b00000010ULL << 8  |
                       0b00000010ULL;

int attackPatternCounter = 0;
BlockerAttackPattern attackPatterns[64][4096];

void initBlackPawnAttacks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t attackBitTable = 0;

        uint64_t pawnPosition = 1ULL << sqInd; 

        attackBitTable |= (pawnPosition >> 7) & ~aFile; //bottom left
        attackBitTable |= (pawnPosition >> 9) & ~hFile; //bottom right

        attackTables->blackPanwsAttacks[sqInd] = attackBitTable;
    }
}

void initWhitePawnAttacks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t attackBitTable = 0;

        uint64_t pawnPosition = 1ULL << sqInd;

        attackBitTable |= (pawnPosition << 9) & ~aFile; //top left
        attackBitTable |= (pawnPosition << 7) & ~hFile; //top right

        attackTables->whitePanwsAttacks[sqInd] = attackBitTable;
    }
}

void initKnightAttacks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t attackBitTable = 0;

        uint64_t knightPosition = 1ULL << sqInd;

        attackBitTable |= (knightPosition << 10) & ~(aFile | bFile); //top left corner
        attackBitTable |= (knightPosition << 17) & ~aFile;

        attackBitTable |= (knightPosition << 6) & ~(hFile | gFile); //top right corner
        attackBitTable |= (knightPosition << 15) & ~hFile;

        attackBitTable |= (knightPosition >> 6) & ~(aFile | bFile); //bottom left corner
        attackBitTable |= (knightPosition >> 15) & ~aFile;

        attackBitTable |= (knightPosition >> 10) & ~(hFile | gFile); //bottom right corner
        attackBitTable |= (knightPosition >> 17) & ~hFile;

        attackTables->knightAttacks[sqInd] = attackBitTable;
    } 
}

void initKingAttacks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t kingPosition = 1ULL << sqInd;  

        uint64_t attackBitTable = 0;
        
        attackBitTable |= (kingPosition << 8); //up
        attackBitTable |= (kingPosition >> 8); // down

        attackBitTable |= (kingPosition << 1) & ~aFile; //left
        attackBitTable |= (kingPosition >> 1) & ~hFile; //right

        attackBitTable |= (kingPosition << 9) & ~aFile; //top left
        attackBitTable |= (kingPosition << 7) & ~hFile; //top right

        attackBitTable |= (kingPosition >> 7) & ~aFile; //bottom left
        attackBitTable |= (kingPosition >> 9) & ~hFile; //bottom right

        attackTables->kingAttacks[sqInd] = attackBitTable;
    }
}

void generateRookAttackMasks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t rookPosition = 1ULL << sqInd;
        uint64_t mask = 0;

        int column = sqInd % 8;
        int row = sqInd / 8;
        int numOfBits = 0; 
        
        for (int l = 1; l < column; l++)
        {
            mask |= rookPosition >> l;
            numOfBits++;
        }

        for (int r = 1; r < 7 - column; r++)
        {
            mask |= rookPosition << r;
            numOfBits++;
        }

        for (int u = 1; u < row; u++)
        {
            mask |= rookPosition >> (u * 8);
            numOfBits++;
        }

        for (int d = 1; d < 7 - row; d++)
        {
            mask |= rookPosition << (d * 8);
            numOfBits++;
        }

        attackTables->rookMagicHashTable[sqInd].mask = mask;
        attackTables->rookMagicHashTable[sqInd].shift = BOARD_SIZE - numOfBits;
        
    }
    
}

void generateRookAttack(uint64_t blockers, int rookSqInd)
{
    BlockerAttackPattern newPattern;

    int column = rookSqInd % 8;
    int row = rookSqInd / 8;

    int left = column;
    int right = 7 - column;
    int up = 7 - row;
    int down = row;

    uint64_t attackMask = 0;
    
    for (int i = 1; i <= left; i++)
    {
        uint64_t sq = 1ULL << (rookSqInd - i);
        attackMask |= sq;
        if (sq & blockers)
        {
            break;
        }
        
    }

    for (int i = 1; i <= right; i++)
    {
        uint64_t sq = 1ULL << (rookSqInd + i);
        attackMask |= sq;

        if (sq & blockers)
        {
            break;
        }
    }

    for (int i = 1; i <= down; i++)
    {
        uint64_t sq = 1ULL << (rookSqInd - i * 8);
        attackMask |= sq;
        if (sq & blockers)
        {
            break;
        }
    }

    for (int i = 1; i <= up; i++)
    {
        uint64_t sq = 1ULL << (rookSqInd + i * 8);
        attackMask |= sq;

        if (sq & blockers)
        {
            break;
        }
    }

    newPattern.attackPattern = attackMask;
    newPattern.blockerPattern = blockers;
    attackPatterns[rookSqInd][attackPatternCounter] = newPattern;
    attackPatternCounter++;
}

void generateDownRookBlockers(uint64_t blockers, int sqInd, int blockerInd, int down)
{
    if (down <= 0)
    {
        generateRookAttack(blockers, sqInd);
        return;
    }
    
    int nextBlockerInd = blockerInd - 8;
    generateDownRookBlockers(blockers, sqInd, nextBlockerInd, down - 1);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateDownRookBlockers(newBlocker, sqInd, nextBlockerInd, down - 1);      

}

void generateUpRookBlockers(uint64_t blockers, int sqInd, int blockerInd, int up, int down)
{
    if (up <= 0)
    {
        generateDownRookBlockers(blockers, sqInd, sqInd, down);
        return;
    }
    
    int nextBlockerInd = blockerInd + 8;
    generateUpRookBlockers(blockers, sqInd, nextBlockerInd, up - 1, down);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateUpRookBlockers(newBlocker, sqInd, nextBlockerInd, up - 1, down);      

}

void generateRightRookBlockers(uint64_t blockers, int sqInd, int blockerInd, int right, int up, int down)
{
    if (right <= 0)
    {
        generateUpRookBlockers(blockers, sqInd, sqInd, up, down);
        return;
    }
    
    int nextBlockerInd = blockerInd + 1;
    generateRightRookBlockers(blockers, sqInd, nextBlockerInd, right - 1, up, down);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateRightRookBlockers(newBlocker, sqInd, nextBlockerInd, right - 1, up, down);      

}

void generateLeftRookBlockers(uint64_t blockers, int sqInd, int blockerInd, int left, int right, int up, int down)
{
    if (left <= 0)
    {
        generateRightRookBlockers(blockers, sqInd, sqInd, right, up, down);
        return;
    }
    
    int nextBlockerInd = blockerInd - 1;
    generateLeftRookBlockers(blockers, sqInd, nextBlockerInd, left - 1, right, up, down);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateLeftRookBlockers(newBlocker, sqInd, nextBlockerInd, left - 1, right, up, down);      

}

void findAndSaveRookMagics()
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {

    }
}

void generateRookAttackPatterns()
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        int column = sqInd % 8;
        int row = sqInd / 8;

        int left = column - 1;
        int right = 6 - column;
        int up = 6 - row;
        int down = row - 1;

        attackPatternCounter = 0;

        generateLeftRookBlockers(0, sqInd, sqInd, left, right, up, down);
        
    }
}

void initRookAttacksTable(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        attackTables->rookAttacks[sqInd] = malloc(sizeof(uint64_t) * 4096);
    }
   
}

void initRookAttacks(AttackTables* attackTables)
{
    //initRookAttacksTable(attackTables);
    generateRookAttackMasks(attackTables);
    generateRookAttackPatterns();
    findAndSaveRookMagics();
}

AttackTables* initAttackTables()
{
    AttackTables* attackTables = malloc(sizeof(AttackTables));

    initBlackPawnAttacks(attackTables);
    initWhitePawnAttacks(attackTables);
    initKnightAttacks(attackTables);
    initKingAttacks(attackTables);
    initRookAttacks(attackTables);
    
    return attackTables;
}