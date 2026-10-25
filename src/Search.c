#include <string.h>
#include <math.h>

#include "Search.h"
#include "ChessBoard.h"
#include "MoveGenerator.h"
#include "TacticalMoveGenerator.h"
#include "Utils.h"
#include "Eval.h"
#include "Tests.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"
#include "MakeMove.h"
#include "UnMakeMove.h"
#include "AttackTables.h"
#include "Eval.h"
#include "HistoryHeuristic.h"
#include "KillerHeuristic.h"
#include "MoveGrader.h"

int lateMoveReductionTable[MAX_MOVE_COUNT][MAX_DEPTH];
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

void setBestMoveFirst(GradedMoveList* moveList, int moveCount)
{
    int moveInd = moveCount;

    for (int i = moveCount + 1; i < moveList->nextIndex; i++)
    {   
        if (moveList->gradedMoves[i].grade > moveList->gradedMoves[moveInd].grade)
        {
            moveInd = i;
        }
    }
    GradedMove tmp = moveList->gradedMoves[moveCount];
    moveList->gradedMoves[moveCount] = moveList->gradedMoves[moveInd];
    moveList->gradedMoves[moveInd] = tmp;
}

void initLateMoveReductionTable()
{
    for (int moveInd = 0; moveInd < MAX_MOVE_COUNT; moveInd++)
    {
        for (int depth = 0; depth < MAX_DEPTH; depth++)
        {
            lateMoveReductionTable[moveInd][depth] = (int)(0.75 + log(depth) * log(moveInd) / 2.25);
        }  
    }
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
    nodesSearched++;

    MoveScore bestMove;
    bestMove.eval = MIN_EVAL;
    bestMove.move = 0;

    int mateValue = -MATED - mateDistance;

    if (mateValue < beta)
    {
        beta = mateValue;
        if (alpha >= beta)
        {
            bestMove.eval = mateValue;
            return bestMove;
        }
        
    }

    mateValue = MATED - mateDistance;

    if (mateValue > alpha)
    {
        alpha = mateValue;
        if (beta <= alpha)
        {
            bestMove.eval = mateValue;
            return bestMove;
        }
        
    }

    int originalBeta = beta;
    int originalAlpha = alpha;

    //ChessBoard* original = malloc(sizeof(ChessBoard));
    //memcpy(original, chessBoard, sizeof(ChessBoard));

    TranspositionTableEntry* transpositionScore = checkTranspositionHit(chessBoard, transpositionTable, QSEARCH, originalAlpha, originalBeta);
    //transpositionSearches++;

    if (transpositionScore != NULL)
    {
        makeMove(chessBoard, transpositionScore->moveScore.move, hashes);

        if (isThreeFoldRepetition(chessBoard))
        {
            unMakeMove(chessBoard, transpositionScore->moveScore.move);
            //ASSERT_CHESS_BOARD(original, chessBoard);
        }
        else
        {
            unMakeMove(chessBoard, transpositionScore->moveScore.move);
            //ASSERT_CHESS_BOARD(original, chessBoard);
            //free(original);
            MoveScore transpositionMove = transpositionScore->moveScore;
            transpositionMove.eval = getScoreFromTransposition(transpositionMove.eval, mateDistance);
            return transpositionMove;
        }
    }
    
    int ownKingSq = getSqInd(side ? chessBoard->pieceBoards[blackKing] : chessBoard->pieceBoards[whiteKing]);
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
    uint16_t moves[MAX_MOVE_COUNT];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    GradedMoveList gradedMoveList;
    GradedMove gradedMoves[MAX_MOVE_COUNT];
    gradedMoveList.gradedMoves = gradedMoves;

    int legalMoves = 0;

    MoveScore moveScore;

    if (gotChecked)
    {
        generateMoves(chessBoard, attackTables, &moveList);
        gradeMoves(chessBoard, transpositionTable, &moveList, &gradedMoveList, depthSearched);
    }
    else
    {
        generateTactivalMoves(chessBoard, attackTables, &moveList);
        gradeTacticalMoves(chessBoard, &moveList, &gradedMoveList);
    }

    gradedMoveList.nextIndex = moveList.nextIndex;

    for (int i = 0; i < gradedMoveList.nextIndex; i++)
    {
        updateTime();

        if (timeLimitReached && currentDepth != 1)
        {
            //free(original);
            return bestMove;
        }

        setBestMoveFirst(&gradedMoveList, i);

        makeMove(chessBoard, gradedMoveList.gradedMoves[i].move, hashes);

        ownKingSq = getSqInd(side ? chessBoard->pieceBoards[blackKing] : chessBoard->pieceBoards[whiteKing]);
        int isNotLegalMove = isSquareAttacked(ownKingSq, chessBoard, attackTables, side);

        if (!isNotLegalMove)
        {
            legalMoves++;

            if (isThreeFoldRepetition(chessBoard))
            {
                moveScore.eval = DRAW;
                moveScore.move = gradedMoveList.gradedMoves[i].move;
            }
            else
            {
                moveScore = qsearch(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1, mateDistance + 1, -beta, -alpha, !side);
                moveScore.eval = -moveScore.eval;
            }

            if (moveScore.eval > bestMove.eval || legalMoves == 1)
            {
                bestMove.eval = moveScore.eval;
                bestMove.move = gradedMoveList.gradedMoves[i].move;
            }

            if (moveScore.eval > alpha)
            {
                alpha = moveScore.eval;
            }

            if (alpha >= beta)
            {
                unMakeMove(chessBoard, gradedMoveList.gradedMoves[i].move);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
        }

        unMakeMove(chessBoard, gradedMoveList.gradedMoves[i].move);
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
    nodesSearched++;

    MoveScore bestMove;
    bestMove.eval = MIN_EVAL;
    bestMove.move = 0;
    
    if (depthSearched > currentDepth)
    {
        bestMove = qsearch(chessBoard, attackTables, hashes, transpositionTable, depthSearched, mateDistance, alpha, beta, side);
        return bestMove;
    }

    int mateValue = -MATED - mateDistance;

    if (mateValue < beta)
    {
        beta = mateValue;
        if (alpha >= beta)
        {
            bestMove.eval = mateValue;
            return bestMove;
        }
        
    }

    mateValue = MATED - mateDistance;

    if (mateValue > alpha)
    {
        alpha = mateValue;
        if (beta <= alpha)
        {
            bestMove.eval = mateValue;
            return bestMove;
        }
        
    }

    //ChessBoard* original = malloc(sizeof(ChessBoard));
    //memcpy(original, chessBoard, sizeof(ChessBoard));

    int originalAlpha = alpha;
    int originalBeta = beta;

    MoveList moveList;
    uint16_t moves[MAX_MOVE_COUNT];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    MoveScore moveScore;

    TranspositionTableEntry* transpositionScore = checkTranspositionHit(chessBoard, transpositionTable, currentDepth - depthSearched, originalAlpha, originalBeta);
    int legalMoves = 0;


    if (transpositionScore != NULL)
    {
        makeMove(chessBoard, transpositionScore->moveScore.move, hashes);

        if (isThreeFoldRepetition(chessBoard))
        {
            unMakeMove(chessBoard, transpositionScore->moveScore.move);
            //ASSERT_CHESS_BOARD(original, chessBoard);
        }
        else
        {
            unMakeMove(chessBoard, transpositionScore->moveScore.move);
            //ASSERT_CHESS_BOARD(original, chessBoard);
            //free(original);
            MoveScore transpositionMove = transpositionScore->moveScore;
            transpositionMove.eval = getScoreFromTransposition(transpositionMove.eval, mateDistance);
            
            return transpositionMove;
        }
    }

    int ownKingSq = getSqInd(side ? chessBoard->pieceBoards[blackKing] : chessBoard->pieceBoards[whiteKing]);
    int amChecked = isSquareAttacked(ownKingSq, chessBoard, attackTables, side);

    if (!isNullMove && currentDepth - depthSearched >= 3 && !amChecked && depthSearched != 0 && hasNonPawnPieces(chessBoard, side) && isBetaValid(beta))
    {
        uint16_t nullMove = 0;

        MoveScore nullMoveScore;
        nullMoveScore.move = nullMove;

        isNullMove = 1;

        makeNullMove(chessBoard, hashes);

        nullMoveScore = negamax(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1 + NULL_MOVE_SKIP, mateDistance + 1, -beta, -beta + 1, !side);
        nullMoveScore.eval = -nullMoveScore.eval;

        unMakeNullMove(chessBoard);

        isNullMove = 0;

        if (nullMoveScore.eval >= beta)
        {
            bestMove.eval = beta;
            
            //free(original);
            return bestMove;
        }
    }

    generateMoves(chessBoard, attackTables, &moveList);

    GradedMoveList gradedMoveList;
    GradedMove gradedMoves[MAX_MOVE_COUNT];
    gradedMoveList.gradedMoves = gradedMoves;
    gradedMoveList.nextIndex = moveList.nextIndex;

    gradeMoves(chessBoard, transpositionTable, &moveList, &gradedMoveList, depthSearched);

    int isFirstMove = 1;

    for (int i = 0; i < gradedMoveList.nextIndex; i++)
    {
        updateTime();

        if (timeLimitReached && currentDepth != 1)
        {
            //free(original);
            return bestMove;
        }

        setBestMoveFirst(&gradedMoveList, i);

        uint8_t capturedPiece = chessBoard->pieceLookup[getToSq(gradedMoveList.gradedMoves[i].move)];

        makeMove(chessBoard, gradedMoveList.gradedMoves[i].move, hashes);

        ownKingSq = getSqInd(side ? chessBoard->pieceBoards[blackKing] : chessBoard->pieceBoards[whiteKing]);

        int isChecked = isSquareAttacked(ownKingSq, chessBoard, attackTables, side);

        if (!isChecked)
        {
            legalMoves++;

            int enemyKingSq = getSqInd(side ? chessBoard->pieceBoards[whiteKing] : chessBoard->pieceBoards[blackKing]);
            int isEnemyChecked = isSquareAttacked(enemyKingSq, chessBoard, attackTables, !side);
            int moveReduction = 0;

            if (i > 3 && !isEnemyChecked && !amChecked && currentDepth - depthSearched >= 3 && !isTacticalMove(capturedPiece, gradedMoveList.gradedMoves[i].move))
            {
                moveReduction = lateMoveReductionTable[i][currentDepth - depthSearched];
            }

            if (isThreeFoldRepetition(chessBoard))
            {
                moveScore.move = gradedMoveList.gradedMoves[i].move;
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
                    
                    if (moveReduction > 0 && moveScore.eval > alpha)
                    {
                        moveScore = negamax(chessBoard, attackTables, hashes, transpositionTable,  depthSearched + 1, mateDistance + 1, -alpha - 1, -alpha, !side);
                        moveScore.eval = -moveScore.eval;
                    }

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
                bestMove.move = gradedMoveList.gradedMoves[i].move;
            }

            isFirstMove = 0;

            if (moveScore.eval > alpha)
            {
                alpha = moveScore.eval;
            }

            if (alpha >= beta)
            {
                unMakeMove(chessBoard, gradedMoveList.gradedMoves[i].move);
                //ASSERT_CHESS_BOARD(original, chessBoard);

                if (!isTacticalMove(capturedPiece, gradedMoveList.gradedMoves[i].move))
                {
                    uint8_t movedPiece = chessBoard->pieceLookup[getFromSq(gradedMoveList.gradedMoves[i].move)];

                    setKillerMove(gradedMoveList.gradedMoves[i].move, depthSearched);
                    updateHistoryHeuristic(gradedMoveList.gradedMoves[i].move, movedPiece, currentDepth - depthSearched);

                    for (int moveInd = i - 1; moveInd >= 0; moveInd--)
                    {
                        if (gradedMoveList.gradedMoves[moveInd].grade > MAX_HISTORY_SCORE)
                        {
                            break;
                        }
                        
                        if (gradedMoveList.gradedMoves[moveInd].grade > MIN_HISOTRY_SCORE)
                        {
                            penalizeHistoryHeuristic(gradedMoveList.gradedMoves[moveInd].move, movedPiece, currentDepth - depthSearched);
                        }
                    }
                }

                
                break;
            }
        }

        unMakeMove(chessBoard, gradedMoveList.gradedMoves[i].move);
        //ASSERT_CHESS_BOARD(original, chessBoard);
    }

    //free(original);

    if (legalMoves == 0)
    {
        ownKingSq = getSqInd(side ? chessBoard->pieceBoards[blackKing] : chessBoard->pieceBoards[whiteKing]);
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
    initKillerMoves(currentDepth);
    bestMove = negamax(chessBoard, attackTables, hashes, transpositionTable, 1, 1, MIN_EVAL, MAX_EVAL, isBlack(chessBoard));
    return bestMove;
}

MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTable* transpositionTable, uint64_t timePerMove)
{
    MoveScore currentBestMove;
    MoveScore depthBestMove;

    initLateMoveReductionTable();

    timeLimitReached = 0;
    timeCheckCounter = 1;
    stopTime = getTimeMs() + timePerMove;

    currentDepth = 1;
    qSearchDepthReached = 1;

    nodesSearched = 0;
    while (!timeLimitReached)
    {
        /*
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
    
        if (currentDepth > MAX_DEPTH)
        {
            break;
        }
        
    }

    printf("Nodes searched: %d \n", nodesSearched);
    printf("PVS checks: %llu, PVS reserches: %llu\n", (long long unsigned)pvsChecks, (long long unsigned)pvsResearches);
    printf("TT moves searched: %llu, TT moves found: %llu\n", (long long unsigned)getTTMovesSearched(), (long long unsigned)getTTMovesFound());

    return currentBestMove;
}