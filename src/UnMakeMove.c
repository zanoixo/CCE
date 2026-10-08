#include "ChessBoard.h"
#include "Move.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"

void unMakeKnightMove(ChessBoard *chessBoard, Move *move, MoveData moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = moveData.capturedPiece;

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackKnight] &= ~to;
        chessBoard->pieceBoards[blackKnight] |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = blackKnight;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whitePawn;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteBishop;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteRook;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteQueen;
                break;
            case 0:
                break;
        }
    }
    else
    {
        chessBoard->pieceBoards[whiteKnight] &= ~to;
        chessBoard->pieceBoards[whiteKnight] |= from;
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = whiteKnight;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackPawn;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackBishop;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackRook;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackQueen;
                break;
            case 0:
                break;
        }
    }
}

void unMakeBishopMove(ChessBoard *chessBoard, Move *move, MoveData moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = moveData.capturedPiece;

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackBishop] &= ~to;
        chessBoard->pieceBoards[blackBishop] |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = blackBishop;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whitePawn;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteBishop;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteRook;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteQueen;
                break;
            case 0:
                break;
        }
    }
    else
    {
        chessBoard->pieceBoards[whiteBishop] &= ~to;
        chessBoard->pieceBoards[whiteBishop] |= from;
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = whiteBishop;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackPawn;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackBishop;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackRook;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackQueen;
                break;
            case 0:
                break;
        }
    }
}

void unMakeRookMove(ChessBoard *chessBoard, Move *move, MoveData moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = moveData.capturedPiece;

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackRook] &= ~to;
        chessBoard->pieceBoards[blackRook] |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = blackRook;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whitePawn;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteBishop;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteRook;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteQueen;
                break;
            case 0:
                break;
        }
    }
    else
    {
        chessBoard->pieceBoards[whiteRook] &= ~to;
        chessBoard->pieceBoards[whiteRook] |= from;
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = whiteRook;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackPawn;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackBishop;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackRook;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackQueen;
                break;
            case 0:
                break;
        }
    }
}

void unMakeQueenMove(ChessBoard *chessBoard, Move *move, MoveData moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = moveData.capturedPiece;

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackQueen] &= ~to;
        chessBoard->pieceBoards[blackQueen] |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = blackQueen;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whitePawn;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteBishop;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteRook;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteQueen;
                break;
            case 0:
                break;
        }
    }
    else
    {
        chessBoard->pieceBoards[whiteQueen] &= ~to;
        chessBoard->pieceBoards[whiteQueen] |= from;
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = whiteQueen;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackPawn;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackBishop;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackRook;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackQueen;
                break;
            case 0:
                break;
        }
    }
}

void unMakeKingMove(ChessBoard *chessBoard, Move *move, MoveData moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = moveData.capturedPiece;

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackKing] &= ~to;
        chessBoard->pieceBoards[blackKing] |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = blackKing;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whitePawn;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteBishop;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteRook;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = whiteQueen;
                break;
            case 0:
                break;
        }

        if (from == e8)
        {
            if (to == g8)
            {
                chessBoard->pieceBoards[blackRook] &= ~f8;
                chessBoard->pieceBoards[blackRook] |= h8;
                chessBoard->blackPieces &= ~f8;
                chessBoard->blackPieces |= h8;
                chessBoard->allPieces &= ~f8;
                chessBoard->allPieces |= h8;
                chessBoard->pieceLookup[getSqInd(f8)] = empty;
                chessBoard->pieceLookup[getSqInd(h8)] = blackRook;
            }

            if (to == c8)
            {
                chessBoard->pieceBoards[blackRook] &= ~d8;
                chessBoard->pieceBoards[blackRook] |= a8;
                chessBoard->blackPieces &= ~d8;
                chessBoard->blackPieces |= a8;
                chessBoard->allPieces &= ~d8;
                chessBoard->allPieces |= a8;
                chessBoard->pieceLookup[getSqInd(d8)] = empty;
                chessBoard->pieceLookup[getSqInd(a8)] = blackRook;
            }
        }
    }
    else
    {
        chessBoard->pieceBoards[whiteKing] &= ~to;
        chessBoard->pieceBoards[whiteKing] |= from;
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;
        chessBoard->pieceLookup[toSq] = empty;
        chessBoard->pieceLookup[fromSq] = whiteKing;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackPawn;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackBishop;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackRook;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                chessBoard->pieceLookup[toSq] = blackQueen;
                break;
            case 0:
                break;
        }

        if (from == e1)
        {
            if (to == g1)
            {
                chessBoard->pieceBoards[whiteRook] &= ~f1;
                chessBoard->pieceBoards[whiteRook] |= h1;
                chessBoard->whitePieces &= ~f1;
                chessBoard->whitePieces |= h1;
                chessBoard->allPieces &= ~f1;
                chessBoard->allPieces |= h1;
                chessBoard->pieceLookup[getSqInd(f1)] = empty;
                chessBoard->pieceLookup[getSqInd(h1)] = whiteRook;
            }

            if (to == c1)
            {
                chessBoard->pieceBoards[whiteRook] &= ~d1;
                chessBoard->pieceBoards[whiteRook] |= a1;
                chessBoard->whitePieces &= ~d1;
                chessBoard->whitePieces |= a1;
                chessBoard->allPieces &= ~d1;
                chessBoard->allPieces |= a1;
                chessBoard->pieceLookup[getSqInd(d1)] = empty;
                chessBoard->pieceLookup[getSqInd(a1)] = whiteRook;
            }
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
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
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
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whitePawn;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] |= moveTo;
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whiteKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] |= moveTo;
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whiteBishop;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] |= moveTo;
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = whiteRook;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] |= moveTo;
                chessBoard->whitePieces |= moveTo;
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
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
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
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackPawn;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] |= moveTo;
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackKnight;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] |= moveTo;
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackBishop;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] |= moveTo;
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                chessBoard->pieceLookup[moveToSq] = blackRook;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] |= moveTo;
                chessBoard->blackPieces |= moveTo;
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

    uint8_t piece;
    
    if (getPromotionPiece(*move))
    {
        piece = pawn;
    }
    else
    {
        piece = getPieceFromSquare(getToSq(move->move), chessBoard);
    }


    switch (piece)
    {
        case pawn:
            unMakePawnMove(chessBoard, move, moveData);
            break;
        case knight:
            unMakeKnightMove(chessBoard, move, moveData);
            break;
        case bishop:
            unMakeBishopMove(chessBoard, move, moveData);
            break;
        case rook:
            unMakeRookMove(chessBoard, move, moveData);
            break;
        case queen:
            unMakeQueenMove(chessBoard, move, moveData);
            break;
        case king:
            unMakeKingMove(chessBoard, move, moveData);
            break;
    }
    
    removeMovefromHistory(chessBoard);
}

void unMakeNullMove(ChessBoard* chessBoard)
{
    revertMoveData(chessBoard);
}