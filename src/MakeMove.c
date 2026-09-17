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

    if (isBlacksMove)
    {
        chessBoard->blackKnights &= ~from;
        chessBoard->blackKnights |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {   

        chessBoard->whiteKnights &= ~from;
        chessBoard->whiteKnights |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
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

    if (isBlacksMove)
    {
        chessBoard->blackBishops &= ~from;
        chessBoard->blackBishops |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteBishops &= ~from;
        chessBoard->whiteBishops |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
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

    if (isBlacksMove)
    {
        chessBoard->blackRooks &= ~from;
        chessBoard->blackRooks |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        if (from == h8 && canBlackShortCastle(chessBoard))
        {
            chessBoard->flags &= ~blackShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
            move->flags |= removeBlackShortCastleFlag;
        }

        if (from == a8 && canBlackLongCastle(chessBoard))
        {
            chessBoard->flags &= ~blackLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
            move->flags |= removeBlackLongCastleFlag;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteRooks &= ~from;
        chessBoard->whiteRooks |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        if (from == h1 && canWhiteShortCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
            move->flags |= removeWhiteShortCastleFlag;
        }

        if (from == a1 && canWhiteLongCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
            move->flags |= removeWhiteLongCastleFlag;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
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

    if (isBlacksMove)
    {
        chessBoard->blackQueens &= ~from;
        chessBoard->blackQueens |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteQueens &= ~from;
        chessBoard->whiteQueens |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
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

    if (isBlacksMove)
    {
        chessBoard->blackKing &= ~from;
        chessBoard->blackKing |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKingHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKingHash][getSqInd(to)];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        if (from == e8 && canBlackShortCastle(chessBoard))
        {
            chessBoard->flags &= ~blackShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
            move->flags |= removeBlackShortCastleFlag;
        }

        if (from == e8 && canBlackLongCastle(chessBoard))
        {
            chessBoard->flags &= ~blackLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
            move->flags |= removeBlackLongCastleFlag;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces &= ~to;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
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
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(h8)];
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(f8)];
                chessBoard->blackPieces &= ~h8;
                chessBoard->blackPieces |= f8;
                chessBoard->allPieces &= ~h8;
                chessBoard->allPieces |= f8;
                chessBoard->flags |= hasBlackCastledMask;
            }

            if (to == c8)
            {
                chessBoard->blackRooks &= ~ a8;
                chessBoard->blackRooks |= d8;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(a8)];
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(d8)];
                chessBoard->blackPieces &= ~a8;
                chessBoard->blackPieces |= d8;
                chessBoard->allPieces &= ~a8;
                chessBoard->allPieces |= d8;
                chessBoard->flags |= hasBlackCastledMask;
            }
        }
        
    }else
    {
        chessBoard->whiteKing &= ~from;
        chessBoard->whiteKing |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKingHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKingHash][getSqInd(to)];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        if (from == e1 && canWhiteShortCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
            move->flags |= removeWhiteShortCastleFlag;
        }

        if (from == e1 && canWhiteLongCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
            move->flags |= removeWhiteLongCastleFlag;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case knight:
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;
                break;
            case rook:
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces &= ~to;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
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
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(h1)];
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(f1)];
                chessBoard->whitePieces &= ~h1;
                chessBoard->whitePieces |= f1;
                chessBoard->allPieces &= ~h1;
                chessBoard->allPieces |= f1;
                chessBoard->flags |= hasWhiteCastledMask;
            }

            if (to == c1)
            {
                chessBoard->whiteRooks &= ~ a1;
                chessBoard->whiteRooks |= d1;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(a1)];
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(d1)];
                chessBoard->whitePieces &= ~a1;
                chessBoard->whitePieces |= d1;
                chessBoard->allPieces &= ~a1;
                chessBoard->allPieces |= d1;
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
    
    uint64_t moveTo = to;

    if (isBlacksMove)
    {
        chessBoard->blackPawns &= ~from;
        chessBoard->blackPawns |= to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
        chessBoard->blackPieces &= ~from;
        chessBoard->blackPieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        if (move->flags & enPassantMask)
        {
            moveTo = to << 8;
            chessBoard->allPieces &= ~moveTo;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(moveTo)];
                chessBoard->whitePieces &= ~moveTo;
                break;
            case knight:
                chessBoard->whiteKnights &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(moveTo)];
                chessBoard->whitePieces &= ~moveTo;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(moveTo)];
                chessBoard->whitePieces &= ~moveTo;
                break;
            case rook:
                chessBoard->whiteRooks &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(moveTo)];
                chessBoard->whitePieces &= ~moveTo;

                if (to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(moveTo)];
                chessBoard->whitePieces &= ~moveTo;
                break;
            case 0:
                break;
        }

        switch (promotion)
        {
            case knightPromotion:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                break;
            case bishopPromotion:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                break;
            case rookPromotion:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                break;
            case queenPromotion:
                chessBoard->blackPawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
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
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
        chessBoard->whitePieces &= ~from;
        chessBoard->whitePieces |= to;
        chessBoard->allPieces &= ~from;
        chessBoard->allPieces |= to;

        if (move->flags & enPassantMask)
        {
            moveTo = to >> 8;
            chessBoard->allPieces &= ~moveTo;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(moveTo)];
                chessBoard->blackPieces &= ~moveTo;
                break;
            case knight:
                chessBoard->blackKnights &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(moveTo)];
                chessBoard->blackPieces &= ~moveTo;
                break;
            case bishop:
                chessBoard->blackBishops &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(moveTo)];
                chessBoard->blackPieces &= ~moveTo;
                break;
            case rook:
                chessBoard->blackRooks &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(moveTo)];
                chessBoard->blackPieces &= ~moveTo;

                if (to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(moveTo)];
                chessBoard->blackPieces &= ~moveTo;
                break;
            case 0:
                break;
        }

        switch (promotion)
        {
            case knightPromotion:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whiteKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                break;
            case bishopPromotion:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whiteBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                break;
            case rookPromotion:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whiteRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                break;
            case queenPromotion:
                chessBoard->whitePawns &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whiteQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
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
    
    hashEnPassant(chessBoard, hashes);

    addMoveData(chessBoard, chessBoard->enPassantSq);

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
    addMoveData(chessBoard, chessBoard->enPassantSq);
    chessBoard->flags ^= colorMask;
    chessBoard->positionHash ^= hashes->colorHash;
    hashEnPassant(chessBoard, hashes);
    chessBoard->enPassantSq = 0;
}