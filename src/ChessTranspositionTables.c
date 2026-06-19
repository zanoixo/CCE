#include "ChessTranspositionTables.h"
#include <stdint.h>

uint64_t randomHash = 12121212121212121212ULL;

uint64_t getRandomHash()
{
    randomHash ^= randomHash << 13;
    randomHash ^= randomHash >> 7;
    randomHash ^= randomHash << 17;
    return randomHash;
}

TranspositionTableHashes* initTranpositionTableHashes()
{
    TranspositionTableHashes* hashes = malloc(sizeof(TranspositionTableHashes));
    hashes->colorHash = getRandomHash();

    for (int piece = 0; piece < PIECE_COUNT; piece++)
    {
        for (int sq = 0; sq < BOARD_SIZE; sq++)
        {
            hashes->pieceHashes[piece][sq] = getRandomHash();
        }
        
    }

    for (int right = 0; right < CASTLE_RIGHT_COUNT; right++)
    {
        hashes->castellingHashes[right] = getRandomHash();
    }

    for (int file = 0; file < ENPASSANT_FILES_COUNT; file++)
    {
        hashes->enPassantHashes[file] = getRandomHash();
    }
    
    return hashes;
}