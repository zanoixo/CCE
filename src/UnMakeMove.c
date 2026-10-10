#include "ChessBoard.h"
#include "Move.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"

void unMakeGenericMove(ChessBoard *chessBoard, Move *move, MoveData moveData)
{
    uint8_t friendlyPieces = isBlack(chessBoard);
    uint8_t enemyPieces = !friendlyPieces;

    uint8_t capturedPiece = moveData.capturedPiece;
    uint8_t movedPiece = moveData.movedPiece;

    uint8_t fromSq = getFromSq(move->move);
    uint8_t toSq = getToSq(move->move);

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

void unMakeKingMove(ChessBoard *chessBoard, Move *move, MoveData moveData)
{
    uint8_t friendlyPieces = isBlack(chessBoard);
    uint8_t enemyPieces = !friendlyPieces;

    uint8_t capturedPiece = moveData.capturedPiece;
    uint8_t movedPiece = moveData.movedPiece;

    uint8_t fromSq = getFromSq(move->move);
    uint8_t toSq = getToSq(move->move);

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

void unMakePawnMove(ChessBoard *chessBoard, Move *move, MoveData moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = moveData.capturedPiece;
    uint8_t promotion = getPromotionPiece(*move);
    
    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    uint64_t moveTo = to;
    uint8_t moveToSq = getSqInd(moveTo);

    if (isBlacksMove)
    {
        switch (promotion)
        {
            case knightPromotion:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->pieceBoards[blackKnight] &= ~to;
                break;
            case bishopPromotion:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->pieceBoards[blackBishop] &= ~to;
                break;
            case rookPromotion:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->pieceBoards[blackRook] &= ~to;
                break;
            case queenPromotion:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->pieceBoards[blackQueen] &= ~to;
                break;
            case 0:
                break;
        }

        chessBoard->pieceBoards[blackPawn] &= ~to;
        chessBoard->pieceBoards[blackPawn] |= from;
        chessBoard->coloredBoards[black] &= ~to;
        chessBoard->coloredBoards[black] |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = blackPawn;

        if (move->move & enPassantMask)
        {
            moveTo = to << 8;
            moveToSq = getSqInd(moveTo);
            chessBoard->allPieces |= moveTo;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] |= moveTo;
                chessBoard->coloredBoards[white] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whitePawn;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] |= moveTo;
                chessBoard->coloredBoards[white] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whiteKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] |= moveTo;
                chessBoard->coloredBoards[white] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whiteBishop;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] |= moveTo;
                chessBoard->coloredBoards[white] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whiteRook;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] |= moveTo;
                chessBoard->coloredBoards[white] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whiteQueen;
                break;
            case 0:
                break;
        }
    }
    else
    {
        switch (promotion)
        {
            case knightPromotion:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->pieceBoards[whiteKnight] &= ~to;
                break;
            case bishopPromotion:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->pieceBoards[whiteBishop] &= ~to;
                break;
            case rookPromotion:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->pieceBoards[whiteRook] &= ~to;
                break;
            case queenPromotion:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->pieceBoards[whiteQueen] &= ~to;
                break;
            case 0:
                break;
        }

        chessBoard->pieceBoards[whitePawn] &= ~to;
        chessBoard->pieceBoards[whitePawn] |= from;
        chessBoard->coloredBoards[white] &= ~to;
        chessBoard->coloredBoards[white] |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = whitePawn;

        if (move->move & enPassantMask)
        {
            moveTo = to >> 8;
            moveToSq = getSqInd(moveTo);
            chessBoard->allPieces |= moveTo;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] |= moveTo;
                chessBoard->coloredBoards[black] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackPawn;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] |= moveTo;
                chessBoard->coloredBoards[black] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] |= moveTo;
                chessBoard->coloredBoards[black] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackBishop;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] |= moveTo;
                chessBoard->coloredBoards[black] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackRook;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] |= moveTo;
                chessBoard->coloredBoards[black] |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackQueen;
                break;
            case 0:
                break;
        }
    }
}

void unMakeMove(ChessBoard* chessBoard, Move* move)
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