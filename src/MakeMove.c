#include "ChessBoard.h"
#include "Move.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"

uint8_t castleRightLookup[BOARD_SIZE] = {
    0b1101, 0b1111, 0b1111, 0b1111, 0b1100, 0b1111, 0b1111, 0b1110,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111,
    0b0111, 0b1111, 0b1111, 0b1111, 0b0011, 0b1111, 0b1111, 0b1011
};

void makeKnightMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    uint8_t capture = getPieceFromSquare(toSq, chessBoard);

    moveData->capturedPiece = capture;

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackKnight] &= ~from;
        chessBoard->pieceBoards[blackKnight] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
        chessBoard->coloredBoards[black] &= ~from;
        chessBoard->coloredBoards[black] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackKnight;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {   

        chessBoard->pieceBoards[whiteKnight] &= ~from;
        chessBoard->pieceBoards[whiteKnight] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
        chessBoard->coloredBoards[white] &= ~from;
        chessBoard->coloredBoards[white] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteKnight;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case 0:
                break;
        }
    }
}

void makeBishopMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    uint8_t capture = getPieceFromSquare(toSq, chessBoard);

    moveData->capturedPiece = capture;

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackBishop] &= ~from;
        chessBoard->pieceBoards[blackBishop] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
        chessBoard->coloredBoards[black] &= ~from;
        chessBoard->coloredBoards[black] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackBishop;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->pieceBoards[whiteBishop] &= ~from;
        chessBoard->pieceBoards[whiteBishop] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
        chessBoard->coloredBoards[white] &= ~from;
        chessBoard->coloredBoards[white] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteBishop;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case 0:
                break;
        }
    }
}

void makeRookMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    uint8_t capture = getPieceFromSquare(toSq, chessBoard);

    moveData->capturedPiece = capture;

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackRook] &= ~from;
        chessBoard->pieceBoards[blackRook] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackRook][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
        chessBoard->coloredBoards[black] &= ~from;
        chessBoard->coloredBoards[black] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackRook;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->pieceBoards[whiteRook] &= ~from;
        chessBoard->pieceBoards[whiteRook] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
        chessBoard->coloredBoards[white] &= ~from;
        chessBoard->coloredBoards[white] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteRook;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case 0:
                break;
        }
    }
}

void makeQueenMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    uint8_t capturedPiece = getPieceFromSquare(toSq, chessBoard);

    moveData->capturedPiece = capturedPiece;

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];

    if (isBlacksMove)
    {
        //capturedPiece = chessBoard->pieceLookup[toSq];

        chessBoard->pieceBoards[blackQueen] &= ~from;
        chessBoard->pieceBoards[blackQueen] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
        chessBoard->coloredBoards[black] &= ~from;
        chessBoard->coloredBoards[black] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackQueen;
        //chessBoard->pieceBoards[capturedPiece] &= ~to;
        //chessBoard->positionHash ^= hashes->pieceHashes[capturedPiece][toSq];

        switch (capturedPiece)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->pieceBoards[whiteQueen] &= ~from;
        chessBoard->pieceBoards[whiteQueen] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
        chessBoard->coloredBoards[white] &= ~from;
        chessBoard->coloredBoards[white] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteQueen;

        switch (capturedPiece)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case 0:
                break;
        }
    }
}

void makeKingMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    uint8_t capture = getPieceFromSquare(toSq, chessBoard);

    moveData->capturedPiece = capture;

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackKing] &= ~from;
        chessBoard->pieceBoards[blackKing] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKing][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKing][toSq];
        chessBoard->coloredBoards[black] &= ~from;
        chessBoard->coloredBoards[black] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackKing;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->coloredBoards[white] &= ~to;
                break;
            case 0:
                break;
        }

        if (from == e8)
        {
            if (to == g8)
            {
                chessBoard->pieceBoards[blackRook] &= ~ h8;
                chessBoard->pieceBoards[blackRook] |= f8;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][getSqInd(h8)];
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][getSqInd(f8)];
                chessBoard->coloredBoards[black] &= ~h8;
                chessBoard->coloredBoards[black] |= f8;
                chessBoard->allPieces &= ~h8;
                chessBoard->allPieces |= f8;
                chessBoard->pieceLookup[getSqInd(h8)] = empty;
                chessBoard->pieceLookup[getSqInd(f8)] = blackRook;
                chessBoard->flags |= hasBlackCastledMask;
            }

            if (to == c8)
            {
                chessBoard->pieceBoards[blackRook] &= ~ a8;
                chessBoard->pieceBoards[blackRook] |= d8;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][getSqInd(a8)];
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][getSqInd(d8)];
                chessBoard->coloredBoards[black] &= ~a8;
                chessBoard->coloredBoards[black] |= d8;
                chessBoard->allPieces &= ~a8;
                chessBoard->allPieces |= d8;
                chessBoard->pieceLookup[getSqInd(a8)] = empty;
                chessBoard->pieceLookup[getSqInd(d8)] = blackRook;
                chessBoard->flags |= hasBlackCastledMask;
            }
        }
        
    }else
    {
        chessBoard->pieceBoards[whiteKing] &= ~from;
        chessBoard->pieceBoards[whiteKing] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKing][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKing][toSq];
        chessBoard->coloredBoards[white] &= ~from;
        chessBoard->coloredBoards[white] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteKing;

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->coloredBoards[black] &= ~to;
                break;
            case 0:
                break;
        }

        if (from == e1)
        {
            if (to == g1)
            {
                chessBoard->pieceBoards[whiteRook] &= ~ h1;
                chessBoard->pieceBoards[whiteRook] |= f1;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][getSqInd(h1)];
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][getSqInd(f1)];
                chessBoard->coloredBoards[white] &= ~h1;
                chessBoard->coloredBoards[white] |= f1;
                chessBoard->allPieces &= ~h1;
                chessBoard->allPieces |= f1;
                chessBoard->pieceLookup[getSqInd(h1)] = empty;
                chessBoard->pieceLookup[getSqInd(f1)] = whiteRook;
                chessBoard->flags |= hasWhiteCastledMask;
            }

            if (to == c1)
            {
                chessBoard->pieceBoards[whiteRook] &= ~ a1;
                chessBoard->pieceBoards[whiteRook] |= d1;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][getSqInd(a1)];
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][getSqInd(d1)];
                chessBoard->coloredBoards[white] &= ~a1;
                chessBoard->coloredBoards[white] |= d1;
                chessBoard->allPieces &= ~a1;
                chessBoard->allPieces |= d1;
                chessBoard->pieceLookup[getSqInd(a1)] = empty;
                chessBoard->pieceLookup[getSqInd(d1)] = whiteRook;
                chessBoard->flags |= hasWhiteCastledMask;
            }
        }
    }
}

void makePawnMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes, MoveData* moveData)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t promotion = getPromotionPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);
    
    uint64_t moveTo = to;

    uint8_t moveToSq = getSqInd(moveTo);

    uint8_t capture = getPieceFromSquare(toSq, chessBoard);

    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];
    chessBoard->castleRights &= castleRightLookup[fromSq] & castleRightLookup[toSq];
    chessBoard->positionHash ^= hashes->castellingHashes[chessBoard->castleRights];

    if (isBlacksMove)
    {
        chessBoard->pieceBoards[blackPawn] &= ~from;
        chessBoard->pieceBoards[blackPawn] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
        chessBoard->coloredBoards[black] &= ~from;
        chessBoard->coloredBoards[black] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackPawn;

        if (move->move & enPassantMask)
        {
            moveTo = to << 8;
            moveToSq = getSqInd(moveTo);
            chessBoard->allPieces &= ~moveTo;
            chessBoard->pieceLookup[moveToSq] = empty;
            capture = pawn;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[whitePawn] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][moveToSq];
                chessBoard->coloredBoards[white] &= ~moveTo;
                break;
            case knight:
                chessBoard->pieceBoards[whiteKnight] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][moveToSq];
                chessBoard->coloredBoards[white] &= ~moveTo;
                break;
            case bishop:
                chessBoard->pieceBoards[whiteBishop] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][moveToSq];
                chessBoard->coloredBoards[white] &= ~moveTo;
                break;
            case rook:
                chessBoard->pieceBoards[whiteRook] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][moveToSq];
                chessBoard->coloredBoards[white] &= ~moveTo;
                break;
            case queen:
                chessBoard->pieceBoards[whiteQueen] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][moveToSq];
                chessBoard->coloredBoards[white] &= ~moveTo;
                break;
            case 0:
                break;
        }

        switch (promotion)
        {
            case knightPromotion:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->pieceBoards[blackKnight] |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->pieceLookup[toSq] = blackKnight;
                break;
            case bishopPromotion:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->pieceBoards[blackBishop] |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->pieceLookup[toSq] = blackBishop;
                break;
            case rookPromotion:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->pieceBoards[blackRook] |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->pieceLookup[toSq] = blackRook;
                break;
            case queenPromotion:
                chessBoard->pieceBoards[blackPawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->pieceBoards[blackQueen] |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->pieceLookup[toSq] = blackQueen;
                break;
            case 0:
                break;
        }
        
        if ((from >> 16) == to)
        {
            chessBoard->enPassantSq = from >> 8;
        }
        
        
    }else
    {
        chessBoard->pieceBoards[whitePawn] &= ~from;
        chessBoard->pieceBoards[whitePawn] |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
        chessBoard->coloredBoards[white] &= ~from;
        chessBoard->coloredBoards[white] |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whitePawn;

        if (move->move & enPassantMask)
        {
            moveTo = to >> 8;
            moveToSq = getSqInd(moveTo);
            chessBoard->allPieces &= ~moveTo;
            chessBoard->pieceLookup[moveToSq] = empty;
            capture = pawn;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->pieceBoards[blackPawn] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][moveToSq];
                chessBoard->coloredBoards[black] &= ~moveTo;
                break;
            case knight:
                chessBoard->pieceBoards[blackKnight] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][moveToSq];
                chessBoard->coloredBoards[black] &= ~moveTo;
                break;
            case bishop:
                chessBoard->pieceBoards[blackBishop] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][moveToSq];
                chessBoard->coloredBoards[black] &= ~moveTo;
                break;
            case rook:
                chessBoard->pieceBoards[blackRook] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][moveToSq];
                chessBoard->coloredBoards[black] &= ~moveTo;
                break;
            case queen:
                chessBoard->pieceBoards[blackQueen] &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][moveToSq];
                chessBoard->coloredBoards[black] &= ~moveTo;
                break;
            case 0:
                break;
        }

        switch (promotion)
        {
            case knightPromotion:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->pieceBoards[whiteKnight] |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->pieceLookup[toSq] = whiteKnight;
                break;
            case bishopPromotion:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->pieceBoards[whiteBishop] |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->pieceLookup[toSq] = whiteBishop;
                break;
            case rookPromotion:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->pieceBoards[whiteRook] |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->pieceLookup[toSq] = whiteRook;
                break;
            case queenPromotion:
                chessBoard->pieceBoards[whitePawn] &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->pieceBoards[whiteQueen] |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->pieceLookup[toSq] = whiteQueen;
                break;
            case 0:
                break;
        }

        if ((from << 16) == to)
        {
            chessBoard->enPassantSq = from << 8;
        }
    }

    moveData->capturedPiece = capture;
}

void makeMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t piece = getPieceFromSquare(getFromSq(move->move), chessBoard);

    MoveData* moveData = &chessBoard->moveDataStack.moveData[chessBoard->moveDataStack.size]; 

    addMoveData(chessBoard);
    
    hashEnPassant(chessBoard, hashes);

    chessBoard->enPassantSq = 0;

    switch (piece)
    {
        case pawn:
            makePawnMove(chessBoard, move, hashes, moveData);
            break;
        case knight:
            makeKnightMove(chessBoard, move, hashes, moveData);
            break;
        case bishop:
            makeBishopMove(chessBoard, move, hashes, moveData);
            break;
        case rook:
            makeRookMove(chessBoard, move, hashes, moveData);
            break;
        case queen:
            makeQueenMove(chessBoard, move, hashes, moveData);
            break;
        case king:
            makeKingMove(chessBoard, move, hashes, moveData);
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