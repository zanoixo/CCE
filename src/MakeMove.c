#include "ChessBoard.h"
#include "Move.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"

static const uint8_t castleRightLookup[BOARD_SIZE] = {
    0b1101, 0b1111, 0b1111, 0b1111, 0b1100, 0b1111, 0b1111, 0b1110,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b0111, 0b1111, 0b1111, 0b1111, 0b0011, 0b1111, 0b1111, 0b1011
};

static const uint8_t doublePawnPushOffset[2] = {8, -8};

void makeGenericMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t friendlyPieces = isBlack(chessBoard);
    uint8_t enemyPieces = !friendlyPieces;

    uint8_t fromSq = getFromSq(move->move);
    uint8_t toSq = getToSq(move->move);

    uint64_t from = 1ULL << fromSq;
    uint64_t to = 1ULL << toSq;

    uint8_t movedPiece = chessBoard->pieceLookup[fromSq];
    uint8_t capturedPiece = chessBoard->pieceLookup[toSq];

    moveData->movedPiece = movedPiece;
    moveData->capturedPiece = capturedPiece;

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->pieceBoards[movedPiece] &= ~from;
    chessBoard->pieceBoards[movedPiece] |= to;
    chessBoard->positionHash ^= hashes->pieceHashes[movedPiece][fromSq];
    chessBoard->positionHash ^= hashes->pieceHashes[movedPiece][toSq];
    chessBoard->coloredBoards[friendlyPieces] &= ~from;
    chessBoard->coloredBoards[friendlyPieces] |= to;
    chessBoard->allPieces &= ~from;
    chessBoard->allPieces |= to;
    chessBoard->pieceLookup[fromSq] = empty;
    chessBoard->pieceLookup[toSq] = movedPiece;
    chessBoard->positionHash ^= hashes->pieceHashes[capturedPiece][toSq];
    chessBoard->pieceBoards[capturedPiece] &= ~to;
    chessBoard->coloredBoards[enemyPieces] &= ~to;
}

void makeKingMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t friendlyPieces = isBlack(chessBoard);
    uint8_t enemyPieces = !friendlyPieces;

    uint8_t fromSq = getFromSq(move->move);
    uint8_t toSq = getToSq(move->move);

    uint64_t from = 1ULL << fromSq;
    uint64_t to = 1ULL << toSq;

    uint8_t movedPiece = chessBoard->pieceLookup[fromSq];
    uint8_t capturedPiece = chessBoard->pieceLookup[toSq];

    moveData->movedPiece = movedPiece;
    moveData->capturedPiece = capturedPiece;

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->pieceBoards[movedPiece] &= ~from;
    chessBoard->pieceBoards[movedPiece] |= to;
    chessBoard->positionHash ^= hashes->pieceHashes[movedPiece][fromSq];
    chessBoard->positionHash ^= hashes->pieceHashes[movedPiece][toSq];
    chessBoard->coloredBoards[friendlyPieces] &= ~from;
    chessBoard->coloredBoards[friendlyPieces] |= to;
    chessBoard->allPieces &= ~from;
    chessBoard->allPieces |= to;
    chessBoard->pieceLookup[fromSq] = empty;
    chessBoard->pieceLookup[toSq] = movedPiece;
    chessBoard->positionHash ^= hashes->pieceHashes[capturedPiece][toSq];
    chessBoard->pieceBoards[capturedPiece] &= ~to;
    chessBoard->coloredBoards[enemyPieces] &= ~to;

    if (fromSq == e8Sq || fromSq == e1Sq)
    {
        switch (toSq)
        {
        case g8Sq:
            chessBoard->pieceBoards[blackRook] &= ~h8;
            chessBoard->pieceBoards[blackRook] |= f8;
            chessBoard->positionHash ^= hashes->pieceHashes[blackRook][h8Sq];
            chessBoard->positionHash ^= hashes->pieceHashes[blackRook][f8Sq];
            chessBoard->coloredBoards[black] &= ~h8;
            chessBoard->coloredBoards[black] |= f8;
            chessBoard->allPieces &= ~h8;
            chessBoard->allPieces |= f8;
            chessBoard->pieceLookup[h8Sq] = empty;
            chessBoard->pieceLookup[f8Sq] = blackRook;
            chessBoard->flags |= hasBlackCastledMask;
            break;
        case c8Sq:
            chessBoard->pieceBoards[blackRook] &= ~a8;
            chessBoard->pieceBoards[blackRook] |= d8;
            chessBoard->positionHash ^= hashes->pieceHashes[blackRook][a8Sq];
            chessBoard->positionHash ^= hashes->pieceHashes[blackRook][d8Sq];
            chessBoard->coloredBoards[black] &= ~a8;
            chessBoard->coloredBoards[black] |= d8;
            chessBoard->allPieces &= ~a8;
            chessBoard->allPieces |= d8;
            chessBoard->pieceLookup[a8Sq] = empty;
            chessBoard->pieceLookup[d8Sq] = blackRook;
            chessBoard->flags |= hasBlackCastledMask;
            break;
        case g1Sq:
            chessBoard->pieceBoards[whiteRook] &= ~h1;
            chessBoard->pieceBoards[whiteRook] |= f1;
            chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][h1Sq];
            chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][f1Sq];
            chessBoard->coloredBoards[white] &= ~h1;
            chessBoard->coloredBoards[white] |= f1;
            chessBoard->allPieces &= ~h1;
            chessBoard->allPieces |= f1;
            chessBoard->pieceLookup[h1Sq] = empty;
            chessBoard->pieceLookup[f1Sq] = whiteRook;
            chessBoard->flags |= hasWhiteCastledMask;
            break;
        case c1Sq:
            chessBoard->pieceBoards[whiteRook] &= ~a1;
            chessBoard->pieceBoards[whiteRook] |= d1;
            chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][a1Sq];
            chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][d1Sq];
            chessBoard->coloredBoards[white] &= ~a1;
            chessBoard->coloredBoards[white] |= d1;
            chessBoard->allPieces &= ~a1;
            chessBoard->allPieces |= d1;
            chessBoard->pieceLookup[a1Sq] = empty;
            chessBoard->pieceLookup[d1Sq] = whiteRook;
            chessBoard->flags |= hasWhiteCastledMask;
            break;
        default:
            break;
        }
    }
}

void makePawnMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t friendlyPieces = isBlack(chessBoard);
    uint8_t enemyPieces = !friendlyPieces;

    uint8_t fromSq = getFromSq(move->move);
    uint8_t toSq = getToSq(move->move);

    uint64_t from = 1ULL << fromSq;
    uint64_t to = 1ULL << toSq;

    uint8_t isEnPassant = (move->move & enPassantMask) != 0;
    uint8_t captureSq = toSq + isEnPassant * (16 * friendlyPieces - 8);
    uint64_t capturedBitboard = 1ULL << captureSq;

    uint8_t finalPiece = promotionFlagToPiece[getPromotionPiece(*move)] + GENERIC_PIECE_TYPES * friendlyPieces;

    uint8_t movedPiece = chessBoard->pieceLookup[fromSq];
    uint8_t capturedPiece = chessBoard->pieceLookup[captureSq];

    moveData->movedPiece = movedPiece;
    moveData->capturedPiece = capturedPiece;

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->pieceBoards[movedPiece] &= ~from;
    chessBoard->pieceBoards[finalPiece] |= to;
    chessBoard->positionHash ^= hashes->pieceHashes[movedPiece][fromSq];
    chessBoard->positionHash ^= hashes->pieceHashes[finalPiece][toSq];
    chessBoard->coloredBoards[friendlyPieces] &= ~from;
    chessBoard->coloredBoards[friendlyPieces] |= to;
    chessBoard->allPieces &= ~from;
    chessBoard->allPieces &= ~capturedBitboard;
    chessBoard->allPieces |= to;
    chessBoard->pieceLookup[fromSq] = empty;
    chessBoard->pieceLookup[captureSq] = empty;
    chessBoard->pieceLookup[toSq] = finalPiece;
    chessBoard->positionHash ^= hashes->pieceHashes[capturedPiece][captureSq];
    chessBoard->pieceBoards[capturedPiece] &= ~capturedBitboard;
    chessBoard->coloredBoards[enemyPieces] &= ~capturedBitboard;

    int sqMoved = (int)toSq - (int)fromSq;
    uint64_t isDoublePush = (sqMoved == 16) | (sqMoved == -16);
    chessBoard->enPassantSq = (1ULL << (toSq - doublePawnPushOffset[friendlyPieces])) * isDoublePush;
}

void makeMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t piece = chessBoard->pieceLookup[getFromSq(move->move)];

    MoveData* moveData = &chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size]; 

    addMoveData(chessBoard);
    
    hashEnPassant(chessBoard, hashes);

    chessBoard->enPassantSq = 0;

    switch (piece)
    {
        case whitePawn:
        case blackPawn:
            makePawnMove(chessBoard, move, hashes, moveData);
            break;
        case whiteKing:
        case blackKing:
            makeKingMove(chessBoard, move, hashes, moveData);
            break;
        default:
            makeGenericMove(chessBoard, move, hashes, moveData);
            break;
    }

    chessBoard->flags ^= colorMask;

    hashEnPassant(chessBoard, hashes);
    
    chessBoard->positionHash ^= hashes->colorHash;

    addMoveToHistory(chessBoard, moveData, piece);
}

void makeNullMove(ChessBoard* chessBoard, TranspositionTableHashes* hashes)
{
    addMoveData(chessBoard);
    chessBoard->flags ^= colorMask;
    chessBoard->positionHash ^= hashes->colorHash;
    hashEnPassant(chessBoard, hashes);
    chessBoard->enPassantSq = 0;
}