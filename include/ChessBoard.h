#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "MoveHistory.h"
#include "Utils.h"

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct AttackTables AttackTables;

typedef struct MoveData
{
    uint64_t enPassantSq;
    uint64_t positionHash;
    uint8_t movedPiece;
    uint8_t capturedPiece;
    uint8_t boardFlags;
    uint8_t castleRights;
}MoveData;

typedef struct MoveDataStack
{
    MoveData moveData[1024];
    int size;
}MoveDataStack;

typedef struct ChessBoard
{
    uint64_t pieceBoards[PIECE_TYPES + 1];
    uint64_t coloredBoards[COLORS];
    
    uint64_t allPieces;
    uint64_t enPassantSq;
    uint8_t flags;
    uint8_t castleRights;
    uint64_t positionHash;

    MoveHistory history;
    MoveDataStack moveDataStack;
    uint8_t pieceLookup[BOARD_SIZE];
}ChessBoard;

enum boardFlags
{
    colorMask            = 0b00000001,
    hasWhiteCastledMask  = 0b00000010,
    hasBlackCastledMask  = 0b00000100,
};

enum castleRights 
{
    whiteShortCastleMask = 0b00000001,
    whiteLongCastleMask  = 0b00000010,
    blackShortCastleMask = 0b00000100,
    blackLongCastleMask  = 0b00001000,
};

void showPosition(const ChessBoard* chessBoard);
ChessBoard* initChessBoard();
void createPosition(char fileName[], ChessBoard *chessBoard);
void initStartingPosition(ChessBoard *chessBoard, TranspositionTableHashes* hashes);
int hasNonPawnPieces(ChessBoard* chessBoard, int side);
int isSquareAttacked(uint8_t sqInd, ChessBoard *chessBoard, AttackTables *attackTables, int isAttackedByWhite);
void addMoveData(ChessBoard *chessBoard);
MoveData revertMoveData(ChessBoard *chessBoard);

static inline uint8_t canWhiteShortCastle(ChessBoard *chessBoard)
{
    return chessBoard->castleRights & whiteShortCastleMask;
}

static inline uint8_t canWhiteLongCastle(ChessBoard *chessBoard)
{
    return chessBoard->castleRights & whiteLongCastleMask;
}

static inline uint8_t canBlackShortCastle(ChessBoard *chessBoard)
{
    return chessBoard->castleRights & blackShortCastleMask;
}

static inline uint8_t canBlackLongCastle(ChessBoard *chessBoard)
{
    return chessBoard->castleRights & blackLongCastleMask;
}

static inline uint8_t isBlack(ChessBoard *chessBoard)
{
    return chessBoard->flags & colorMask;
}

static inline uint8_t hasCastled(ChessBoard* chessBoard, int isBlack)
{
    int isCastled = chessBoard->flags & hasWhiteCastledMask;

    if (isBlack)
    {
        isCastled = chessBoard->flags & hasBlackCastledMask;
    }
    
    return isCastled;
}