#include "ChessBoard.h"
#include "Move.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"

void unMakeKnightMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackKnights &= ~to;
        chessBoard->blackKnights |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(from)];
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeWhiteLongCastleFlag)
                {
                    chessBoard->flags |= whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }

                if (move->flags & removeWhiteShortCastleFlag)
                {
                    chessBoard->flags |= whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }
                
                break;
            case queen:
                chessBoard->whiteQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
    else
    {

        chessBoard->whiteKnights &= ~to;
        chessBoard->whiteKnights |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(from)];
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeBlackLongCastleFlag)
                {
                    chessBoard->flags |= blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }

                if (move->flags & removeBlackShortCastleFlag)
                {
                    chessBoard->flags |= blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
}

void unMakeBishopMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackBishops &= ~to;
        chessBoard->blackBishops |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(from)];
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeWhiteLongCastleFlag)
                {
                    chessBoard->flags |= whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }

                if (move->flags & removeWhiteShortCastleFlag)
                {
                    chessBoard->flags |= whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
    else
    {
        chessBoard->whiteBishops &= ~to;
        chessBoard->whiteBishops |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(from)];
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeBlackLongCastleFlag)
                {
                    chessBoard->flags |= blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }

                if (move->flags & removeBlackShortCastleFlag)
                {
                    chessBoard->flags |= blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
}

void unMakeRookMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackRooks &= ~to;
        chessBoard->blackRooks |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(from)];
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        if (move->flags & removeBlackLongCastleFlag)
        {
            chessBoard->flags |= blackLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
        }

        if (move->flags & removeBlackShortCastleFlag)
        {
            chessBoard->flags |= blackShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
        }
        
        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeWhiteLongCastleFlag)
                {
                    chessBoard->flags |= whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }

                if (move->flags & removeWhiteShortCastleFlag)
                {
                    chessBoard->flags |= whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
    else
    {
        chessBoard->whiteRooks &= ~to;
        chessBoard->whiteRooks |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(from)];
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        if (move->flags & removeWhiteLongCastleFlag)
        {
            chessBoard->flags |= whiteLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
        }

        if (move->flags & removeWhiteShortCastleFlag)
        {
            chessBoard->flags |= whiteShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeBlackLongCastleFlag)
                {
                    chessBoard->flags |= blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }

                if (move->flags & removeBlackShortCastleFlag)
                {
                    chessBoard->flags |= blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }
                
                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
}

void unMakeQueenMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackQueens &= ~to;
        chessBoard->blackQueens |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(from)];
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeWhiteLongCastleFlag)
                {
                    chessBoard->flags |= whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }

                if (move->flags & removeWhiteShortCastleFlag)
                {
                    chessBoard->flags |= whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
    else
    {
        chessBoard->whiteQueens &= ~to;
        chessBoard->whiteQueens |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(from)];
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeBlackLongCastleFlag)
                {
                    chessBoard->flags |= blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }

                if (move->flags & removeBlackShortCastleFlag)
                {
                    chessBoard->flags |= blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
}

void unMakeKingMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackKing &= ~to;
        chessBoard->blackKing |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[blackKingHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackKingHash][getSqInd(from)];
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        if (move->flags & removeBlackLongCastleFlag)
        {
            chessBoard->flags |= blackLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
        }

        if (move->flags & removeBlackShortCastleFlag)
        {
            chessBoard->flags |= blackShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeWhiteLongCastleFlag)
                {
                    chessBoard->flags |= whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }

                if (move->flags & removeWhiteShortCastleFlag)
                {
                    chessBoard->flags |= whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }

        if (from == e8)
        {
            if (to == g8)
            {
                chessBoard->blackRooks &= ~f8;
                chessBoard->blackRooks |= h8;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(f8)];
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(h8)];
                chessBoard->blackPieces &= ~f8;
                chessBoard->blackPieces |= h8;
                chessBoard->allPieces &= ~f8;
                chessBoard->allPieces |= h8;
                chessBoard->flags &= ~hasBlackCastledMask;
            }

            if (to == c8)
            {
                chessBoard->blackRooks &= ~d8;
                chessBoard->blackRooks |= a8;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(d8)];
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(a8)];
                chessBoard->blackPieces &= ~d8;
                chessBoard->blackPieces |= a8;
                chessBoard->allPieces &= ~d8;
                chessBoard->allPieces |= a8;
                chessBoard->flags &= ~hasBlackCastledMask;
            }
        }
    }
    else
    {
        chessBoard->whiteKing &= ~to;
        chessBoard->whiteKing |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKingHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[whiteKingHash][getSqInd(from)];
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

         if (move->flags & removeWhiteLongCastleFlag)
        {
            chessBoard->flags |= whiteLongCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
        }

        if (move->flags & removeWhiteShortCastleFlag)
        {
            chessBoard->flags |= whiteShortCastleMask;
            chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;

                if (move->flags & removeBlackLongCastleFlag)
                {
                    chessBoard->flags |= blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }

                if (move->flags & removeBlackShortCastleFlag)
                {
                    chessBoard->flags |= blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }

        if (from == e1)
        {
            if (to == g1)
            {
                chessBoard->whiteRooks &= ~f1;
                chessBoard->whiteRooks |= h1;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(f1)];
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(h1)];
                chessBoard->whitePieces &= ~f1;
                chessBoard->whitePieces |= h1;
                chessBoard->allPieces &= ~f1;
                chessBoard->allPieces |= h1;
                chessBoard->flags &= ~hasWhiteCastledMask;
            }

            if (to == c1)
            {
                chessBoard->whiteRooks &= ~d1;
                chessBoard->whiteRooks |= a1;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(d1)];
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(a1)];
                chessBoard->whitePieces &= ~d1;
                chessBoard->whitePieces |= a1;
                chessBoard->allPieces &= ~d1;
                chessBoard->allPieces |= a1;
                chessBoard->flags &= ~hasWhiteCastledMask;
            }
        }
    }
}

void unMakePawnMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);
    uint8_t promotion = getPromotionPiece(*move);
    
    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint64_t moveTo = to;

    if (isBlacksMove)
    {
        switch (promotion)
        {
            case knightPromotion:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(to)];
                break;
            case bishopPromotion:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(to)];
                break;
            case rookPromotion:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(to)];
                break;
            case queenPromotion:
                chessBoard->blackPawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
                chessBoard->blackQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(to)];
                break;
            case 0:
                break;
        }

        chessBoard->blackPawns &= ~to;
        chessBoard->blackPawns |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(from)];
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        if (move->flags & enPassantMask)
        {
            moveTo = to << 8;
            chessBoard->allPieces |= moveTo;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(moveTo)];
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case knight:
                chessBoard->whiteKnights |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(moveTo)];
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case bishop:
                chessBoard->whiteBishops |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(moveTo)];
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case rook:
                chessBoard->whiteRooks |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(moveTo)];
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;

                if (move->flags & removeWhiteLongCastleFlag)
                {
                    chessBoard->flags |= whiteLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
                }

                if (move->flags & removeWhiteShortCastleFlag)
                {
                    chessBoard->flags |= whiteShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
                }

                break;
            case queen:
                chessBoard->whiteQueens |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(moveTo)];
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
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
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whiteKnights &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][getSqInd(to)];
                break;
            case bishopPromotion:
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whiteBishops &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][getSqInd(to)];
                break;
            case rookPromotion:
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whiteRooks &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][getSqInd(to)];
                break;
            case queenPromotion:
                chessBoard->whitePawns |= to;
                chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
                chessBoard->whiteQueens &= ~to;
                chessBoard->positionHash ^= hashes->pieceHashes[whiteQueenHash][getSqInd(to)];
                break;
            case 0:
                break;
        }

        chessBoard->whitePawns &= ~to;
        chessBoard->whitePawns |= from;
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(to)];
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][getSqInd(from)];
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        if (move->flags & enPassantMask)
        {
            moveTo = to >> 8;
            chessBoard->allPieces |= moveTo;
        }

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][getSqInd(moveTo)];
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case knight:
                chessBoard->blackKnights |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][getSqInd(moveTo)];
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case bishop:
                chessBoard->blackBishops |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][getSqInd(moveTo)];
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case rook:
                chessBoard->blackRooks |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][getSqInd(moveTo)];
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                
                if (move->flags & removeBlackLongCastleFlag)
                {
                    chessBoard->flags |= blackLongCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];
                }

                if (move->flags & removeBlackShortCastleFlag)
                {
                    chessBoard->flags |= blackShortCastleMask;
                    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
                }

                break;
            case queen:
                chessBoard->blackQueens |= moveTo;
                chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][getSqInd(moveTo)];
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case 0:
                break;
        }
    }
}

void unMakeMove(ChessBoard* chessBoard, Move* move, TranspositionTableHashes* hashes)
{
    chessBoard->flags ^= colorMask;
    chessBoard->positionHash ^= hashes->colorHash;

    uint8_t piece = getPiece(*move);

    switch (piece)
    {
        case pawn:
            unMakePawnMove(chessBoard, move, hashes);
            break;
        case knight:
            unMakeKnightMove(chessBoard, move, hashes);
            break;
        case bishop:
            unMakeBishopMove(chessBoard, move, hashes);
            break;
        case rook:
            unMakeRookMove(chessBoard, move, hashes);
            break;
        case queen:
            unMakeQueenMove(chessBoard, move, hashes);
            break;
        case king:
            unMakeKingMove(chessBoard, move, hashes);
            break;
    }

    hashEnPassant(chessBoard, hashes);

    revertMoveData(chessBoard);

    hashEnPassant(chessBoard, hashes);
    
    removeMovefromHistory(chessBoard);
}

void unMakeNullMove(ChessBoard* chessBoard, TranspositionTableHashes* hashes)
{
    chessBoard->flags ^= colorMask;
    chessBoard->positionHash ^= hashes->colorHash;
    revertMoveData(chessBoard);
    hashEnPassant(chessBoard, hashes);
}