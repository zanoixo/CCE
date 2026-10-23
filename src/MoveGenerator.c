#include "Eval.h"
#include "MoveGenerator.h"
#include "Utils.h"
#include "ChessBoard.h"
#include "ChessBitboards.h"
#include "AttackTables.h"
#include "MoveGeneratorHelper.h"

void generateKingMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t kingPositions = chessBoard->pieceBoards[whiteKing + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t friendlyPieces = chessBoard->coloredBoards[turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    uint64_t from = kingPositions & -kingPositions;
    uint8_t fromSq = getSqInd(from);

    uint64_t kingAttacks = attackTables->kingAttacks[fromSq];
    kingAttacks &= ~friendlyPieces;

    while (kingAttacks != 0)
    {
        uint64_t to = kingAttacks & -kingAttacks;

        if (to & enemyPieces)
        {   
            addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);    
        }else
        {
            addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
        }
        
        kingAttacks &= kingAttacks - 1;
    }
}

void generateKnightMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t knightPositions = chessBoard->pieceBoards[whiteKnight + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t friendlyPieces = chessBoard->coloredBoards[turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    while (knightPositions != 0)
    {
        uint64_t from =  knightPositions & -knightPositions;
        uint8_t fromSq = getSqInd(from);

        uint64_t knightAttacks = attackTables->knightAttacks[fromSq];
        knightAttacks &= ~friendlyPieces;

        while (knightAttacks != 0)
        {
            uint64_t to = knightAttacks & -knightAttacks;

            if (to & enemyPieces)
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);    
            }else
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
            }
            
            knightAttacks &= knightAttacks - 1;
        }

        knightPositions &= knightPositions - 1;
    }
}

void generateBishopMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t bishopPositions = chessBoard->pieceBoards[whiteBishop + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t friendlyPieces = chessBoard->coloredBoards[turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    while (bishopPositions != 0)
    {
        uint64_t from = bishopPositions & -bishopPositions;
        uint8_t fromSq = getSqInd(from);
        uint64_t bishopAttacks = getBishopAttackPattern(fromSq, chessBoard->allPieces, attackTables);
        bishopAttacks &= ~friendlyPieces;

        while (bishopAttacks != 0)
        {
            uint64_t to = bishopAttacks & -bishopAttacks;

            if (to & enemyPieces)
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);    
            }else
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
            }
            
            bishopAttacks &= bishopAttacks - 1;
        }

        bishopPositions &= bishopPositions - 1;
    }
}

void generateQueenMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t queenPositions = chessBoard->pieceBoards[whiteQueen + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t friendlyPieces = chessBoard->coloredBoards[turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    while (queenPositions != 0)
    {
        uint64_t from = queenPositions & -queenPositions;
        uint8_t fromSq = getSqInd(from);

        uint64_t queenAttacks = getQueenAttackPattern(fromSq, chessBoard->allPieces, attackTables);
        queenAttacks &= ~friendlyPieces;

        while (queenAttacks != 0)
        {
            uint64_t to = queenAttacks & -queenAttacks;

            if (to & enemyPieces)
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);    
            }else
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
            }
            
            queenAttacks &= queenAttacks - 1;
        }

        queenPositions &= queenPositions - 1;
    }
}

void generatePawnMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
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
                }else
                {
                    addMove(from, next, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
                }

                if (from & line7 && ((from >> 16) & (~chessBoard->allPieces)))
                {
                    addMove(from, from >> 16, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
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
                }else
                {
                    addMove(from, next, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
                }

                if (from & line2 && ((from << 16) & (~chessBoard->allPieces)))
                {
                    addMove(from, from << 16, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
                }
            } 
        }
        
        uint64_t pawnAttacks = pawnAttackTable[fromSq];

        while (pawnAttacks != 0)
        {   
            uint64_t to = pawnAttacks & -pawnAttacks;

            if (to & enemyPieces)
            {
                if (to & promotionLine)
                {
                    generatePawnPromotionMoves(from, to, moveList);
                }else
                {
                    addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
                }
                 
            }

            if ((chessBoard->enPassantSq & to) && (chessBoard->enPassantSq & enpassantLine))
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, ENPASSANT_PRESENT_FLAG, moveList);
            }
            
            pawnAttacks &= pawnAttacks - 1;
        }

        pawnPositions &= pawnPositions - 1;
    }
}

void generateRookMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint8_t turnPlayer = isBlack(chessBoard);

    uint64_t rookPositions = chessBoard->pieceBoards[whiteRook + GENERIC_PIECE_TYPES * turnPlayer];
    uint64_t friendlyPieces = chessBoard->coloredBoards[turnPlayer];
    uint64_t enemyPieces = chessBoard->coloredBoards[!turnPlayer];
    
    while (rookPositions != 0)
    {
        uint64_t from = rookPositions & -rookPositions;
        uint8_t fromSq = getSqInd(from);
        
        uint64_t rookAttacks = getRookAttackPattern(fromSq, chessBoard->allPieces, attackTables);
        rookAttacks &= ~friendlyPieces;

        while (rookAttacks != 0)
        {
            uint64_t to = rookAttacks & -rookAttacks;

            if (to & enemyPieces)
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
            }else
            {
                addMove(from, to, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);   
            } 
            
            rookAttacks &= rookAttacks - 1;
        }

        rookPositions &= rookPositions - 1;
    }
}

void generateCastleMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    if (isBlack(chessBoard))
    {
        if (canBlackShortCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & f8) && !(chessBoard->allPieces & g8) && 
                !isSquareAttacked(e8Sq, chessBoard, attackTables, 1) && 
                !isSquareAttacked(f8Sq, chessBoard, attackTables, 1) && 
                !isSquareAttacked(g8Sq, chessBoard, attackTables, 1))
            {
                addMove(e8, g8, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
            }
                
        }

        if (canBlackLongCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & b8) && !(chessBoard->allPieces & c8) && !(chessBoard->allPieces & d8) && 
                !isSquareAttacked(e8Sq, chessBoard, attackTables, 1) && 
                !isSquareAttacked(c8Sq, chessBoard, attackTables, 1) &&  
                !isSquareAttacked(d8Sq, chessBoard, attackTables, 1)) 
            {
                addMove(e8, c8, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
            }    
        }
    }else
    {
        if (canWhiteShortCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & f1) && !(chessBoard->allPieces & g1) && 
                !isSquareAttacked(e1Sq, chessBoard, attackTables, 0) && 
                !isSquareAttacked(f1Sq, chessBoard, attackTables, 0) && 
                !isSquareAttacked(g1Sq, chessBoard, attackTables, 0))
            {
                addMove(e1, g1, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
            }    
        }

        if (canWhiteLongCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & b1) && !(chessBoard->allPieces & c1) && !(chessBoard->allPieces & d1) && 
                !isSquareAttacked(e1Sq, chessBoard, attackTables, 0) && 
                !isSquareAttacked(c1Sq, chessBoard, attackTables, 0) &&  
                !isSquareAttacked(d1Sq, chessBoard, attackTables, 0)) 
            {
                addMove(e1, c1, EMPTY_PROMOTION_FLAG, EMPTY_ENPASSANT_FLAG, moveList);
            } 
        }
    }
    
}

void generateMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    generateKnightMoves(chessBoard, attackTables, moveList);
    generateKingMoves(chessBoard, attackTables, moveList);
    generateBishopMoves(chessBoard, attackTables, moveList);
    generateRookMoves(chessBoard, attackTables, moveList);
    generateQueenMoves(chessBoard, attackTables, moveList);
    generatePawnMoves(chessBoard, attackTables, moveList);
    generateCastleMoves(chessBoard, attackTables, moveList);
}

