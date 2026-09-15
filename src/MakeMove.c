#include "ChessBoard.h"
#include "Move.h"
#include "ChessTranspositionTables.h"
#include "ChessBitboards.h"

void makeKnightMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    if (isBlacksMove)
    {
        chessBoard->blackKnights &= ~move->from;
        chessBoard->blackKnights |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(move->to)];
        chessBoard->blackPieces &= ~move->from;
        chessBoard->blackPieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;

                if (move->to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (move->to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case 0:
                break;
        }
    }else
    {   

        chessBoard->whiteKnights &= ~move->from;
        chessBoard->whiteKnights |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(move->to)];
        chessBoard->whitePieces &= ~move->from;
        chessBoard->whitePieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case knight:
                chessBoard->blackKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case rook:
                chessBoard->blackRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;

                if (move->to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (move->to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
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

    if (isBlacksMove)
    {
        chessBoard->blackBishops &= ~move->from;
        chessBoard->blackBishops |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(move->to)];
        chessBoard->blackPieces &= ~move->from;
        chessBoard->blackPieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;

                if (move->to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (move->to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteBishops &= ~move->from;
        chessBoard->whiteBishops |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(move->to)];
        chessBoard->whitePieces &= ~move->from;
        chessBoard->whitePieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case knight:
                chessBoard->blackKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case rook:
                chessBoard->blackRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;

                if (move->to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (move->to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
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

    if (isBlacksMove)
    {
        chessBoard->blackRooks &= ~move->from;
        chessBoard->blackRooks |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(move->to)];
        chessBoard->blackPieces &= ~move->from;
        chessBoard->blackPieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        if (move->from == h8 && canBlackShortCastle(chessBoard))
        {
            chessBoard->flags &= ~blackShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
            move->flags |= removeBlackShortCastleFlag;
        }

        if (move->from == a8 && canBlackLongCastle(chessBoard))
        {
            chessBoard->flags &= ~blackLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
            move->flags |= removeBlackLongCastleFlag;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;

                if (move->to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (move->to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteRooks &= ~move->from;
        chessBoard->whiteRooks |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(move->to)];
        chessBoard->whitePieces &= ~move->from;
        chessBoard->whitePieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        if (move->from == h1 && canWhiteShortCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
            move->flags |= removeWhiteShortCastleFlag;
        }

        if (move->from == a1 && canWhiteLongCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
            move->flags |= removeWhiteLongCastleFlag;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case knight:
                chessBoard->blackKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case rook:
                chessBoard->blackRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;

                if (move->to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (move->to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
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

    if (isBlacksMove)
    {
        chessBoard->blackQueens &= ~move->from;
        chessBoard->blackQueens |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(move->to)];
        chessBoard->blackPieces &= ~move->from;
        chessBoard->blackPieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;

                if (move->to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (move->to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case 0:
                break;
        }
    }else
    {
        chessBoard->whiteQueens &= ~move->from;
        chessBoard->whiteQueens |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(move->to)];
        chessBoard->whitePieces &= ~move->from;
        chessBoard->whitePieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case knight:
                chessBoard->blackKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case rook:
                chessBoard->blackRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;

                if (move->to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (move->to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
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

    if (isBlacksMove)
    {
        chessBoard->blackKing &= ~move->from;
        chessBoard->blackKing |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKingHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKingHash][getSqInd(move->to)];
        chessBoard->blackPieces &= ~move->from;
        chessBoard->blackPieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        if (move->from == e8 && canBlackShortCastle(chessBoard))
        {
            chessBoard->flags &= ~blackShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
            move->flags |= removeBlackShortCastleFlag;
        }

        if (move->from == e8 && canBlackLongCastle(chessBoard))
        {
            chessBoard->flags &= ~blackLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
            move->flags |= removeBlackLongCastleFlag;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case knight:
                chessBoard->whiteKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case bishop:
                chessBoard->whiteBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case rook:
                chessBoard->whiteRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;

                if (move->to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (move->to == h1 && canWhiteShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                    move->flags |= removeWhiteShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->whiteQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(move->to)];
                chessBoard->whitePieces &= ~move->to;
                break;
            case 0:
                break;
        }

        if (move->from == e8)
        {
            if (move->to == g8)
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

            if (move->to == c8)
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
        chessBoard->whiteKing &= ~move->from;
        chessBoard->whiteKing |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKingHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKingHash][getSqInd(move->to)];
        chessBoard->whitePieces &= ~move->from;
        chessBoard->whitePieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        if (move->from == e1 && canWhiteShortCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
            move->flags |= removeWhiteShortCastleFlag;
        }

        if (move->from == e1 && canWhiteLongCastle(chessBoard))
        {
            chessBoard->flags &= ~whiteLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
            move->flags |= removeWhiteLongCastleFlag;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case knight:
                chessBoard->blackKnights &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case bishop:
                chessBoard->blackBishops &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case rook:
                chessBoard->blackRooks &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;

                if (move->to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (move->to == h8 && canBlackShortCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                    move->flags |= removeBlackShortCastleFlag;
                }

                break;
            case queen:
                chessBoard->blackQueens &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(move->to)];
                chessBoard->blackPieces &= ~move->to;
                break;
            case 0:
                break;
        }

        if (move->from == e1)
        {
            if (move->to == g1)
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

            if (move->to == c1)
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
    uint64_t moveTo = move->to;

    if (isBlacksMove)
    {
        chessBoard->blackPawns &= ~move->from;
        chessBoard->blackPawns |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
        chessBoard->blackPieces &= ~move->from;
        chessBoard->blackPieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        if (move->flags & enPassantMask)
        {
            moveTo = move->to << 8;
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

                if (move->to == a1 && canWhiteLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                    move->flags |= removeWhiteLongCastleFlag;
                }
                if (move->to == h1 && canWhiteShortCastle(chessBoard))
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
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackKnights |= move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(move->to)];
                break;
            case bishopPromotion:
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackBishops |= move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(move->to)];
                break;
            case rookPromotion:
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackRooks |= move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(move->to)];
                break;
            case queenPromotion:
                chessBoard->blackPawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(move->to)];
                chessBoard->blackQueens |= move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(move->to)];
                break;
            case 0:
                break;
        }
        
        if ((move->from >> 16) == move->to)
        {
            chessBoard->enPassantSq = move->from >> 8;
        }
        
        
    }else
    {
        chessBoard->whitePawns &= ~move->from;
        chessBoard->whitePawns |= move->to;
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->from)];
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
        chessBoard->whitePieces &= ~move->from;
        chessBoard->whitePieces |= move->to;
        chessBoard->allPieces &= ~move->from;
        chessBoard->allPieces |= move->to;

        if (move->flags & enPassantMask)
        {
            moveTo = move->to >> 8;
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

                if (move->to == a8 && canBlackLongCastle(chessBoard))
                {
                    chessBoard->flags &= ~blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                    move->flags |= removeBlackLongCastleFlag;
                }
                if (move->to == h8 && canBlackShortCastle(chessBoard))
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
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whiteKnights |= move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(move->to)];
                break;
            case bishopPromotion:
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whiteBishops |= move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(move->to)];
                break;
            case rookPromotion:
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whiteRooks |= move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(move->to)];
                break;
            case queenPromotion:
                chessBoard->whitePawns &= ~move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(move->to)];
                chessBoard->whiteQueens |= move->to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(move->to)];
                break;
            case 0:
                break;
        }

        if ((move->from << 16) == move->to)
        {
            chessBoard->enPassantSq = move->from << 8;
        }
    }
}

void makeMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t piece = getPiece(*move);
    
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

void makeNullMove(ChessBoard* chessBoard, Move* move, TranspositionTableHashes* hashes)
{
    chessBoard->flags ^= colorMask;
    chessBoard->positionHash ^= hashes->colorHash;
    move->prevEnPassantSq = chessBoard->enPassantSq;
    hashEnPassant(chessBoard, hashes);
    chessBoard->enPassantSq = 0;
}