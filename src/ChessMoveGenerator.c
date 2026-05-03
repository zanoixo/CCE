#include <stdio.h>
#include <time.h>
#include <string.h>
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

uint64_t MAX_NUMBER_OF_MAGICS = 10000000;

int attackPatternCounter = 0;
BlockerAttackPattern attackPatterns[64][4096];

uint64_t randomState;

int numberOfRookMovementBits(int rookSqInd)
{
    int column = rookSqInd % 8;
    int row = rookSqInd / 8;

    int left  = column - 1;
    int right = 7 - column - 1;
    int up    = 7 - row - 1;
    int down  = row - 1;

    int bits = 0;

    if (left  > 0)
    {
        bits += left;
    } 
    if (right > 0)
    {
        bits += right;
    } 
    if (up    > 0)
    {
        bits += up;
    } 
    if (down  > 0)
    {
        bits += down;
    } 

    return bits;
}

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
        
        for (int l = 1; l < column; l++)
        {
            mask |= rookPosition >> l;
        }

        for (int r = 1; r < 7 - column; r++)
        {
            mask |= rookPosition << r;
        }

        for (int u = 1; u < row; u++)
        {
            mask |= rookPosition >> (u * 8);
        }

        for (int d = 1; d < 7 - row; d++)
        {
            mask |= rookPosition << (d * 8);
        }

        attackTables->rookMagicHashTable[sqInd].mask = mask;
        attackTables->rookMagicHashTable[sqInd].shift = BOARD_SIZE - numberOfRookMovementBits(sqInd);
        
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

uint64_t generateRandomMagic()
{
    randomState ^= randomState << 13;
    randomState ^= randomState >> 7;
    randomState ^= randomState << 17;

    uint64_t firstRandomPart = randomState;

    randomState ^= randomState << 13;
    randomState ^= randomState >> 7;
    randomState ^= randomState << 17;

    uint64_t secondRandomPart = randomState;

    randomState ^= randomState << 13;
    randomState ^= randomState >> 7;
    randomState ^= randomState << 17;

    uint64_t thirdRandomPart = randomState;
 
    return firstRandomPart & secondRandomPart & thirdRandomPart;
}

int isMagicNumberValid(int sqInd, uint64_t magicNumber, int numOfIndexBits)
{
    int numberOfBits = numberOfRookMovementBits(sqInd);
    uint64_t tempHashTable[1 << numOfIndexBits];
    uint64_t usedIndexes[1 << numOfIndexBits];

    memset(tempHashTable, 0, sizeof(tempHashTable));
    memset(usedIndexes, 0, sizeof(usedIndexes));
    

    for (int variation = 0; variation < 1 << numberOfBits; variation++)
    {
        BlockerAttackPattern blockerAttackPattern = attackPatterns[sqInd][variation];
        uint64_t newInd = (blockerAttackPattern.blockerPattern * magicNumber) >> (64 - numOfIndexBits);
        if (usedIndexes[newInd] != 0 && tempHashTable[newInd] != blockerAttackPattern.attackPattern)
        {
            return 0;
        }else
        {
            tempHashTable[newInd] = blockerAttackPattern.attackPattern;
            usedIndexes[newInd] = 1;
        }
    }

    return 1;
}

void saveRookMagics(uint64_t validMagicNumbers[], int numberOfBits[])
{
    FILE* file = fopen("magics/rookMagics.csv", "w");
    if (!file)
    {
        printf("Failed to open file\n");
        return;
    }

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        fprintf(file, "%d,%d,%llu\n", sqInd, numberOfBits[sqInd],(unsigned long long)validMagicNumbers[sqInd]);
    }

    fclose(file);
}

void loadRookAttacks(AttackTables* attackTables)
{
    uint64_t magicNumbers[64];
    int numOfBits[64];
    unsigned long long magicNumber;
    int nBits;
    int sq;

    FILE* file = fopen("magics/rookMagics.csv", "r");
    if (!file)
    {
        printf("Failed to open file\n");
        return;
    }

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        fscanf(file, "%d,%d,%llu\n", &sq, &nBits, &magicNumber);
        magicNumbers[sq] = (uint64_t)magicNumber;
        numOfBits[sq] = nBits;
    }

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        int shift = 64 - numOfBits[sqInd];
        magicNumber = magicNumbers[sqInd];
        attackTables->rookAttacks[sqInd] = malloc(sizeof(uint64_t) * (1 << numOfBits[sqInd]));
        attackTables->rookMagicHashTable[sqInd].magicNumber = magicNumber;
        attackTables->rookMagicHashTable[sqInd].shift = shift;

        for (int variation = 0; variation < 1 << numOfBits[sqInd]; variation++)
        {
            BlockerAttackPattern pattern = attackPatterns[sqInd][variation];
            uint64_t attackPattern = pattern.attackPattern;
            uint64_t newIndex = (pattern.blockerPattern * magicNumber) >> shift;

            attackTables->rookAttacks[sqInd][newIndex] = attackPattern;
        }
        
    }
    
    fclose(file);
}

void findAndSaveRookMagics()
{
    uint64_t validMagicNumbers[64] = {0};
    int numberOfBits[64] = {0};
    uint64_t magicNumber;
    randomState = time(NULL);
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        for (int nBits = 12; nBits > 0; nBits--)
        {
            int wasMagicFound = 0;
            for (uint64_t magicAttempt = 0; magicAttempt < MAX_NUMBER_OF_MAGICS; magicAttempt++)
            {
                magicNumber = generateRandomMagic();
                if (isMagicNumberValid(sqInd, magicNumber, nBits))
                {
                    validMagicNumbers[sqInd] = magicNumber;
                    numberOfBits[sqInd] = nBits;
                    wasMagicFound = 1;
                    break;
                }
            }
            if (!wasMagicFound)
            {
                printf("%d magic not found\n", nBits);
                break;
            }
             
        }
       
    }

    saveRookMagics(validMagicNumbers, numberOfBits);
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

void initRookAttacks(AttackTables* attackTables)
{
    generateRookAttackMasks(attackTables);
    generateRookAttackPatterns();
    //findAndSaveRookMagics();
    loadRookAttacks(attackTables);
}

uint64_t getRookAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables)
{
    MagicTableHash magicTableHash = attackTables->rookMagicHashTable[sqInd];
    uint64_t index = (position & magicTableHash.mask) * magicTableHash.magicNumber;                 
    index = index >> magicTableHash.shift;

    return attackTables->rookAttacks[sqInd][index];
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