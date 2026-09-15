#include "Eval.h"

#include "Utils.h"
#include "ChessBoard.h"
#include "AttackTables.h"
#include "ChessBitboards.h"

uint64_t passedPawnMasks[64];
uint64_t isolatedPawnMasks[64];

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

int evaluateMobility(ChessBoard* chessBoard, AttackTables* attackTables, int isBlack)
{
    int mobility = 0;
    int piecePositioning = 0;

    uint64_t pawns = chessBoard->whitePawns;
    uint64_t knights = chessBoard->whiteKnights;
    uint64_t bishops = chessBoard->whiteBishops;
    uint64_t rooks = chessBoard->whiteRooks;
    uint64_t queens = chessBoard->whiteQueens;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPawns = chessBoard->blackPawns;
    uint64_t enemyKing = chessBoard->blackKing;

    if (isBlack)
    {
        pawns = chessBoard->blackPawns;
        knights = chessBoard->blackKnights;
        bishops = chessBoard->blackBishops;
        rooks = chessBoard->blackRooks;
        queens = chessBoard->blackQueens;
        friendlyPieces = chessBoard->blackPieces;
        enemyPawns = chessBoard->whitePawns;
        enemyKing = chessBoard->whiteKing;
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

        uint64_t rookFile = files[sq % 8];

        if (!(pawns & rookFile))
        {
            if (!(enemyPawns & rookFile))
            {
                piecePositioning += ROOK_OPEN_FILE_VALUE;
            }
            else
            {
                piecePositioning += ROOK_SEMIOPEN_FILE_VALUE;
            }

            if (enemyKing & rookFile)
            {
                piecePositioning += ROOK_ON_KING_FILE_VALUE;
            }
            
        }
        
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

int evaluateKingSafety(ChessBoard* chessBoard, int isBlack, int material)
{
    int score = 0;

    if (isBlack)
    {
        int pawnsValue = countPieces(chessBoard->whitePawns) * PAWN_VALUE;

        if ((material - pawnsValue) < KING_SAFETY_CUTOFF)
        {
            return 0;
        }
        

        if (hasCastled(chessBoard, isBlack) && ((blackKingSideCastleSquares | blackQueenSideCastleSquares) & chessBoard->blackKing))
        {
            score += KING_CASTLED_VALUE;
        }
        
        if (chessBoard->blackKing & blackKingSideCastleSquares)
        {
            score += countPieces(chessBoard->blackPawns & blackKingSideInnerPawnShield) * INNER_PAWN_WALL_VALUE;
            score += countPieces(chessBoard->blackPawns & blackKingSideOuterPawnShield) * OUTER_PAWN_WALL_VALUE;

            uint64_t blackKingSideShield = blackKingSideInnerPawnShield | blackKingSideOuterPawnShield;

            if ((chessBoard->blackPawns & blackKingSideShield & hFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->blackPawns & hFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }

            if ((chessBoard->blackPawns & blackKingSideShield & gFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->blackPawns & gFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }

            if ((chessBoard->blackPawns & blackKingSideShield & fFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->blackPawns & fFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }
        }
        else if(chessBoard->blackKing & blackQueenSideCastleSquares)
        {
            score += countPieces(chessBoard->blackPawns & blackQueenSideInnerPawnShield) * INNER_PAWN_WALL_VALUE;
            score += countPieces(chessBoard->blackPawns & blackQueenSideOuterPawnShield) * OUTER_PAWN_WALL_VALUE;

            uint64_t blackQueenSideShield = blackQueenSideInnerPawnShield | blackQueenSideOuterPawnShield;

            if ((chessBoard->blackPawns & blackQueenSideShield & bFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->blackPawns & bFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }

            if ((chessBoard->blackPawns & blackQueenSideShield & cFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->blackPawns & cFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }

            if ((chessBoard->blackPawns & blackQueenSideShield & dFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->blackPawns & dFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }
            
        }
        
    }
    else
    {
        int pawnsValue = countPieces(chessBoard->blackPawns) * PAWN_VALUE;

        if ((material - pawnsValue) < KING_SAFETY_CUTOFF)
        {
            return 0;
        }

        if (hasCastled(chessBoard, isBlack) && ((whiteKingSideCastleSquares | whiteQueenSideCastleSquares) & chessBoard->whiteKing))
        {
            score += KING_CASTLED_VALUE;
        }

        if (chessBoard->whiteKing & whiteKingSideCastleSquares)
        {
            score += countPieces(chessBoard->whitePawns & whiteKingSideInnerPawnShield) * INNER_PAWN_WALL_VALUE;
            score += countPieces(chessBoard->whitePawns & whiteKingSideOuterPawnShield) * OUTER_PAWN_WALL_VALUE;

            uint64_t whiteKingSideShield = whiteKingSideInnerPawnShield | whiteKingSideOuterPawnShield;

            if ((chessBoard->whitePawns & whiteKingSideShield & hFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->whitePawns & hFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }

            if ((chessBoard->whitePawns & whiteKingSideShield & gFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->whitePawns & gFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }

            if ((chessBoard->whitePawns & whiteKingSideShield & fFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->whitePawns & fFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }
        }
        else if(chessBoard->whiteKing & whiteQueenSideCastleSquares)
        {
            score += countPieces(chessBoard->whitePawns & whiteQueenSideInnerPawnShield) * INNER_PAWN_WALL_VALUE;
            score += countPieces(chessBoard->whitePawns & whiteQueenSideOuterPawnShield) * OUTER_PAWN_WALL_VALUE;
            
            uint64_t whiteQueenSideShield = whiteQueenSideInnerPawnShield | whiteQueenSideOuterPawnShield;

            if ((chessBoard->whitePawns & whiteQueenSideShield & bFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->whitePawns & bFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }

            if ((chessBoard->whitePawns & whiteQueenSideShield & cFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->whitePawns & cFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }

            if ((chessBoard->whitePawns & whiteQueenSideShield & dFile) == 0)
            {
                score -= PAWN_WALL_MISSING_PENALTY;

                if ((chessBoard->whitePawns & dFile) == 0)
                {
                    score -= OPEN_FILE_IN_WALL;
                }
                
            }
        }
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


    int whiteMaterial = evaluateMaterial(chessBoard, white);
    int blackMaterial = evaluateMaterial(chessBoard, black);
    
    score += whiteMaterial;
    score += evaluateMobility(chessBoard, attackTables, white);
    score += evaluatePawnPositioning(chessBoard, white);
    score += evaluateBishopPair(chessBoard, white);
    score += evaluateKingSafety(chessBoard, white, blackMaterial);


    score -= blackMaterial;
    score -= evaluateMobility(chessBoard, attackTables, black);
    score -= evaluatePawnPositioning(chessBoard, black);
    score -= evaluateBishopPair(chessBoard, black);
    score -= evaluateKingSafety(chessBoard, black, whiteMaterial);

    return score;
}

int getPieceScore(uint8_t piece)
{
    switch (piece)
    {
        case pawn:
            return PAWN_VALUE; 
        case knight:
            return KNIGHT_VALUE; 
        case bishop:
            return BISHOP_VALUE; 
        case rook:
            return ROOK_VALUE;
        case queen:
            return QUEEN_VALUE;  
        case king:
            return KING_VALUE; 
    }
    return 0;
}