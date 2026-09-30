#include <stdio.h>

#include "ChessBoard.h"
#include "Utils.h"
#include "TranspositionTables.h"
#include "AttackTables.h"

uint8_t startPos[64] = {
    whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, whiteBishop, whiteKnight, whiteRook,
    whitePawn, whitePawn,   whitePawn,   whitePawn,  whitePawn, whitePawn,   whitePawn,   whitePawn,
    empty,     empty,       empty,       empty,      empty,     empty,       empty,       empty,
    empty,     empty,       empty,       empty,      empty,     empty,       empty,       empty,
    empty,     empty,       empty,       empty,      empty,     empty,       empty,       empty,
    empty,     empty,       empty,       empty,      empty,     empty,       empty,       empty,
    blackPawn, blackPawn,   blackPawn,   blackPawn,  blackPawn, blackPawn,   blackPawn,   blackPawn,
    blackRook, blackKnight, blackBishop, blackQueen, blackKing, blackBishop, blackKnight, blackRook,
};

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

    for (int sq = 0; sq < BOARD_SIZE; sq++)
    {
        chessBoard->pieceLookup[sq] = empty;
    }
    
    
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
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][sq];
    }

    for (int sq = 48; sq < 56; sq++)
    {
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][sq];
    }

    chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][0];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][7];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackRook][56];
    chessBoard->positionHash ^= hashes->pieceHashes[blackRook][63];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][1];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][6];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][57];
    chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][62];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][2];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][5];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][58];
    chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][61];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][3];

    chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][60];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteKing][4];

    chessBoard->positionHash ^= hashes->pieceHashes[blackKing][59];

    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];

    chessBoard->enPassantSq = 0;
    chessBoard->flags = whiteShortCastleMask | whiteLongCastleMask | blackShortCastleMask | blackLongCastleMask;
    
    chessBoard->history.size = 0;
    chessBoard->history.lastIrreversableIndex[0] = 0;

    chessBoard->moveDataStack.size = 0;

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        chessBoard->pieceLookup[sqInd] = startPos[sqInd];
    }
    
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

uint8_t getPieceFromSquare(uint8_t sq, ChessBoard *chessBoard)
{
    return coloredPieceToGeneric(chessBoard->pieceLookup[sq]);
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

MoveData revertMoveData(ChessBoard *chessBoard)
{
    chessBoard->moveDataStack.size--;
    chessBoard->enPassantSq = chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].enPassantSq;
    chessBoard->positionHash = chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].positionHash;
    chessBoard->flags = chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size].boardFlags;

    return chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size];
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
        uint8_t sqInd = getSqInd(square);
        pieceName = piece[1];

        if (piece[0] == 'W')
        {
            switch (pieceName)
            {
            case 'Q': chessBoard->whiteQueens |= square; chessBoard->pieceLookup[sqInd] = whiteQueen; break;
            case 'R': chessBoard->whiteRooks |= square; chessBoard->pieceLookup[sqInd] = whiteRook; break;
            case 'N': chessBoard->whiteKnights |= square; chessBoard->pieceLookup[sqInd] = whiteKnight; break;
            case 'B': chessBoard->whiteBishops |= square; chessBoard->pieceLookup[sqInd] = whiteBishop; break;
            case 'P': chessBoard->whitePawns |= square; chessBoard->pieceLookup[sqInd] = whitePawn; break;
            case 'K': chessBoard->whiteKing |= square; chessBoard->pieceLookup[sqInd] = whiteKing; break;
            default: sendError("Wrong format in file");   
            }
            chessBoard->whitePieces |= square;
        } else if (piece[0] == 'B')
        {
            switch (pieceName)
            {
            case 'Q': chessBoard->blackQueens |= square; chessBoard->pieceLookup[sqInd] = blackQueen; break;
            case 'R': chessBoard->blackRooks |= square; chessBoard->pieceLookup[sqInd] = blackRook; break;
            case 'N': chessBoard->blackKnights |= square; chessBoard->pieceLookup[sqInd] = blackKnight; break;
            case 'B': chessBoard->blackBishops |= square; chessBoard->pieceLookup[sqInd] = blackBishop; break;
            case 'P': chessBoard->blackPawns |= square; chessBoard->pieceLookup[sqInd] = blackPawn; break;
            case 'K': chessBoard->blackKing |= square; chessBoard->pieceLookup[sqInd] = blackKing; break;
            default: sendError("Wrong format in file");   
            }
            chessBoard->blackPieces |= square;
        }
        squareIndex++;
    }
    chessBoard->allPieces = chessBoard->whitePieces | chessBoard->blackPieces;
}
