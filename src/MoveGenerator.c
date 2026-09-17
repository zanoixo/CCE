#include "Eval.h"
#include "MoveGenerator.h"
#include "Utils.h"
#include "ChessBoard.h"
#include "ChessBitboards.h"
#include "AttackTables.h"

int calculateCaptureMoveScore(uint8_t attackerPiece, uint8_t capturedPiece)
{
    int attackerScore = getPieceScore(attackerPiece);
    int capturedScore = getPieceScore(capturedPiece);

    int score;

    if (attackerScore < capturedScore + 30 )
    {
        score = 2000 + 10 * capturedScore - attackerScore;
    }
    else
    {
        score = -2000 + 10 * capturedScore - attackerScore;
    }
    
    return score;
}

void addMove(uint64_t from, uint64_t to, uint16_t flags, MoveList* moveList, int score)
{
    moveList->moves[moveList->nextIndex] = (Move){ from, to, flags, score };
    moveList->nextIndex++;
}

void generatePawnPromotionMoves(uint64_t from, uint64_t to, uint16_t flags, MoveList* moveList)
{
    addMove(from, to, flags | queenPromotion, moveList, QUEEN_PROMOTION_VALUE);
    addMove(from, to, flags | rookPromotion, moveList, ROOK_PROMOTION_VALUE);
    addMove(from, to, flags | bishopPromotion, moveList, BISHOP_PROMOTION_VALUE);
    addMove(from, to, flags | knightPromotion, moveList, KNIGHT_PROMOTION_VALUE);
}

void generateKingMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t kingPositions = chessBoard->whiteKing;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        kingPositions = chessBoard->blackKing;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    uint64_t fromSq = kingPositions & -kingPositions;
    uint64_t kingAttacks = attackTables->kingAttacks[getSqInd(fromSq)];
    kingAttacks &= ~friendlyPieces;

    while (kingAttacks != 0)
    {
        uint16_t moveFlags = king << pieceFlagPosition;
        uint64_t toSq = kingAttacks & -kingAttacks;

        if (toSq & enemyPieces)
        {   
            uint8_t enemyColor = !isBlack(chessBoard);
            uint8_t capturedPiece = getPieceFromSquare(toSq, enemyColor, chessBoard);
            moveFlags |= capturedPiece << captureFlagPostion;
            addMove(fromSq, toSq, moveFlags, moveList, calculateCaptureMoveScore(king, capturedPiece));    
        }else
        {
            addMove(fromSq, toSq, moveFlags, moveList, 0);
        }
        
        kingAttacks &= kingAttacks - 1;
    }
}

void generateKnightMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t knightPositions = chessBoard->whiteKnights;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        knightPositions = chessBoard->blackKnights;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    while (knightPositions != 0)
    {
        uint64_t fromSq =  knightPositions & -knightPositions;
        uint64_t knightAttacks = attackTables->knightAttacks[getSqInd(fromSq)];
        knightAttacks &= ~friendlyPieces;

        while (knightAttacks != 0)
        {
            uint16_t moveFlags = knight << pieceFlagPosition;
            uint64_t toSq= knightAttacks & -knightAttacks;
            if (toSq & enemyPieces)
            {
                uint8_t enemyColor = !isBlack(chessBoard);
                uint8_t capturedPiece = getPieceFromSquare(toSq, enemyColor, chessBoard);
                moveFlags |= capturedPiece << captureFlagPostion;
                addMove(fromSq, toSq, moveFlags, moveList, calculateCaptureMoveScore(knight, capturedPiece));    
            }else
            {
                addMove(fromSq, toSq, moveFlags, moveList, 0);
            }
            
            knightAttacks &= knightAttacks - 1;
        }

        knightPositions &= knightPositions - 1;
    }
}

void generateBishopMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t bishopPositions = chessBoard->whiteBishops;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        bishopPositions = chessBoard->blackBishops;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    while (bishopPositions != 0)
    {
        uint64_t fromSq = bishopPositions & -bishopPositions;
        uint64_t bishopAttacks = getBishopAttackPattern(getSqInd(fromSq), chessBoard->allPieces, attackTables);
        bishopAttacks &= ~friendlyPieces;

        while (bishopAttacks != 0)
        {
            uint16_t moveFlags = bishop << pieceFlagPosition;
            uint64_t toSq = bishopAttacks & -bishopAttacks;
            if (toSq & enemyPieces)
            {
                uint8_t enemyColor = !isBlack(chessBoard);
                uint8_t capturedPiece = getPieceFromSquare(toSq, enemyColor, chessBoard);
                moveFlags |= capturedPiece << captureFlagPostion;
                addMove(fromSq, toSq, moveFlags, moveList, calculateCaptureMoveScore(bishop, capturedPiece));    
            }else
            {
                addMove(fromSq, toSq, moveFlags, moveList, 0);
            }
            
            bishopAttacks &= bishopAttacks - 1;
        }

        bishopPositions &= bishopPositions - 1;
    }
}

void generateQueenMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t queenPositions = chessBoard->whiteQueens;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        queenPositions = chessBoard->blackQueens;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    while (queenPositions != 0)
    {
        uint64_t fromSq = queenPositions & -queenPositions;
        uint64_t queenAttacks = getQueenAttackPattern(getSqInd(fromSq), chessBoard->allPieces, attackTables);
        queenAttacks &= ~friendlyPieces;

        while (queenAttacks != 0)
        {
            uint16_t moveFlags = queen << pieceFlagPosition;
            uint64_t toSq = queenAttacks & -queenAttacks;
            if (toSq & enemyPieces)
            {
                uint8_t enemyColor = !isBlack(chessBoard);
                uint8_t capturedPiece = getPieceFromSquare(toSq, enemyColor, chessBoard);
                moveFlags |= capturedPiece << captureFlagPostion;
                addMove(fromSq, toSq, moveFlags, moveList, calculateCaptureMoveScore(queen, capturedPiece));    
            }else
            {
                addMove(fromSq, toSq, moveFlags, moveList, 0);
            }
            
            queenAttacks &= queenAttacks - 1;
        }

        queenPositions &= queenPositions - 1;
    }
}

void generatePawnMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t pawnPositions = chessBoard->whitePawns;
    uint64_t enemyPieces = chessBoard->blackPieces;
    uint64_t *pawnAttackTable = attackTables->whitePanwsAttacks;
    uint64_t promotionLine = line8;
    uint64_t enpassantLine = line6;

    if (isBlack(chessBoard))
    {
        pawnPositions = chessBoard->blackPawns;
        enemyPieces = chessBoard->whitePieces;
        pawnAttackTable = attackTables->blackPanwsAttacks;
        promotionLine = line1;
        enpassantLine = line3;
    }  
    
    while (pawnPositions != 0)
    {   
        uint16_t moveFlags = pawn << pieceFlagPosition;
        uint64_t fromSq = pawnPositions & -pawnPositions;

        if (isBlack(chessBoard))
        {
            uint64_t nextSq = fromSq >> 8;
            if (nextSq & (~chessBoard->allPieces))
            {
                if (nextSq & promotionLine)
                {
                    generatePawnPromotionMoves(fromSq, nextSq, moveFlags, moveList);
                }else
                {
                    addMove(fromSq, nextSq, moveFlags, moveList, 0);
                }

                if (fromSq & line7 && ((fromSq >> 16) & (~chessBoard->allPieces)))
                {
                    addMove(fromSq, fromSq >> 16, moveFlags, moveList, 0);
                }
            }
                    
        }else
        {
            uint64_t nextSq = fromSq << 8;
            if (nextSq & (~chessBoard->allPieces))
            {
                if (nextSq & promotionLine)
                {
                    generatePawnPromotionMoves(fromSq, nextSq, moveFlags, moveList);
                }else
                {
                    addMove(fromSq, nextSq, moveFlags, moveList, 0);
                }

                if (fromSq & line2 && ((fromSq << 16) & (~chessBoard->allPieces)))
                {
                    addMove(fromSq, fromSq << 16, moveFlags, moveList, 0);
                }
            } 
        }
        
        uint64_t pawnAttacks = pawnAttackTable[getSqInd(fromSq)];

        while (pawnAttacks != 0)
        {   
            moveFlags = pawn << pieceFlagPosition;
            uint64_t toSq = pawnAttacks & -pawnAttacks;

            if (toSq & enemyPieces)
            {
                uint8_t enemyColor = !isBlack(chessBoard);
                uint8_t capturedPiece = getPieceFromSquare(toSq, enemyColor, chessBoard);
                moveFlags |= capturedPiece << captureFlagPostion;   
                if (toSq & promotionLine)
                {
                    generatePawnPromotionMoves(fromSq, toSq, moveFlags, moveList);
                }else
                {
                    addMove(fromSq, toSq, moveFlags, moveList, calculateCaptureMoveScore(pawn, capturedPiece));
                }
                 
            }

            if ((chessBoard->enPassantSq & toSq) && (chessBoard->enPassantSq & enpassantLine))
            {
                moveFlags |= (pawn << captureFlagPostion) | (1 << enPassantFlagPosition);
                addMove(fromSq, toSq, moveFlags, moveList, calculateCaptureMoveScore(pawn, pawn));
            }
            
            pawnAttacks &= pawnAttacks - 1;
        }

        pawnPositions &= pawnPositions - 1;
    }
}

void generateRookMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t rookPositions = chessBoard->whiteRooks;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        rookPositions = chessBoard->blackRooks;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    while (rookPositions != 0)
    {
        uint64_t fromSq = rookPositions & -rookPositions;
        uint64_t rookAttacks = getRookAttackPattern(getSqInd(fromSq), chessBoard->allPieces, attackTables);
        rookAttacks &= ~friendlyPieces;

        while (rookAttacks != 0)
        {
            uint16_t moveFlags = rook << pieceFlagPosition;
            uint64_t toSq = rookAttacks & -rookAttacks;
            if (toSq & enemyPieces)
            {
                uint8_t enemyColor = !isBlack(chessBoard);
                uint8_t capturedPiece = getPieceFromSquare(toSq, enemyColor, chessBoard);
                moveFlags |= capturedPiece << captureFlagPostion;
                addMove(fromSq, toSq, moveFlags, moveList, calculateCaptureMoveScore(rook, capturedPiece));
            }else
            {
                addMove(fromSq, toSq, moveFlags, moveList, 0);   
            } 
            
            rookAttacks &= rookAttacks - 1;
        }

        rookPositions &= rookPositions - 1;
    }
}

void generateCastleMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint16_t moveFlags = king << pieceFlagPosition;
    moveFlags |= castleMask;
    if (isBlack(chessBoard))
    {
        if (canBlackShortCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & f8) && !(chessBoard->allPieces & g8) && 
                !isSquareAttacked(getSqInd(e8), chessBoard, attackTables, 1) && 
                !isSquareAttacked(getSqInd(f8), chessBoard, attackTables, 1) && 
                !isSquareAttacked(getSqInd(g8), chessBoard, attackTables, 1))
            {
                addMove(e8, g8, moveFlags, moveList, 0);
            }
                
        }

        if (canBlackLongCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & b8) && !(chessBoard->allPieces & c8) && !(chessBoard->allPieces & d8) && 
                !isSquareAttacked(getSqInd(e8), chessBoard, attackTables, 1) && 
                !isSquareAttacked(getSqInd(c8), chessBoard, attackTables, 1) &&  
                !isSquareAttacked(getSqInd(d8), chessBoard, attackTables, 1)) 
            {
                addMove(e8, c8, moveFlags, moveList, 0);
            }    
        }
    }else
    {
        if (canWhiteShortCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & f1) && !(chessBoard->allPieces & g1) && 
                !isSquareAttacked(getSqInd(e1), chessBoard, attackTables, 0) && 
                !isSquareAttacked(getSqInd(f1), chessBoard, attackTables, 0) && 
                !isSquareAttacked(getSqInd(g1), chessBoard, attackTables, 0))
            {
                addMove(e1, g1, moveFlags, moveList, 0);
            }    
        }

        if (canWhiteLongCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & b1) && !(chessBoard->allPieces & c1) && !(chessBoard->allPieces & d1) && 
                !isSquareAttacked(getSqInd(e1), chessBoard, attackTables, 0) && 
                !isSquareAttacked(getSqInd(c1), chessBoard, attackTables, 0) &&  
                !isSquareAttacked(getSqInd(d1), chessBoard, attackTables, 0)) 
            {
                addMove(e1, c1, moveFlags, moveList, 0);
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

