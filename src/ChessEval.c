#include "ChessBoard.h"
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"
#include "ChessEval.h"

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


int evaluatePosition(ChessBoard *chessBoard)
{
    int score = 0;

    score += countPieces(chessBoard->whitePawns)   * PAWN_VALUE;
    score += countPieces(chessBoard->whiteKnights) * KNIGHT_VALUE;
    score += countPieces(chessBoard->whiteBishops) * BISHOP_VALUE;
    score += popCount(chessBoard->whiteRooks)   * ROOK_VALUE;
    score += popCount(chessBoard->whiteQueens)  * QUEEN_VALUE;

    score -= countPieces(chessBoard->blackPawns)   * PAWN_VALUE;
    score -= countPieces(chessBoard->blackKnights) * KNIGHT_VALUE;
    score -= countPieces(chessBoard->blackBishops) * BISHOP_VALUE;
    score -= countPieces(chessBoard->blackRooks)   * ROOK_VALUE;
    score -= countPieces(chessBoard->blackQueens)  * QUEEN_VALUE;

    return score;
}

int whiteMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta)
{
    if (depth == 0)
    {
        return evaluatePosition(chessBoard);
    }

    MoveList moveList;
    moveList.moves = malloc(sizeof(Move) * 256);
    moveList.nextIndex = 0;

    int legalMoves = 0;

    generateMoves(chessBoard, attackTables, &moveList);

    int bestScore = MIN_INT;

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        makeMove(chessBoard, &moveList.moves[i]);

        uint64_t kingPosition = chessBoard->whiteKing;

        if (!isSquareAttacked(getSqInd(kingPosition), chessBoard, attackTables, white))
        {
            legalMoves++;

            int score = blackMove(chessBoard, attackTables, depth - 1, alpha, beta);

            if (score > bestScore)
            {
                bestScore = score;
            }

            if (score > alpha)
            {
                alpha = score;
            }

            if (alpha >= beta)
            {
                unMakeMove(chessBoard, &moveList.moves[i]);
                break;
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i]);
    }

    free(moveList.moves);

    if (legalMoves == 0)
    {
        if (isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, black))
        {
            return MIN_INT;
        }

        return 0;
    }

    return bestScore;
}

int blackMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta)
{
    if (depth == 0)
    {
        return evaluatePosition(chessBoard);
    }

    MoveList moveList;
    moveList.moves = malloc(sizeof(Move) * 256);
    moveList.nextIndex = 0;

    int legalMoves = 0;

    generateMoves(chessBoard, attackTables, &moveList);

    int bestScore = MAX_INT;

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        makeMove(chessBoard, &moveList.moves[i]);

        uint64_t kingPosition = chessBoard->blackKing;

        if (!isSquareAttacked(getSqInd(kingPosition), chessBoard, attackTables, black))
        {
            legalMoves++;

            int score = whiteMove(chessBoard, attackTables, depth - 1, alpha, beta);

            if (score < bestScore)
            {
                bestScore = score;
            }

            if (score < beta)
            {
                beta = score;
            }

            if (alpha >= beta)
            {
                unMakeMove(chessBoard, &moveList.moves[i]);
                break;
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i]);
    }

    free(moveList.moves);

    if (legalMoves == 0)
    {
        if (isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, black))
        {
            return MAX_INT;
        }

        return 0;
    }

    return bestScore;
}

int evaluate(ChessBoard *chessBoard)
{
    if (isBlack(chessBoard))
    {
        /* code */
    }
    
}