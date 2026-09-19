#include <stdio.h>

#include "ChessBoard.h"
#include "Utils.h"
#include "TranspositionTables.h"
#include "AttackTables.h"

void showPosition(const ChessBoard* chessBoard)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        printf("%d  ", rank + 1);

        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;
            uint64_t mask = 1ULL << square;

            char piece = '.';

            if (chessBoard->whitePawns & mask) piece = 'P';
            else if (chessBoard->whiteKnights & mask) piece = 'N';
            else if (chessBoard->whiteBishops & mask) piece = 'B';
            else if (chessBoard->whiteRooks & mask) piece = 'R';
            else if (chessBoard->whiteQueens & mask) piece = 'Q';
            else if (chessBoard->whiteKing & mask) piece = 'K';

            else if (chessBoard->blackPawns & mask) piece = 'p';
            else if (chessBoard->blackKnights & mask) piece = 'n';
            else if (chessBoard->blackBishops & mask) piece = 'b';
            else if (chessBoard->blackRooks & mask) piece = 'r';
            else if (chessBoard->blackQueens & mask) piece = 'q';
            else if (chessBoard->blackKing & mask) piece = 'k';

            printf("%c ", piece);
        }

        printf("\n");
    }

    printf("   a b c d e f g h\n\n");
}

uint8_t hasCastled(ChessBoard* chessBoard, int isBlack)
{
    int isCastled = chessBoard->flags & hasWhiteCastledMask;

    if (isBlack)
    {
        isCastled = chessBoard->flags & hasBlackCastledMask;
    }
    
    return isCastled;
}

ChessBoard* initChessBoard()
{
    ChessBoard* chessBoard = malloc(sizeof(ChessBoard));

    chessBoard->whitePawns = 0;
    chessBoard->whiteKnights = 0;
    chessBoard->whiteBishops = 0;
    chessBoard->whiteRooks = 0;
    chessBoard->whiteQueens = 0;
    chessBoard->whiteKing = 0;

    chessBoard->blackPawns = 0;
    chessBoard->blackKnights = 0;
    chessBoard->blackBishops = 0;
    chessBoard->blackRooks = 0;
    chessBoard->blackQueens = 0;
    chessBoard->blackKing = 0;

    chessBoard->blackPieces = 0;
    chessBoard->whitePieces = 0;
    chessBoard->allPieces = 0;
    chessBoard->enPassantSq = 0;
    chessBoard->flags = 0;

    chessBoard->history.size = 0;
    chessBoard->moveDataStack.size = 0;
    
    return chessBoard;
}

void initStartingPosition(ChessBoard *chessBoard, TranspositionTableHashes* hashes)
{
    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b11111111ULL << 8  |
                             0b00000000ULL;

    chessBoard->whiteKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b01000010ULL;

    chessBoard->whiteBishops = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00100100ULL;

    chessBoard->whiteRooks = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b10000001ULL;

    chessBoard->whiteQueens = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00001000ULL;

    chessBoard->whiteKing = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00010000ULL;

    chessBoard->blackPawns = 0b00000000ULL << 56 |
                             0b11111111ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackKnights = 0b01000010ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->blackBishops = 0b00100100ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->blackRooks = 0b10000001ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackQueens = 0b00001000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000000ULL;

    chessBoard->blackKing = 0b00010000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00000000ULL;

    chessBoard->blackPieces = 0b11111111ULL << 56 |
                              0b11111111ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000000ULL;

    chessBoard->whitePieces = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b11111111ULL << 8  |
                              0b11111111ULL;

    chessBoard->allPieces = 0b11111111ULL << 56 |
                            0b11111111ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b11111111ULL << 8  |
                            0b11111111ULL;

    chessBoard->positionHash = 0;

    for (int sq = 8; sq < 16; sq++)
    {
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][sq];
    }

    for (int sq = 48; sq < 56; sq++)
    {
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][sq];
    }

    chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][0];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][7];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][56];
    chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][63];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][1];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][6];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][57];
    chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][62];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][2];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][5];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][58];
    chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][61];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][3];

    chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][60];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteKingHash][4];

    chessBoard->positionHash ^= hashes->pieceHashes[blackKingHash][59];

    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];

    chessBoard->enPassantSq = 0;
    chessBoard->flags = whiteShortCastleMask | whiteLongCastleMask | blackShortCastleMask | blackLongCastleMask;
    
    chessBoard->history.size = 0;
    chessBoard->history.lastIrreversableIndex[0] = 0;

    chessBoard->moveDataStack.size = 0;
}

uint8_t canWhiteShortCastle(ChessBoard *chessBoard)
{
    return chessBoard->flags & whiteShortCastleMask;
}

uint8_t canWhiteLongCastle(ChessBoard *chessBoard)
{
    return chessBoard->flags & whiteLongCastleMask;
}

uint8_t canBlackShortCastle(ChessBoard *chessBoard)
{
    return chessBoard->flags & blackShortCastleMask;
}

uint8_t canBlackLongCastle(ChessBoard *chessBoard)
{
    return chessBoard->flags & blackLongCastleMask;
}

uint8_t isBlack(ChessBoard *chessBoard)
{
    return chessBoard->flags & colorMask;
}

uint8_t getPieceFromSquare(uint64_t sq, uint8_t isBlack, ChessBoard *chessBoard)
{
    uint64_t pawnsSq = chessBoard->whitePawns;
    uint64_t knightsSq = chessBoard->whiteKnights; 
    uint64_t bishopsSq = chessBoard->whiteBishops; 
    uint64_t rooksSq = chessBoard->whiteRooks; 
    uint64_t queensSq = chessBoard->whiteQueens;
    uint64_t kingSq = chessBoard->whiteKing;
    
    if (isBlack)
    {
        pawnsSq = chessBoard->blackPawns;
        knightsSq = chessBoard->blackKnights; 
        bishopsSq = chessBoard->blackBishops; 
        rooksSq = chessBoard->blackRooks; 
        queensSq = chessBoard->blackQueens;
        kingSq = chessBoard->blackKing;
    }

    if (pawnsSq & sq)
    {
        return pawn;
    }
    
    if (knightsSq & sq)
    {
        return knight;
    }

    if (bishopsSq & sq)
    {
        return bishop;
    }

    if (rooksSq & sq)
    {
        return rook;
    }

    if (queensSq & sq)
    {
        return queen;
    }

    if (kingSq & sq)
    {
        return king;
    }
    
    return 0;
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

int isSquareAttacked(uint8_t sqInd, ChessBoard *chessBoard, AttackTables *attackTables, int isAttackedByWhite)
{
    
    uint64_t enemyKnights = chessBoard->blackKnights;
    uint64_t enemyBishops = chessBoard->blackBishops;
    uint64_t enemyRooks = chessBoard->blackRooks;
    uint64_t enemyQueens = chessBoard->blackQueens;
    uint64_t enemyPawns = chessBoard->blackPawns;
    uint64_t enemyKing = chessBoard->blackKing;
    uint64_t *friendlyPawnAttacks = attackTables->whitePanwsAttacks;
    
    if (isAttackedByWhite)
    {
        enemyKnights = chessBoard->whiteKnights;
        enemyBishops = chessBoard->whiteBishops;
        enemyRooks = chessBoard->whiteRooks;
        enemyQueens = chessBoard->whiteQueens;
        enemyPawns = chessBoard->whitePawns;
        enemyKing = chessBoard->whiteKing;
        friendlyPawnAttacks = attackTables->blackPanwsAttacks;

    }
    
    if (attackTables->knightAttacks[sqInd] & enemyKnights)
    {
        return 1;
    }

    if (attackTables->kingAttacks[sqInd] & enemyKing)
    {
        return 1;
    }
    
    uint64_t bishopAndQueenAttacks = getBishopAttackPattern(sqInd, chessBoard->allPieces, attackTables);
    
    if ((bishopAndQueenAttacks & enemyBishops) || (bishopAndQueenAttacks & enemyQueens))
    {
        return 1;
    }
    
    uint64_t rookAndQueenAttacks = getRookAttackPattern(sqInd, chessBoard->allPieces, attackTables);
    
    if ((rookAndQueenAttacks & enemyRooks) || (rookAndQueenAttacks & enemyQueens))
    {
        return 1;
    }

    if (friendlyPawnAttacks[sqInd] & enemyPawns)
    {
        return 1;
    }

    return 0;
}

void addMoveData(ChessBoard *chessBoard)
{
    chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].enPassantSq = chessBoard->enPassantSq;
    chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].positionHash = chessBoard->positionHash;
    chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].boardFlags = chessBoard->flags;
    chessBoard->moveDataStack.size++;
}

void revertMoveData(ChessBoard *chessBoard)
{
    chessBoard->moveDataStack.size--;
    chessBoard->enPassantSq = chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].enPassantSq;
    chessBoard->positionHash = chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].positionHash;
    chessBoard->flags = chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].boardFlags;
}

void createPosition(char fileName[], ChessBoard *chessBoard)
{
    int squareIndex = 0;

    FILE *positionFile = fopen(fileName, "r");

    if (positionFile == NULL)
    {
        sendError("failed to open file");
    }

    while (!feof(positionFile))
    {
        char piece[3];
        char pieceName;

        fscanf(positionFile, "%s", piece);

        uint64_t square = 1ULL << squareIndex;
        pieceName = piece[1];

        if (piece[0] == 'W')
        {
            switch (pieceName)
            {
            case 'Q': chessBoard->whiteQueens |= square; break;
            case 'R': chessBoard->whiteRooks |= square; break;
            case 'N': chessBoard->whiteKnights |= square; break;
            case 'B': chessBoard->whiteBishops |= square; break;
            case 'P': chessBoard->whitePawns |= square; break;
            case 'K': chessBoard->whiteKing |= square; break;
            default: sendError("Wrong format in file");   
            }
            chessBoard->whitePieces |= square;
        } else if (piece[0] == 'B')
        {
            switch (pieceName)
            {
            case 'Q': chessBoard->blackQueens |= square; break;
            case 'R': chessBoard->blackRooks |= square; break;
            case 'N': chessBoard->blackKnights |= square; break;
            case 'B': chessBoard->blackBishops |= square; break;
            case 'P': chessBoard->blackPawns |= square; break;
            case 'K': chessBoard->blackKing |= square; break;
            default: sendError("Wrong format in file");   
            }
            chessBoard->blackPieces |= square;
        }
        squareIndex++;
    }
    chessBoard->allPieces = chessBoard->whitePieces | chessBoard->blackPieces;
}
