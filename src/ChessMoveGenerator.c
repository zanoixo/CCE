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

void initRookAttacks(AttackTables* attackTables)
{
    generateRookAttackMasks(attackTables);
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