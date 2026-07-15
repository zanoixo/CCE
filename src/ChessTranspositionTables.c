#include <stdint.h>

#include "ChessTranspositionTables.h"
#include "ChessBoard.h"

uint64_t randomHash = 12121212121212121212ULL;
uint64_t transpositionTableSize = 1 << TRANSPOSITION_TABLE_NUM_OF_BITS;
uint64_t transpositionTableMask = (1 << TRANSPOSITION_TABLE_NUM_OF_BITS) - 1;
uint64_t TTMoveFound = 0;
uint64_t TTMoveSearched = 0;
uint16_t currentAge = 0;

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

    for (int piece = 0; piece < DIFFERENT_PIECE_COUNT; piece++)
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

TranspositionTable* initTranpositionTable()
{
    TranspositionTable* transpositionTable = malloc(sizeof(TranspositionTable));

    clearTranspositionTable(transpositionTable);
    
    return transpositionTable;
}

void clearTranspositionTable(TranspositionTable* transpositionTable)
{
    for (uint64_t i = 0; i < transpositionTableSize; i++)
    {
        transpositionTable->transpositions[i].depth = UNINITIALIZED;
        transpositionTable->transpositions[i].hash = 0;
    }   
}

TranspositionTableEntry* getTransposition(ChessBoard* chessBoard, TranspositionTable* transpositionTable, int remainingDepth, int isEvalOnly)
{
    uint64_t index = chessBoard->positionHash & transpositionTableMask;

    if (isEvalOnly && transpositionTable->transpositions[index].hash != chessBoard->positionHash)
    {
        return NULL;
    }
    

    if (!isEvalOnly && (transpositionTable->transpositions[index].depth < remainingDepth || transpositionTable->transpositions[index].hash != chessBoard->positionHash))
    {
        return NULL;
    }
        
    return &transpositionTable->transpositions[index];
}

TranspositionTableEntry* checkTranspositionHit(ChessBoard* chessBoard, TranspositionTable* transpositionTable, int remeiningDepth, int alpha, int beta)
{
    TranspositionTableEntry* transposition = getTransposition(chessBoard, transpositionTable, remeiningDepth, 0);

    if (transposition != NULL)
    {
        //transpositionHits++;
        if (transposition->flag == alphaCutoff && transposition->moveScore.eval <= alpha)
        {
            //transpositionCutoffs++;
            return transposition;
        }
        else if (transposition->flag == betaCutoff && transposition->moveScore.eval >= beta)
        {
            //transpositionCutoffs++;
            return transposition;
        }
        else if (transposition->flag == exactCutoff)
        {
            //transpositionCutoffs++;
            return transposition;
        }
        else
        {
            return NULL;
        } 
    }

    return NULL;
}



void setTransposition(ChessBoard* chessBoard, TranspositionTable* transpositionTable, int remainingDepth, MoveScore* moveScore, int alpha, int beta)
{
    if (moveScore->move.from == 0 || moveScore->move.to == 0)
    {
        return;
    }

    uint8_t transpositionFlag;

    if (moveScore->eval >= beta)
    {
        transpositionFlag = betaCutoff;
    }
    else if (moveScore->eval <= alpha)
    {
        transpositionFlag = alphaCutoff;
    }
    else
    {
        transpositionFlag = exactCutoff;
    }

    

    uint64_t index = chessBoard->positionHash & transpositionTableMask;

    if (transpositionTable->transpositions[index].depth <= remainingDepth || transpositionTable->transpositions[index].age < currentAge)
    {
        transpositionTable->transpositions[index].moveScore = *moveScore;
        transpositionTable->transpositions[index].depth = remainingDepth;
        transpositionTable->transpositions[index].hash = chessBoard->positionHash;
        transpositionTable->transpositions[index].flag = transpositionFlag;
        transpositionTable->transpositions[index].age = currentAge;
    }
}

void setScoreToTranspositionMove(ChessBoard* chessBoard, MoveList* moveList, TranspositionTable* transpositionTable)
{

    TTMoveSearched++;
    TranspositionTableEntry* transposition = getTransposition(chessBoard, transpositionTable, 0, 1);

    for (int i = 0; i < moveList->nextIndex; i++)
    {
        if (transposition != NULL && transposition->moveScore.move.from == moveList->moves[i].from && 
            transposition->moveScore.move.to == moveList->moves[i].to)
        {
            moveList->moves[i].score = TRANSPOSITION_SCORE;
            TTMoveFound++;
            break;
        }    
    }
}

uint64_t getTTMovesFound()
{
    return TTMoveFound;
}

uint64_t getTTMovesSearched()
{
    return TTMoveSearched;
}

void initAge()
{
    currentAge = 0;
}

void incrementAge()
{
    currentAge++;
}   

uint16_t getCurrentAge()
{
    return currentAge;
}

int getScoreForTransposition(int eval, int depth)
{
    if (eval > MATED_TRESHOLD)
    {
        return eval + depth;
    }
    
    if (eval < -MATED_TRESHOLD)
    {
        return eval - depth;
    }
    
    return eval;
}

int getScoreFromTransposition(int eval, int depth)
{
    if (eval > MATED_TRESHOLD)
    {
        return eval - depth;
    }
    
    if (eval < -MATED_TRESHOLD)
    {
        return eval + depth;
    }
    
    return eval;
}