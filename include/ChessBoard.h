#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "MoveHistory.h"

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct AttackTables AttackTables;

typedef struct MoveData
{
    uint64_t enPassantSq;
    uint64_t positionHash;
    uint8_t boardFlags;
}MoveData;

typedef struct MoveDataStack
{
    MoveData moveData[1024];
    int size;
}MoveDataStack;

typedef struct ChessBoard
{
    uint64_t whitePawns;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whiteRooks;
    uint64_t whiteQueens;
    uint64_t whiteKing;

    uint64_t blackPawns;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackRooks;
    uint64_t blackQueens;
    uint64_t blackKing;
    
    uint64_t blackPieces;
    uint64_t whitePieces;
    uint64_t allPieces;
    uint64_t enPassantSq;
    uint8_t flags;
    uint64_t positionHash;

    MoveHistory history;
    MoveDataStack moveDataStack;
}ChessBoard;

enum boardFlags
{
    colorMask            = 0b00000001,
    whiteShortCastleMask = 0b00000010,
    whiteLongCastleMask  = 0b00000100,
    blackShortCastleMask = 0b00001000,
    blackLongCastleMask  = 0b00010000,
    hasWhiteCastledMask  = 0b00100000,
    hasBlackCastledMask  = 0b01000000,
};

void showPosition(const ChessBoard* chessBoard);
ChessBoard* initChessBoard();
void createPosition(char fileName[], ChessBoard *chessBoard);
void initStartingPosition(ChessBoard *chessBoard, TranspositionTableHashes* hashes);
uint8_t hasCastled(ChessBoard* chessBoard, int isBlack);
uint8_t canWhiteShortCastle(ChessBoard *chessBoard);
uint8_t canWhiteLongCastle(ChessBoard *chessBoard);
uint8_t canBlackShortCastle(ChessBoard *chessBoard);
uint8_t canBlackLongCastle(ChessBoard *chessBoard);
uint8_t isBlack(ChessBoard *chessBoard);
uint8_t getPieceFromSquare(uint64_t sq, uint8_t isBlack, ChessBoard *chessBoard);
int hasNonPawnPieces(ChessBoard* chessBoard, int side);
int isSquareAttacked(uint8_t sqInd, ChessBoard *chessBoard, AttackTables *attackTables, int isAttackedByWhite);
void addMoveData(ChessBoard *chessBoard);
void revertMoveData(ChessBoard *chessBoard);