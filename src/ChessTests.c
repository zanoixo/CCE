#include "stdio.h"
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"

void ASSERT_BIT_TABLE(uint64_t acctual, uint64_t expected)
{
    if (acctual != expected)
    {
        printf("ASSERT FAILED acctual: %llu == %llu :expected\n", (unsigned long long)acctual, (unsigned long long)expected);
        printf("GOT: \n");
        showBitBoard(acctual);
        printf("EXPECTED: \n");
        showBitBoard(expected);
        exit(1);
    }
    
}

void runAttackTablesTests()
{
    AttackTables* attackTables = initAttackTables();

    ASSERT_BIT_TABLE(attackTables->kingAttacks[0],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000011ULL << 8  |
    0b00000010ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[7],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b11000000ULL << 8  |
    0b01000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[56],
    0b00000010ULL << 56 |
    0b00000011ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[63],
    0b01000000ULL << 56 |
    0b11000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[24],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000011ULL << 32 |
    0b00000010ULL << 24 |
    0b00000011ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[31],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b11000000ULL << 32 |
    0b01000000ULL << 24 |
    0b11000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[3],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00011100ULL << 8  |
    0b00010100ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[59],
    0b00010100ULL << 56 |
    0b00011100ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[27],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00011100ULL << 32 |
    0b00010100ULL << 24 |
    0b00011100ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL KING ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[8],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000010ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[15],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b01000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[9],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000101ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[56],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[63],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[57],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL WHITE PAWN ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[48],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000010ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[55],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b01000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[49],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000101ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[0],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[7],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[1],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL BLACK PAWN ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->knightAttacks[27],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00010100ULL << 40 |
    0b00100010ULL << 32 |
    0b00000000ULL << 24 |
    0b00100010ULL << 16 |
    0b00010100ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[0],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000010ULL << 16 |
    0b00000100ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[7],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b01000000ULL << 16 |
    0b00100000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[56],
    0b00000000ULL << 56 |
    0b00000100ULL << 48 |
    0b00000010ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[63],
    0b00000000ULL << 56 |
    0b00100000ULL << 48 |
    0b01000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[46],
    0b10100000ULL << 56 |
    0b00010000ULL << 48 |
    0b00000000ULL << 40 |
    0b00010000ULL << 32 |
    0b10100000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[48],
    0b00000100ULL << 56 |
    0b00000000ULL << 48 |
    0b00000100ULL << 40 |
    0b00000010ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[8],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000010ULL << 24 |
    0b00000100ULL << 16 |
    0b00000000ULL << 8  |
    0b00000100ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[14],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b10100000ULL << 24 |
    0b00010000ULL << 16 |
    0b00000000ULL << 8  |
    0b00010000ULL);

    printf("[PASS] ALL KNIGHT ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->rookMagicHashTable[0].mask,
    0b00000000ULL << 56 |
    0b00000001ULL << 48 |
    0b00000001ULL << 40 |
    0b00000001ULL << 32 |
    0b00000001ULL << 24 |
    0b00000001ULL << 16 |
    0b00000001ULL << 8  |
    0b01111110ULL);

    ASSERT_BIT_TABLE(attackTables->rookMagicHashTable[7].mask,
    0b00000000ULL << 56 |
    0b10000000ULL << 48 |
    0b10000000ULL << 40 |
    0b10000000ULL << 32 |
    0b10000000ULL << 24 |
    0b10000000ULL << 16 |
    0b10000000ULL << 8  |
    0b01111110ULL);

    ASSERT_BIT_TABLE(attackTables->rookMagicHashTable[27].mask,
    0b00000000ULL << 56 |
    0b00001000ULL << 48 |
    0b00001000ULL << 40 |
    0b00001000ULL << 32 |
    0b01110110ULL << 24 |
    0b00001000ULL << 16 |
    0b00001000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->rookMagicHashTable[24].mask,
    0b00000000ULL << 56 |
    0b00000001ULL << 48 |
    0b00000001ULL << 40 |
    0b00000001ULL << 32 |
    0b01111110ULL << 24 |
    0b00000001ULL << 16 |
    0b00000001ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL ROOK MASK TESTS PASSED\n");

    free(attackTables);

}

void runAllTests()
{
    printf("Stating testing:\n");
    printf("Running attack table tests testing:\n");

    runAttackTablesTests();
}