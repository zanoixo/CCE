#include "ChessBoard.h"
#include "Move.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"

void makeKnightMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->blackKnights &= ~from;
        chessBoard->blackKnights |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackKnight;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {   

        chessBoard->whiteKnights &= ~from;
        chessBoard->whiteKnights |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteKnight;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case 0:
                break;
        }
    }
}

void makeBishopMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->blackBishops &= ~from;
        chessBoard->blackBishops |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackBishop;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteBishops &= ~from;
        chessBoard->whiteBishops |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteBishop;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case 0:
                break;
        }
    }
}

void makeRookMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->blackRooks &= ~from;
        chessBoard->blackRooks |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackRook][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackRook;

        if (from == h8 && canBlackShortCastle(chessBoard))
        {
            chessBoard->flags &= ~blackShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
        }

        if (from == a8 && canBlackLongCastle(chessBoard))
        {
            chessBoard->flags &= ~blackLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteRooks &= ~from;
        chessBoard->whiteRooks |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteRook;

        if (from == h1 && canWhiteShortCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
        }

        if (from == a1 && canWhiteLongCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case 0:
                break;
        }
    }
}

void makeQueenMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    chessBoard->pieceLookup[fromSq] = empty;
    chessBoard->pieceLookup[toSq] = blackQueen;

    if (isBlacksMove)
    {
        chessBoard->blackQueens &= ~from;
        chessBoard->blackQueens |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteQueens &= ~from;
        chessBoard->whiteQueens |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteQueen;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case 0:
                break;
        }
    }
}

void makeKingMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);

    if (isBlacksMove)
    {
        chessBoard->blackKing &= ~from;
        chessBoard->blackKing |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKing][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKing][toSq];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackKing;

        if (from == e8 && canBlackShortCastle(chessBoard))
        {
            chessBoard->flags &= ~blackShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
        }

        if (from == e8 && canBlackLongCastle(chessBoard))
        {
            chessBoard->flags &= ~blackLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][toSq];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }

        if (from == e8)
        {
            if (to == g8)
            {
                chessBoard->blackRooks &= ~ h8;
                chessBoard->blackRooks |= f8;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][getSqInd(h8)];
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][getSqInd(f8)];
                chessBoard->blackPieces &= ~h8;
                chessBoard->blackPieces |= f8;
                chessBoard->allPieces &= ~h8;
                chessBoard->allPieces |= f8;
                chessBoard->pieceLookup[getSqInd(h8)] = empty;
                chessBoard->pieceLookup[getSqInd(f8)] = blackRook;
                chessBoard->flags |= hasBlackCastledMask;
            }

            if (to == c8)
            {
                chessBoard->blackRooks &= ~ a8;
                chessBoard->blackRooks |= d8;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][getSqInd(a8)];
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][getSqInd(d8)];
                chessBoard->blackPieces &= ~a8;
                chessBoard->blackPieces |= d8;
                chessBoard->allPieces &= ~a8;
                chessBoard->allPieces |= d8;
                chessBoard->pieceLookup[getSqInd(a8)] = empty;
                chessBoard->pieceLookup[getSqInd(d8)] = blackRook;
                chessBoard->flags |= hasBlackCastledMask;
            }
        }
        
    }else
    {
        chessBoard->whiteKing &= ~from;
        chessBoard->whiteKing |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKing][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKing][toSq];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whiteKing;

        if (from == e1 && canWhiteShortCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
        }

        if (from == e1 && canWhiteLongCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][toSq];
                chessBoard->blackPieces &= ~to;
                break;
            case 0:
                break;
        }

        if (from == e1)
        {
            if (to == g1)
            {
                chessBoard->whiteRooks &= ~ h1;
                chessBoard->whiteRooks |= f1;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][getSqInd(h1)];
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][getSqInd(f1)];
                chessBoard->whitePieces &= ~h1;
                chessBoard->whitePieces |= f1;
                chessBoard->allPieces &= ~h1;
                chessBoard->allPieces |= f1;
                chessBoard->pieceLookup[getSqInd(h1)] = empty;
                chessBoard->pieceLookup[getSqInd(f1)] = whiteRook;
                chessBoard->flags |= hasWhiteCastledMask;
            }

            if (to == c1)
            {
                chessBoard->whiteRooks &= ~ a1;
                chessBoard->whiteRooks |= d1;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][getSqInd(a1)];
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][getSqInd(d1)];
                chessBoard->whitePieces &= ~a1;
                chessBoard->whitePieces |= d1;
                chessBoard->allPieces &= ~a1;
                chessBoard->allPieces |= d1;
                chessBoard->pieceLookup[getSqInd(a1)] = empty;
                chessBoard->pieceLookup[getSqInd(d1)] = whiteRook;
                chessBoard->flags |= hasWhiteCastledMask;
            }
        }
    }
}

void makePawnMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);
    uint8_t promotion = getPromotionPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);
    
    uint64_t moveTo = to;

    uint8_t moveToSq = getSqInd(moveTo);

    if (isBlacksMove)
    {
        chessBoard->blackPawns &= ~from;
        chessBoard->blackPawns |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = blackPawn;

        if (move->flags & enPassantMask)
        {
            moveTo = to << 8;
            moveToSq = getSqInd(moveTo);
            chessBoard->allPieces &= ~moveTo;
            chessBoard->pieceLookup[moveToSq] = empty;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][moveToSq];
                chessBoard->whitePieces &= ~moveTo;
                break;
            case knight:
                chessBoard->whiteKnights &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][moveToSq];
                chessBoard->whitePieces &= ~moveTo;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][moveToSq];
                chessBoard->whitePieces &= ~moveTo;
                break;
            case rook:
                chessBoard->whiteRooks &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][moveToSq];
                chessBoard->whitePieces &= ~moveTo;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueen][moveToSq];
                chessBoard->whitePieces &= ~moveTo;
                break;
            case 0:
                break;
        }

        switch (promotion)
        {
            case knightPromotion:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][toSq];
                chessBoard->pieceLookup[toSq] = blackKnight;
                break;
            case bishopPromotion:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][toSq];
                chessBoard->pieceLookup[toSq] = blackBishop;
                break;
            case rookPromotion:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][toSq];
                chessBoard->pieceLookup[toSq] = blackRook;
                break;
            case queenPromotion:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][toSq];
                chessBoard->blackQueens |= to;
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
        chessBoard->whitePawns &= ~from;
        chessBoard->whitePawns |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][fromSq];
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;
        chessBoard->pieceLookup[fromSq] = empty;
        chessBoard->pieceLookup[toSq] = whitePawn;

        if (move->flags & enPassantMask)
        {
            moveTo = to >> 8;
            moveToSq = getSqInd(moveTo);
            chessBoard->allPieces &= ~moveTo;
            chessBoard->pieceLookup[moveToSq] = empty;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawn][moveToSq];
                chessBoard->blackPieces &= ~moveTo;
                break;
            case knight:
                chessBoard->blackKnights &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnight][moveToSq];
                chessBoard->blackPieces &= ~moveTo;
                break;
            case bishop:
                chessBoard->blackBishops &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishop][moveToSq];
                chessBoard->blackPieces &= ~moveTo;
                break;
            case rook:
                chessBoard->blackRooks &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRook][moveToSq];
                chessBoard->blackPieces &= ~moveTo;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueen][moveToSq];
                chessBoard->blackPieces &= ~moveTo;
                break;
            case 0:
                break;
        }

        switch (promotion)
        {
            case knightPromotion:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whiteKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnight][toSq];
                chessBoard->pieceLookup[toSq] = whiteKnight;
                break;
            case bishopPromotion:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whiteBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishop][toSq];
                chessBoard->pieceLookup[toSq] = whiteBishop;
                break;
            case rookPromotion:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whiteRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRook][toSq];
                chessBoard->pieceLookup[toSq] = whiteRook;
                break;
            case queenPromotion:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawn][toSq];
                chessBoard->whiteQueens |= to;
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
}

void makeMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t piece = getPiece(*move);

    addMoveData(chessBoard);
    
    hashEnPassant(chessBoard, hashes);

    chessBoard->enPassantSq = 0;

    switch (piece)
    {
        case pawn:
            makePawnMove(chessBoard, move, hashes);
            break;
        case knight:
            makeKnightMove(chessBoard, move, hashes);
            break;
        case bishop:
            makeBishopMove(chessBoard, move, hashes);
            break;
        case rook:
            makeRookMove(chessBoard, move, hashes);
            break;
        case queen:
            makeQueenMove(chessBoard, move, hashes);
            break;
        case king:
            makeKingMove(chessBoard, move, hashes);
            break;
    }

    chessBoard->flags ^= colorMask;

    hashEnPassant(chessBoard, hashes);
    
    chessBoard->positionHash ^= hashes->colorHash;

    addMoveToHistory(chessBoard, move);
}

void makeNullMove(ChessBoard* chessBoard, TranspositionTableHashes* hashes)
{
    addMoveData(chessBoard);
    chessBoard->flags ^= colorMask;
    chessBoard->positionHash ^= hashes->colorHash;
    hashEnPassant(chessBoard, hashes);
    chessBoard->enPassantSq = 0;
}