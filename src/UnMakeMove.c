#include "ChessBoard.h"
#include "Move.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"

void unMakeGenericMove(ChessBoard *chessBoard, uint16_t move, MoveData moveData)
{
    uint8_t friendlyPieces = isBlack(chessBoard);
    uint8_t enemyPieces = !friendlyPieces;

    uint8_t capturedPiece = moveData.capturedPiece;
    uint8_t movedPiece = moveData.movedPiece;

    uint8_t fromSq = getFromSq(move);
    uint8_t toSq = getToSq(move);

    uint64_t from = 1ULL << fromSq;
    uint64_t to = 1ULL << toSq;

    chessBoard->pieceBoards[movedPiece] &= ~to;
    chessBoard->pieceBoards[movedPiece] |= from;
    chessBoard->coloredBoards[friendlyPieces] &= ~to;
    chessBoard->coloredBoards[friendlyPieces] |= from;
    chessBoard->allPieces &= ~to;
    chessBoard->allPieces |= from;
    chessBoard->pieceLookup[toSq] = empty;
    chessBoard->pieceLookup[fromSq] = movedPiece;
    

    if (capturedPiece != empty)
    {
        chessBoard->pieceBoards[capturedPiece] |= to;
        chessBoard->pieceLookup[toSq] = capturedPiece;
        chessBoard->coloredBoards[enemyPieces] |= to;
        chessBoard->allPieces |= to;
    }
}

void unMakeKingMove(ChessBoard *chessBoard, uint16_t move, MoveData moveData)
{
    uint8_t friendlyPieces = isBlack(chessBoard);
    uint8_t enemyPieces = !friendlyPieces;

    uint8_t capturedPiece = moveData.capturedPiece;
    uint8_t movedPiece = moveData.movedPiece;

    uint8_t fromSq = getFromSq(move);
    uint8_t toSq = getToSq(move);

    uint64_t from = 1ULL << fromSq;
    uint64_t to = 1ULL << toSq;

    chessBoard->pieceBoards[movedPiece] &= ~to;
    chessBoard->pieceBoards[movedPiece] |= from;
    chessBoard->coloredBoards[friendlyPieces] &= ~to;
    chessBoard->coloredBoards[friendlyPieces] |= from;
    chessBoard->allPieces &= ~to;
    chessBoard->allPieces |= from;
    chessBoard->pieceLookup[toSq] = empty;
    chessBoard->pieceLookup[fromSq] = movedPiece;
    

    if (capturedPiece != empty)
    {
        chessBoard->pieceBoards[capturedPiece] |= to;
        chessBoard->pieceLookup[toSq] = capturedPiece;
        chessBoard->coloredBoards[enemyPieces] |= to;
        chessBoard->allPieces |= to;
    }

    if (fromSq == e8Sq || fromSq == e1Sq)
    {
        switch (toSq)
        {
        case g8Sq:
            chessBoard->pieceBoards[blackRook] &= ~f8;
            chessBoard->pieceBoards[blackRook] |= h8;
            chessBoard->coloredBoards[black] &= ~f8;
            chessBoard->coloredBoards[black] |= h8;
            chessBoard->allPieces &= ~f8;
            chessBoard->allPieces |= h8;
            chessBoard->pieceLookup[f8Sq] = empty;
            chessBoard->pieceLookup[h8Sq] = blackRook;
            break;
        case c8Sq:
            chessBoard->pieceBoards[blackRook] &= ~d8;
            chessBoard->pieceBoards[blackRook] |= a8;
            chessBoard->coloredBoards[black] &= ~d8;
            chessBoard->coloredBoards[black] |= a8;
            chessBoard->allPieces &= ~d8;
            chessBoard->allPieces |= a8;
            chessBoard->pieceLookup[d8Sq] = empty;
            chessBoard->pieceLookup[a8Sq] = blackRook;
            break;
        case g1Sq:
            chessBoard->pieceBoards[whiteRook] &= ~f1;
            chessBoard->pieceBoards[whiteRook] |= h1;
            chessBoard->coloredBoards[white] &= ~f1;
            chessBoard->coloredBoards[white] |= h1;
            chessBoard->allPieces &= ~f1;
            chessBoard->allPieces |= h1;
            chessBoard->pieceLookup[f1Sq] = empty;
            chessBoard->pieceLookup[h1Sq] = whiteRook;
            break;
        case c1Sq:
            chessBoard->pieceBoards[whiteRook] &= ~d1;
            chessBoard->pieceBoards[whiteRook] |= a1;
            chessBoard->coloredBoards[white] &= ~d1;
            chessBoard->coloredBoards[white] |= a1;
            chessBoard->allPieces &= ~d1;
            chessBoard->allPieces |= a1;
            chessBoard->pieceLookup[d1Sq] = empty;
            chessBoard->pieceLookup[a1Sq] = whiteRook;
            break;
        default:
            break;
        }
    }
}

void unMakePawnMove(ChessBoard *chessBoard, uint16_t move, MoveData moveData)
{
    uint8_t friendlyPieces = isBlack(chessBoard);
    uint8_t enemyPieces = !friendlyPieces;

    uint8_t capturedPiece = moveData.capturedPiece;
    uint8_t movedPiece = moveData.movedPiece;

    uint8_t fromSq = getFromSq(move);
    uint8_t toSq = getToSq(move);

    uint64_t from = 1ULL << fromSq;
    uint64_t to = 1ULL << toSq;

    uint8_t isEnPassant = (move & enPassantMask) != 0;
    uint8_t captureSq = toSq + isEnPassant * (16 * friendlyPieces - 8);
    uint64_t capturedBitboard = 1ULL << captureSq;

    uint8_t removedPiece = promotionFlagToPiece[getPromotionPiece(move)] + GENERIC_PIECE_TYPES * friendlyPieces;

    chessBoard->pieceBoards[removedPiece] &= ~to;
    chessBoard->pieceBoards[movedPiece] |= from;
    chessBoard->coloredBoards[friendlyPieces] &= ~to;
    chessBoard->coloredBoards[friendlyPieces] |= from;
    chessBoard->allPieces &= ~to;
    chessBoard->allPieces |= from;
    chessBoard->pieceLookup[toSq] = empty;
    chessBoard->pieceLookup[fromSq] = movedPiece;
    

    if (capturedPiece != empty)
    {
        chessBoard->pieceBoards[capturedPiece] |= capturedBitboard;
        chessBoard->pieceLookup[captureSq] = capturedPiece;
        chessBoard->coloredBoards[enemyPieces] |= capturedBitboard;
        chessBoard->allPieces |= capturedBitboard;
    }

}

void unMakeMove(ChessBoard* chessBoard, uint16_t move)
{
    MoveData moveData = revertMoveData(chessBoard);
    
    switch (moveData.movedPiece)
    {
        case whitePawn:
        case blackPawn:
            unMakePawnMove(chessBoard, move, moveData);
            break;
        case whiteKing:
        case blackKing:
            unMakeKingMove(chessBoard, move, moveData);
            break;
        default:
            unMakeGenericMove(chessBoard, move, moveData);
            break;
    }
    
    removeMovefromHistory(chessBoard);
}

void unMakeNullMove(ChessBoard* chessBoard)
{
    revertMoveData(chessBoard);
}