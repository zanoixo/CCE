#include <string.h>
#include <math.h>

#include "Search.h"
#include "ChessBoard.h"
#include "MoveGenerator.h"
#include "Utils.h"
#include "Eval.h"
#include "Tests.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"
#include "MakeMove.h"
#include "UnMakeMove.h"
#include "AttackTables.h"
#include "Eval.h"

Move killerMoves[KILLER_MOVE_DEPTH][2];
int historyHeuristic[BOARD_SIZE][BOARD_SIZE][DIFFERENT_PIECE_COUNT / 2];
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

void penalizeHistoryHeuristic(Move move, int remeniningDepth)
{
    historyHeuristic[getFromSq(move.move)][getToSq(move.move)][getPiece(move) - 1] -= remeniningDepth;     
}

void updateHistoryHeuristic(Move move, int remeniningDepth)
{
    historyHeuristic[getFromSq(move.move)][getToSq(move.move)][getPiece(move) - 1] += remeniningDepth * remeniningDepth; 
}

int getHistoryHeuristic(Move move)
{
    return historyHeuristic[getFromSq(move.move)][getToSq(move.move)][getPiece(move) - 1];
}

void clearHistoryHeuristic()
{
    memset(historyHeuristic, 0, sizeof(historyHeuristic));
}

void initKillerMoves()
{
    for (int i = 0; i < currentDepth; i++)
    {
        killerMoves[i][0] = (Move){0, 0, 0};
        killerMoves[i][1] = (Move){0, 0, 0};
    }
}

void findKillerMoves(MoveList *moveList, int depth)
{
    for (int i = 0; i < moveList->nextIndex; i++)
    {
        if (moveList->moves[i].move == killerMoves[depth][0].move)
        {
            moveList->moves[i].score = 200;
        }

        if (moveList->moves[i].move == killerMoves[depth][1].move)
        {
            moveList->moves[i].score = 100;
        }
        
    }
    
}

void setKillerMove(Move killerMove, int depth)
{
    if (!(killerMoves[depth][0].move == killerMove.move) &&
        !(killerMoves[depth][1].move == killerMove.move))
    {
        killerMoves[depth][1] = killerMoves[depth][0];
        killerMoves[depth][0] = killerMove;
    } 
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

int isValidQSearchMove(Move move)
{    
    return getCapturedPiece(move)  || getPromotionPiece(move);
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
    bestMove.move = (Move){0, 0, 0};

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
        makeMove(chessBoard, &transpositionScore->moveScore.move, hashes);

        if (isThreeFoldRepetition(chessBoard))
        {
            unMakeMove(chessBoard, &transpositionScore->moveScore.move);
            //ASSERT_CHESS_BOARD(original, chessBoard);
        }
        else
        {
            unMakeMove(chessBoard, &transpositionScore->moveScore.move);
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

        if (!gotChecked && !isValidQSearchMove(moveList.moves[i]))
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
                unMakeMove(chessBoard, &moveList.moves[i]);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i]);
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
    bestMove.move = (Move){0, 0, 0};
    
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
            unMakeMove(chessBoard, &transpositionScore->moveScore.move);
            //ASSERT_CHESS_BOARD(original, chessBoard);
        }
        else
        {
            unMakeMove(chessBoard, &transpositionScore->moveScore.move);
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
        Move nullMove = (Move){0, 0, 0};

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

            if (i > 3 && !isEnemyChecked && !amChecked && currentDepth - depthSearched >= 3 && !getCapturedPiece(moveList.moves[i]) && !getPromotionPiece(moveList.moves[i]))
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
                bestMove.move = moveList.moves[i];
            }

            isFirstMove = 0;

            if (moveScore.eval > alpha)
            {
                alpha = moveScore.eval;
            }

            if (alpha >= beta)
            {
                if (!getPromotionPiece(moveList.moves[i]) && !getCapturedPiece(moveList.moves[i]))
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

                unMakeMove(chessBoard, &moveList.moves[i]);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i]);
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
    stopTime = getTimeMs() + timePerMove;

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