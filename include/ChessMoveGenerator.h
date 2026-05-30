#ifndef CHESS_MOVE_GENERATOR_H

#include "ChessBoard.h"

typedef struct MagicTableHash
{
    uint64_t mask;
    uint64_t magicNumber;
    int shift;

}MagicTableHash;

typedef struct BlockerAttackPattern
{
    uint64_t attackPattern;
    uint64_t blockerPattern;
}BlockerAttackPattern;

typedef struct AttackTables
{
    uint64_t whitePanwsAttacks[BOARD_SIZE];
    uint64_t blackPanwsAttacks[BOARD_SIZE];
    uint64_t knightAttacks[BOARD_SIZE];
    uint64_t kingAttacks[BOARD_SIZE];
    uint64_t* rookAttacks[BOARD_SIZE];
    MagicTableHash rookMagicHashTable[BOARD_SIZE];
    uint64_t* bishopAttacks[BOARD_SIZE];
    MagicTableHash bishopMagicHashTable[BOARD_SIZE];
    
}AttackTables;

enum PromotionPieces
{
    queenPromotion = 0,
    rookPromotion = 1,
    bishopPromotion = 2,
    knightPromotion = 3,
    numOfPromotionPieces = 4
};

enum MoveFlags
{
    promotionPieceMask         = 0b0000000011,
    capturePieceMask           = 0b0000011100,
    enPassantMask              = 0b0000100000,
    removeWhiteShortCastleFlag = 0b0001000000,
    removeWhiteLongCastleFlag  = 0b0010000000,
    removeBlackShortCastleFlag = 0b0100000000,
    removeBlackLongCastleFlag  = 0b1000000000
};

enum MoveFlagsPosition
{
    promotionFlagPosition = 0,
    captureFlagPostion = 2,
    enPassantFlagPosition = 5,
    removeWhiteShortCastleFlagPosition = 6,
    removeWhiteLongCastleFlagPosition = 7,
    removeBlackShortCastleFlagPosition = 8,
    removeBlackLongCastleFlagPosition = 9
};

typedef struct Move
{
    uint64_t from;
    uint64_t to;
    uint16_t flags;
}Move;

typedef struct MoveList
{
    Move* moves;
    int nextIndex;
}MoveList;


AttackTables* initAttackTables();
uint64_t getRookAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables);
uint64_t getBishopAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables);
uint64_t getQueenAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables);
void generateMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateKnightMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateKingMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateQueenMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateBishopMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateRookMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generatePawnMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateCastleMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);

#endif