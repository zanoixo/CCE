#include "Eval.h"
#include "TacticalMoveGenerator.h"
#include "Utils.h"
#include "ChessBoard.h"
#include "ChessBitboards.h"
#include "AttackTables.h"
#include "MoveGeneratorHelper.h"

void generateTacticalKingMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t kingPositions = chessBoard->pieceBoards[whiteKing + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    uint64_t from = kingPositions & -kingPositions;
    uint8_t fromSq = getSqInd(from);

    uint64_t kingAttacks = attackTables->kingAttacks[fromSq] & enemyPieces;

    while (kingAttacks != 0)
    {
        uint64_t to = kingAttacks & -kingAttacks;
        uint8_t toSq = getSqInd(to);

        addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList, calculateCaptureMoveScore(chessBoard, fromSq, toSq));    
        
        kingAttacks &= kingAttacks - 1;
    }
}

void generateTacticalKnightMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t knightPositions = chessBoard->pieceBoards[whiteKnight + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    while (knightPositions != 0)
    {
        uint64_t from =  knightPositions & -knightPositions;
        uint8_t fromSq = getSqInd(from);

        uint64_t knightAttacks = attackTables->knightAttacks[fromSq] & enemyPieces;

        while (knightAttacks != 0)
        {
            uint64_t to = knightAttacks & -knightAttacks;
            uint8_t toSq = getSqInd(to);

            addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList, calculateCaptureMoveScore(chessBoard, fromSq, toSq));    

            knightAttacks &= knightAttacks - 1;
        }

        knightPositions &= knightPositions - 1;
    }
}

void generateTacticalBishopMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t bishopPositions = chessBoard->pieceBoards[whiteBishop + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    while (bishopPositions != 0)
    {
        uint64_t from = bishopPositions & -bishopPositions;
        uint8_t fromSq = getSqInd(from);
        uint64_t bishopAttacks = getBishopAttackPattern(fromSq, chessBoard->allPieces, attackTables) & enemyPieces;

        while (bishopAttacks != 0)
        {
            uint64_t to = bishopAttacks & -bishopAttacks;
            uint8_t toSq = getSqInd(to); 

            addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList, calculateCaptureMoveScore(chessBoard, fromSq, toSq));    
            
            bishopAttacks &= bishopAttacks - 1;
        }

        bishopPositions &= bishopPositions - 1;
    }
}

void generateTacticalQueenMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t queenPositions = chessBoard->pieceBoards[whiteQueen + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    while (queenPositions != 0)
    {
        uint64_t from = queenPositions & -queenPositions;
        uint8_t fromSq = getSqInd(from);

        uint64_t queenAttacks = getQueenAttackPattern(fromSq, chessBoard->allPieces, attackTables) & enemyPieces;

        while (queenAttacks != 0)
        {
            uint64_t to = queenAttacks & -queenAttacks;
            uint8_t toSq = getSqInd(to);

            addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList, calculateCaptureMoveScore(chessBoard, fromSq, toSq));    
            
            queenAttacks &= queenAttacks - 1;
        }

        queenPositions &= queenPositions - 1;
    }
}

void generateTacticalPawnMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t pawnPositions = chessBoard->pieceBoards[whitePawn];
    uint64_t enemyPieces = chessBoard->coloredBoards[black];
    uint64_t *pawnAttackTable = attackTables->whitePawnsAttacks;
    uint64_t promotionLine = line8;
    uint64_t enpassantLine = line6;

    if (isBlack(chessBoard))
    {
        pawnPositions = chessBoard->pieceBoards[blackPawn];
        enemyPieces = chessBoard->coloredBoards[white];
        pawnAttackTable = attackTables->blackPawnsAttacks;
        promotionLine = line1;
        enpassantLine = line3;
    }  
    
    while (pawnPositions != 0)
    {   
        uint64_t from = pawnPositions & -pawnPositions;
        uint8_t fromSq = getSqInd(from);

        if (isBlack(chessBoard))
        {
            uint64_t next = from >> 8;
            if (next & (~chessBoard->allPieces))
            {
                if (next & promotionLine)
                {
                    generatePawnPromotionMoves(from, next, moveList);
                }
            }
                    
        }else
        {
            uint64_t next = from << 8;
            if (next & (~chessBoard->allPieces))
            {
                if (next & promotionLine)
                {
                    generatePawnPromotionMoves(from, next, moveList);
                }
            } 
        }
        
        uint64_t pawnAttacks = pawnAttackTable[fromSq] & enemyPieces;

        while (pawnAttacks != 0)
        {   
            uint64_t to = pawnAttacks & -pawnAttacks;
            uint8_t toSq = getSqInd(to);

            if (to & promotionLine)
            {
                generatePawnPromotionMoves(from, to, moveList);
            }else
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList, calculateCaptureMoveScore(chessBoard, fromSq, toSq));
            }

            if ((chessBoard->enPassantSq & to) && (chessBoard->enPassantSq & enpassantLine))
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, ENPASSANT_PRESENT_FLAG, moveList, calculateCaptureMoveScore(chessBoard, fromSq, getSqInd(chessBoard->enPassantSq)));
            }
            
            pawnAttacks &= pawnAttacks - 1;
        }

        pawnPositions &= pawnPositions - 1;
    }
}

void generateTacticalRookMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t rookPositions = chessBoard->pieceBoards[whiteRook + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    while (rookPositions != 0)
    {
        uint64_t from = rookPositions & -rookPositions;
        uint8_t fromSq = getSqInd(from);
        
        uint64_t rookAttacks = getRookAttackPattern(fromSq, chessBoard->allPieces, attackTables) & enemyPieces;

        while (rookAttacks != 0)
        {
            uint64_t to = rookAttacks & -rookAttacks;
            uint8_t toSq = getSqInd(to);

            addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList, calculateCaptureMoveScore(chessBoard, fromSq, toSq));

            rookAttacks &= rookAttacks - 1;
        }

        rookPositions &= rookPositions - 1;
    }
}

void generateTactivalMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    generateTacticalKnightMoves(chessBoard, attackTables, moveList);
    generateTacticalKingMoves(chessBoard, attackTables, moveList);
    generateTacticalBishopMoves(chessBoard, attackTables, moveList);
    generateTacticalRookMoves(chessBoard, attackTables, moveList);
    generateTacticalQueenMoves(chessBoard, attackTables, moveList);
    generateTacticalPawnMoves(chessBoard, attackTables, moveList);
}