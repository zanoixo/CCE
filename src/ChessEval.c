#include <string.h>
#include <math.h>

#include "ChessBoard.h"
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"
#include "ChessEval.h"
#include "ChessTests.h"
#include "ChessTranspositionTables.h"


uint64_t innerCenterEval = 0b00000000ULL << 56 |
                           0b00000000ULL << 48 |
                           0b00000000ULL << 40 |
                           0b00011000ULL << 32 |
                           0b00011000ULL << 24 |
                           0b00000000ULL << 16 |
                           0b00000000ULL << 8  |
                           0b00000000ULL;

uint64_t outerCenterEval = 0b00000000ULL << 56 |
                           0b00000000ULL << 48 |
                           0b00111100ULL << 40 |
                           0b00100100ULL << 32 |
                           0b00100100ULL << 24 |
                           0b00111100ULL << 16 |
                           0b00000000ULL << 8  |
                           0b00000000ULL;

int knightPosTable[64] =
{
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};

int bishopPosTable[64] =
{
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};

int rookPosTable[64] =
{
     0,  0,  5, 10, 10,  5,  0,  0,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     5, 10, 10, 10, 10, 10, 10,  5,
     0,  0,  5, 10, 10,  5,  0,  0
};

int queenPosTable[64] =
{
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
     -5,  0,  5,  5,  5,  5,  0, -5,
      0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

int whitePawnPosTable[64] =
{
      0,  0,  0,  0,  0,  0,  0,  0,
      5, 10, 10,-20,-20, 10, 10,  5,
      5, -5,-10,  0,  0,-10, -5,  5,
      0,  0,  0, 20, 20,  0,  0,  0,
      5,  5, 10, 25, 25, 10,  5,  5,
     10, 10, 20, 30, 30, 20, 10, 10,
     50, 50, 50, 50, 50, 50, 50, 50,
      0,  0,  0,  0,  0,  0,  0,  0
};

int blackPawnPosTable[64] =
{
     0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 25, 25, 10,  5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-20,-20, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

Move killerMoves[KILLER_MOVE_DEPTH][2];
int historyHeuristic[BOARD_SIZE][BOARD_SIZE][DIFFERENT_PIECE_COUNT / 2];
uint64_t passedPawnMasks[64];
uint64_t isolatedPawnMasks[64];
uint64_t stopTime = 0;
int currentDepth;
int qSearchDepthReached;
int nodesSearched;
int transpositionSearches;
int transpositionHits;
int transpositionCutoffs;
int timeCheckCounter = 1;
int timeLimitReached = 0;
int isNullMove = 0;
uint64_t pvsChecks = 0;
uint64_t pvsResearches = 0;

void updateTime()
{
    timeCheckCounter++;
        
    if ((timeCheckCounter & TIME_CHECK) == 0)
    {
        timeCheckCounter = 1;
        
        if (stopTime < getTimeMs())
        {
            timeLimitReached = 1;
        }
        
    }
}

void initPassedPawnMasks()
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t mask = 0;
        int file = sqInd % 8;

        for (int i = 0; i < 8; i++)
        {
            uint64_t nextSq = 1ULL << ((i * 8) + file);
            mask |= nextSq;
        }

        
        if (file + 1 < 8)
        {
            for (int i = 0; i < 8; i++)
            {
                uint64_t nextSq = (1ULL << (i * 8 + file + 1));
                mask |= nextSq;
            }
        }
        
        if (file - 1 > -1)
        {
            for (int i = 0; i < 8; i++)
            {
                uint64_t nextSq = (1ULL << (i * 8  + file - 1));
                mask |= nextSq;
            }
        }
        
        passedPawnMasks[sqInd] = mask;
    }
    
}

void initIsolatedPawnMasks()
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t mask = 0;
        int file = sqInd % 8;
        
        if (file + 1 < 8)
        {
            for (int i = 0; i < 8; i++)
            {
                uint64_t nextSq = (1ULL << (i * 8 + file + 1));
                mask |= nextSq;
            }
        }
        
        if (file - 1 > -1)
        {
            for (int i = 0; i < 8; i++)
            {
                uint64_t nextSq = (1ULL << (i * 8  + file - 1));
                mask |= nextSq;
            }
        }
        
        isolatedPawnMasks[sqInd] = mask;
    }
    
}

void penalizeHistoryHeuristic(Move move, int remeniningDepth)
{
    historyHeuristic[getSqInd(move.from)][getSqInd(move.to)][getPiece(move.flags) - 1] -= remeniningDepth;     
}

void updateHistoryHeuristic(Move move, int remeniningDepth)
{
    historyHeuristic[getSqInd(move.from)][getSqInd(move.to)][getPiece(move.flags) - 1] += remeniningDepth * remeniningDepth; 
}

int getHistoryHeuristic(Move move)
{
    return historyHeuristic[getSqInd(move.from)][getSqInd(move.to)][getPiece(move.flags) - 1];
}

void clearHistoryHeuristic()
{
    memset(historyHeuristic, 0, sizeof(historyHeuristic));
}

void initKillerMoves()
{
    for (int i = 0; i < currentDepth; i++)
    {
        killerMoves[i][0] = (Move){0, 0, 0, 0, 0};
        killerMoves[i][1] = (Move){0, 0, 0, 0, 0};
    }
}

void findKillerMoves(MoveList *moveList, int depth)
{
    for (int i = 0; i < moveList->nextIndex; i++)
    {
        if (moveList->moves[i].from == killerMoves[depth][0].from &&
             moveList->moves[i].to == killerMoves[depth][0].to)
        {
            moveList->moves[i].score = 200;
        }

        if (moveList->moves[i].from == killerMoves[depth][1].from &&
             moveList->moves[i].to == killerMoves[depth][1].to)
        {
            moveList->moves[i].score = 100;
        }
        
    }
    
}

void setKillerMove(Move killerMove, int depth)
{
    if (!(killerMoves[depth][0].from == killerMove.from && killerMoves[depth][0].to == killerMove.to) &&
        !(killerMoves[depth][1].from == killerMove.from && killerMoves[depth][1].to == killerMove.to))
    {
        killerMoves[depth][1] = killerMoves[depth][0];
        killerMoves[depth][0] = killerMove;
    } 
}

int countPieces(uint64_t bitboard)
{
    int count = 0;

    while (bitboard)
    {
        count++;
        bitboard &= bitboard - 1;
    }

    return count;
}

int evaluateMobility(ChessBoard* chessBoard, AttackTables* attackTables, int isBlack)
{
    int mobility = 0;
    int piecePositioning = 0;

    uint64_t knights = chessBoard->whiteKnights;
    uint64_t bishops = chessBoard->whiteBishops;
    uint64_t rooks = chessBoard->whiteRooks;
    uint64_t queens = chessBoard->whiteQueens;
    uint64_t friendlyPieces = chessBoard->whitePieces;

    if (isBlack)
    {
        knights = chessBoard->blackKnights;
        bishops = chessBoard->blackBishops;
        rooks = chessBoard->blackRooks;
        queens = chessBoard->blackQueens;
        friendlyPieces = chessBoard->blackPieces;
    }
    
    while (knights)
    {
        int sq = getSqInd(knights);
        uint64_t attacks = attackTables->knightAttacks[sq] & ~friendlyPieces;
        mobility += countPieces(attacks) * KNIGHT_MOBILITY_VALUE;
        piecePositioning += knightPosTable[sq];
        knights &= knights - 1;
    }

    while (bishops)
    {
        int sq = getSqInd(bishops);
        uint64_t attacks = getBishopAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += countPieces(attacks) * BISHOP_MOBILITY_VALUE;
        piecePositioning += bishopPosTable[sq];
        bishops &= bishops - 1;
    }

    while (rooks)
    {
        int sq = getSqInd(rooks);
        uint64_t attacks = getRookAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += countPieces(attacks) * ROOK_MOBILITY_VALUE;
        piecePositioning += rookPosTable[sq];
        rooks &= rooks - 1;
    }

    while (queens)
    {
        int sq = getSqInd(queens);
        uint64_t attacks = getQueenAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += (countPieces(attacks) * QUEEN_MOBILITY_VALUE) / 2;
        piecePositioning += queenPosTable[sq];
        queens &= queens - 1;
    }

    return mobility + piecePositioning;
}

int evaluateKingSafety(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;

    if (hasCastled(chessBoard, isBlack))
    {
        score += KING_CASTLED_VALUE;
    }
    
    return score;
}

int evaluatePawnPositioning(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;
    int fileCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    if (isBlack)
    {
        uint64_t pawns = chessBoard->blackPawns;

        while (pawns)
        {
            int sq = getSqInd(pawns);
            score += blackPawnPosTable[sq];
            if (!(chessBoard->whitePawns & passedPawnMasks[sq]))
            {
                score += PASSED_PAWN_SCORE;
            }  
            if (!(chessBoard->blackPawns & isolatedPawnMasks[sq]))
            {
                score -= ISOLATED_PAWN_PENALTY;
            }
            
            fileCount[sq % 8]++;
            pawns &= pawns - 1;
        }   
    }
    else
    {
        uint64_t pawns = chessBoard->whitePawns;

        while (pawns)
        {
            int sq = getSqInd(pawns);
            score += whitePawnPosTable[sq];
            if (!(chessBoard->blackPawns & passedPawnMasks[sq]))
            {
                score += PASSED_PAWN_SCORE;
            }
            if (!(chessBoard->whitePawns & isolatedPawnMasks[sq]))
            {
                score -= ISOLATED_PAWN_PENALTY;
            }
            fileCount[sq % 8]++;
            pawns &= pawns - 1;
        }     
    }   

    for (int i = 0; i < 8; i++)
    {
        if (fileCount[i] > 1)
        {
            score -= (fileCount[i] - 1) * DOUBLED_PAWN_PENALTY;
        }  
    }
    
    return score; 
}

int evaluateMaterial(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;

    if (isBlack)
    {
        score += countPieces(chessBoard->blackPawns)   * PAWN_VALUE;
        score += countPieces(chessBoard->blackKnights) * KNIGHT_VALUE;
        score += countPieces(chessBoard->blackBishops) * BISHOP_VALUE;
        score += countPieces(chessBoard->blackRooks)   * ROOK_VALUE;
        score += countPieces(chessBoard->blackQueens)  * QUEEN_VALUE;
    }
    else
    {
        score += countPieces(chessBoard->whitePawns)   * PAWN_VALUE;
        score += countPieces(chessBoard->whiteKnights) * KNIGHT_VALUE;
        score += countPieces(chessBoard->whiteBishops) * BISHOP_VALUE;
        score += countPieces(chessBoard->whiteRooks)   * ROOK_VALUE;
        score += countPieces(chessBoard->whiteQueens)  * QUEEN_VALUE;    
    }
    return score;
}

int evaluateCenter(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;

    if (isBlack)
    {
        score += countPieces(chessBoard->blackPieces & innerCenterEval) * INNER_CENTER_VALUE;
        score += countPieces(chessBoard->blackPieces & outerCenterEval) * OUTER_CENTER_VALUE;
    }
    else
    {
        score += countPieces(chessBoard->whitePieces & innerCenterEval) * INNER_CENTER_VALUE;
        score += countPieces(chessBoard->whitePieces & outerCenterEval) * OUTER_CENTER_VALUE;    
    }
    return score;
}

int evaluateBishopPair(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;

    if (isBlack)
    {
       int numberOfBishops = countPieces(chessBoard->blackBishops);

       if (numberOfBishops == 2)
       {
            score = BISHOP_PAIR_VALUE;
       }
       
    }
    else
    {
        int numberOfBishops = countPieces(chessBoard->whiteBishops);

       if (numberOfBishops == 2)
       {
            score = BISHOP_PAIR_VALUE;
       }    
    }
    return score;
}

int evaluatePosition(ChessBoard* chessBoard, AttackTables* attackTables)
{
    int score = 0;

    score += evaluateMaterial(chessBoard, white);
    score += evaluateCenter(chessBoard, white);
    score += evaluateMobility(chessBoard, attackTables, white);
    score += evaluatePawnPositioning(chessBoard, white);
    score += evaluateBishopPair(chessBoard, white);
    score += evaluateKingSafety(chessBoard, white);

    score -= evaluateMaterial(chessBoard, black);
    score -= evaluateCenter(chessBoard, black);
    score -= evaluateMobility(chessBoard, attackTables, black);
    score -= evaluatePawnPositioning(chessBoard, black);
    score -= evaluateBishopPair(chessBoard, black);
    score -= evaluateKingSafety(chessBoard, black);

    return score;
}

void setBestMoveFirst(MoveList* moveList, int moveCount)
{
    int moveInd = moveCount;

    for (int i = moveCount + 1; i < moveList->nextIndex; i++)
    {   
        if (moveList->moves[i].score > moveList->moves[moveInd].score)
        {
            moveInd = i;
            continue;
        }
        
        if (moveList->moves[moveInd].score == 0 && getHistoryHeuristic(moveList->moves[i]) > getHistoryHeuristic(moveList->moves[moveInd]))
        {
            moveInd = i;
        }
        
    }
    Move tmp = moveList->moves[moveCount];
    moveList->moves[moveCount] = moveList->moves[moveInd];
    moveList->moves[moveInd] = tmp;
}

int isValidQSearchMove(uint16_t moveFlags)
{    
    return getCapturedPiece(moveFlags)  || getPromotionPiece(moveFlags);
}

int hasNonPawnPieces(ChessBoard* chessBoard, int side)
{
    if (side == black)
    {
        if (chessBoard->blackBishops > 0)
        {
            return 1;
        }
        
        if (chessBoard->blackKnights > 0)
        {
            return 1;
        }
        
        if (chessBoard->blackQueens > 0)
        {
            return 1;
        }
        
        if (chessBoard->blackRooks > 0)
        {
            return 1;
        }
        
    }
    else
    {
        if (chessBoard->whiteBishops > 0)
        {
            return 1;
        }
        
        if (chessBoard->whiteKnights > 0)
        {
            return 1;
        }
        
        if (chessBoard->whiteQueens > 0)
        {
            return 1;
        }
        
        if (chessBoard->whiteRooks > 0)
        {
            return 1;
        }       
    }

    return 0;
    
}

int isBetaValid(int beta)
{
    if (beta < 0)
    {
        return !(-MATED_TRESHOLD > beta); 
    }
    else
    {
        return !(MATED_TRESHOLD < beta);
    }
}

MoveScore qsearch(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, int depthSearched, int mateDistance, int alpha, int beta, int side)
{
    //nodesSearched++;

    MoveScore bestMove;
    bestMove.eval = MIN_INT;
    bestMove.move = (Move){0, 0, 0, 0, 0};

    int originalBeta = beta;
    int originalAlpha = alpha;

    //ChessBoard* original = malloc(sizeof(ChessBoard));
    //memcpy(original, chessBoard, sizeof(ChessBoard));

    TranspositionTableEntry* transpositionScore = checkTranspositionHit(chessBoard, transpositionTable, QSEARCH, originalAlpha, originalBeta);
    //transpositionSearches++;

    if (transpositionScore != NULL)
    {
        makeMove(chessBoard, &transpositionScore->moveScore.move, hashes);

        if (isThreeFoldRepetition(chessBoard))
        {
            unMakeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            //ASSERT_CHESS_BOARD(original, chessBoard);
        }
        else
        {
            unMakeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            //ASSERT_CHESS_BOARD(original, chessBoard);
            //free(original);
            MoveScore transpositionMove = transpositionScore->moveScore;
            transpositionMove.eval = getScoreFromTransposition(transpositionMove.eval, mateDistance);
            return transpositionMove;
        }
    }
    
    int ownKingSq = getSqInd(side ? chessBoard->blackKing : chessBoard->whiteKing);
    int gotChecked = isSquareAttacked(ownKingSq, chessBoard, attackTables, side);

    if (!gotChecked)
    {
        int standPat = evaluatePosition(chessBoard, attackTables);
        bestMove.eval = side ? -standPat : standPat;

        if (bestMove.eval >= beta && isBetaValid(beta))
        {
            bestMove.eval = beta;

            //free(original);
            return bestMove;
        }

        if (bestMove.eval > alpha)
        {
            alpha = bestMove.eval;
        }
    }

    if (depthSearched > qSearchDepthReached)
    {
        qSearchDepthReached = depthSearched;
        printf("selective search max depth reached: %d\n", qSearchDepthReached);
    }

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    int legalMoves = 0;

    MoveScore moveScore;

    generateMoves(chessBoard, attackTables, &moveList);

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        updateTime();

        if (timeLimitReached && currentDepth != 1)
        {
            //free(original);
            return bestMove;
        }

        setBestMoveFirst(&moveList, i);

        if (!gotChecked && !isValidQSearchMove(moveList.moves[i].flags))
        {
            continue;
        }

        makeMove(chessBoard, &moveList.moves[i], hashes);

        ownKingSq = getSqInd(side ? chessBoard->blackKing : chessBoard->whiteKing);
        int isNotLegalMove = isSquareAttacked(ownKingSq, chessBoard, attackTables, side);

        if (!isNotLegalMove)
        {
            legalMoves++;

            if (isThreeFoldRepetition(chessBoard))
            {
                moveScore.eval = DRAW;
                moveScore.move = moveList.moves[i];
            }
            else
            {
                moveScore = qsearch(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1, mateDistance + 1, -beta, -alpha, !side);
                moveScore.eval = -moveScore.eval;
            }

            if (moveScore.eval > bestMove.eval || legalMoves == 1)
            {
                bestMove.eval = moveScore.eval;
                bestMove.move = moveList.moves[i];
            }

            if (moveScore.eval > alpha)
            {
                alpha = moveScore.eval;
            }

            if (alpha >= beta)
            {
                unMakeMove(chessBoard, &moveList.moves[i], hashes);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i], hashes);
        //ASSERT_CHESS_BOARD(original, chessBoard);
    }

    //free(original);

    if (gotChecked && legalMoves == 0)
    {
        bestMove.eval = MATED + mateDistance;
    }

    MoveScore transpositionMove = bestMove;
    transpositionMove.eval = getScoreForTransposition(transpositionMove.eval, mateDistance);

    if (!timeLimitReached)
    {
        setTransposition(chessBoard, transpositionTable, QSEARCH, &transpositionMove, originalAlpha, originalBeta);
    }
    
    return bestMove;
}

MoveScore negamax(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, int depthSearched, int mateDistance, int alpha, int beta, int side)
{
    MoveScore bestMove;
    bestMove.eval = MIN_INT;
    bestMove.move = (Move){0, 0, 0, 0, 0};

    if (depthSearched > currentDepth)
    {
        bestMove = qsearch(chessBoard, attackTables, hashes, transpositionTable, depthSearched, mateDistance, alpha, beta, side);
        return bestMove;
    }

    //ChessBoard* original = malloc(sizeof(ChessBoard));
    //memcpy(original, chessBoard, sizeof(ChessBoard));

    int originalAlpha = alpha;
    int originalBeta = beta;

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    MoveScore moveScore;

    TranspositionTableEntry* transpositionScore = checkTranspositionHit(chessBoard, transpositionTable, currentDepth - depthSearched, originalAlpha, originalBeta);
    int legalMoves = 0;


    if (transpositionScore != NULL)
    {
        makeMove(chessBoard, &transpositionScore->moveScore.move, hashes);

        if (isThreeFoldRepetition(chessBoard))
        {
            unMakeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            //ASSERT_CHESS_BOARD(original, chessBoard);
        }
        else
        {
            unMakeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            //ASSERT_CHESS_BOARD(original, chessBoard);
            //free(original);
            MoveScore transpositionMove = transpositionScore->moveScore;
            transpositionMove.eval = getScoreFromTransposition(transpositionMove.eval, mateDistance);
            
            return transpositionMove;
        }
    }

    int ownKingSq = getSqInd(side ? chessBoard->blackKing : chessBoard->whiteKing);
    int amChecked = isSquareAttacked(ownKingSq, chessBoard, attackTables, side);

    if (!isNullMove && currentDepth - depthSearched >= 3 && !amChecked && depthSearched != 0 && hasNonPawnPieces(chessBoard, side) && isBetaValid(beta))
    {
        Move nullMove = (Move){0, 0, 0, 0, 0};

        MoveScore nullMoveScore;
        nullMoveScore.move = nullMove;

        isNullMove = 1;

        makeNullMove(chessBoard, &nullMove, hashes);

        nullMoveScore = negamax(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1 + NULL_MOVE_SKIP, mateDistance + 1, -beta, -beta + 1, !side);
        nullMoveScore.eval = -nullMoveScore.eval;

        unMakeNullMove(chessBoard, &nullMove, hashes);

        isNullMove = 0;

        if (nullMoveScore.eval >= beta)
        {
            bestMove.eval = beta;
            
            //free(original);
            return bestMove;
        }
    }

    generateMoves(chessBoard, attackTables, &moveList);

    setScoreToTranspositionMove(chessBoard, &moveList, transpositionTable);
    findKillerMoves(&moveList, depthSearched);

    int isFirstMove = 1;

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        updateTime();

        if (timeLimitReached && currentDepth != 1)
        {
            //free(original);
            return bestMove;
        }

        setBestMoveFirst(&moveList, i);

        makeMove(chessBoard, &moveList.moves[i], hashes);

        ownKingSq = getSqInd(side ? chessBoard->blackKing : chessBoard->whiteKing);

        int isChecked = isSquareAttacked(ownKingSq, chessBoard, attackTables, side);

        if (!isChecked)
        {
            legalMoves++;

            int enemyKingSq = getSqInd(side ? chessBoard->whiteKing : chessBoard->blackKing);
            int isEnemyChecked = isSquareAttacked(enemyKingSq, chessBoard, attackTables, !side);
            int moveReduction = 0;

            if (i > 3 && !isEnemyChecked && !amChecked && currentDepth - depthSearched >= 3 && !getCapturedPiece(moveList.moves[i].flags) && !getPromotionPiece(moveList.moves[i].flags))
            {
                moveReduction = (int)(0.75 * log(currentDepth - depthSearched) * log(i) / 2.25);
            }

            if (isThreeFoldRepetition(chessBoard))
            {
                moveScore.move = moveList.moves[i];
                moveScore.eval = DRAW;
            }
            else
            {   
                if (isFirstMove)
                {
                    moveScore = negamax(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1, mateDistance + 1, -beta, -alpha, !side);
                    moveScore.eval = -moveScore.eval;
                }
                else
                {
                    moveScore = negamax(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1 + moveReduction, mateDistance + 1, -alpha - 1, -alpha, !side);
                    moveScore.eval = -moveScore.eval;
                    pvsChecks++;  

                    if (moveScore.eval > alpha)
                    {
                        pvsResearches++;
                        moveScore = negamax(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1, mateDistance + 1, -beta, -alpha, !side);
                        moveScore.eval = -moveScore.eval;
                    }
                }
                    
            }

            if (moveScore.eval > bestMove.eval || isFirstMove)
            {
                bestMove.eval = moveScore.eval;
                bestMove.move = moveList.moves[i];
            }

            isFirstMove = 0;

            if (moveScore.eval > alpha)
            {
                alpha = moveScore.eval;
            }

            if (alpha >= beta)
            {
                if (!getPromotionPiece(moveList.moves[i].flags) && !getCapturedPiece(moveList.moves[i].flags))
                {
                    setKillerMove(moveList.moves[i], depthSearched);
                    updateHistoryHeuristic(moveList.moves[i], currentDepth - depthSearched);

                    for (int moveInd = i - 1; moveInd >= 0; moveInd--)
                    {
                        if (moveList.moves[moveInd].score > 0)
                        {
                            break;
                        }

                        penalizeHistoryHeuristic(moveList.moves[moveInd], currentDepth - depthSearched);
                    }
                }

                unMakeMove(chessBoard, &moveList.moves[i], hashes);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i], hashes);
        //ASSERT_CHESS_BOARD(original, chessBoard);
    }

    //free(original);

    if (legalMoves == 0)
    {
        ownKingSq = getSqInd(side ? chessBoard->blackKing : chessBoard->whiteKing);
        if (isSquareAttacked(ownKingSq, chessBoard, attackTables, side))
            bestMove.eval = MATED + mateDistance;
        else
            bestMove.eval = DRAW;
    }

    MoveScore transpositionMove = bestMove;
    transpositionMove.eval = getScoreForTransposition(transpositionMove.eval, mateDistance);
    
    if (!timeLimitReached)
    {
        setTransposition(chessBoard, transpositionTable, currentDepth - depthSearched, &transpositionMove, originalAlpha, originalBeta);
    }
    
    return bestMove;
}

MoveScore iterativeSearch(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTable* transpositionTable, TranspositionTableHashes* hashes)
{
    MoveScore bestMove;
    initKillerMoves();
    bestMove = negamax(chessBoard, attackTables, hashes, transpositionTable, 1, 1, MIN_INT, MAX_INT, isBlack(chessBoard));
    return bestMove;
}

MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, uint64_t timePerMove)
{
    MoveScore currentBestMove;
    MoveScore depthBestMove;
    timeLimitReached = 0;
    timeCheckCounter = 1;
    stopTime = getTimeMs() + timePerMove - 100;

    currentDepth = 1;
    qSearchDepthReached = 1;
    while (!timeLimitReached)
    {
        /*
        nodesSearched = 0;
        transpositionSearches = 0;
        transpositionHits = 0;
        transpositionCutoffs = 0;
        */

        printf("Current search depth: %d\n", currentDepth);
        depthBestMove = iterativeSearch(chessBoard, attackTables, transpositionTable, hashes);
        
        //printf("Nodes: %d, Transposition searches: %d, hits: %d, Cutoffs: %d\n", nodesSearched, transpositionSearches, transpositionHits, transpositionCutoffs);
        if (!timeLimitReached || currentDepth == 1)
        {
            currentBestMove = depthBestMove;
        }
        
        currentDepth++; 
    
        if (currentDepth > 255)
        {
            break;
        }
        
    }

    printf("PVS checks: %llu, PVS reserches: %llu\n", (long long unsigned)pvsChecks, (long long unsigned)pvsResearches);
    printf("TT moves searched: %llu, TT moves found: %llu\n", (long long unsigned)getTTMovesSearched(), (long long unsigned)getTTMovesFound());
    return currentBestMove;
}