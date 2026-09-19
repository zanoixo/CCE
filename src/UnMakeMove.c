#include "ChessBoard.h"
#include "Move.h"
#include "TranspositionTables.h"
#include "ChessBitboards.h"

void unMakeKnightMove(ChessBoard *chessBoard, Move *move)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackKnights &= ~to;
        chessBoard->blackKnights |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->whiteQueens |= to;
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
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
}

void unMakeBishopMove(ChessBoard *chessBoard, Move *move)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackBishops &= ~to;
        chessBoard->blackBishops |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->whiteQueens |= to;
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
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
}

void unMakeRookMove(ChessBoard *chessBoard, Move *move)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackRooks &= ~to;
        chessBoard->blackRooks |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->whiteQueens |= to;
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
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
}

void unMakeQueenMove(ChessBoard *chessBoard, Move *move)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackQueens &= ~to;
        chessBoard->blackQueens |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->whiteQueens |= to;
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
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->blackQueens |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case 0:
                break;
        }
    }
}

void unMakeKingMove(ChessBoard *chessBoard, Move *move)
{
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t capture = getCapturedPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    if (isBlacksMove)
    {
        chessBoard->blackKing &= ~to;
        chessBoard->blackKing |= from;
        chessBoard->blackPieces &= ~to;
        chessBoard->blackPieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->whitePawns |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->whiteKnights |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->whiteBishops |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->whiteRooks |= to;
                chessBoard->whitePieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->whiteQueens |= to;
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
                chessBoard->blackPieces &= ~f8;
                chessBoard->blackPieces |= h8;
                chessBoard->allPieces &= ~f8;
                chessBoard->allPieces |= h8;
            }

            if (to == c8)
            {
                chessBoard->blackRooks &= ~d8;
                chessBoard->blackRooks |= a8;
                chessBoard->blackPieces &= ~d8;
                chessBoard->blackPieces |= a8;
                chessBoard->allPieces &= ~d8;
                chessBoard->allPieces |= a8;
            }
        }
    }
    else
    {
        chessBoard->whiteKing &= ~to;
        chessBoard->whiteKing |= from;
        chessBoard->whitePieces &= ~to;
        chessBoard->whitePieces |= from;
        chessBoard->allPieces &= ~to;
        chessBoard->allPieces |= from;

        switch (capture)
        {
            case pawn:
                chessBoard->blackPawns |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case knight:
                chessBoard->blackKnights |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case bishop:
                chessBoard->blackBishops |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case rook:
                chessBoard->blackRooks |= to;
                chessBoard->blackPieces |= to;
                chessBoard->allPieces |= to;
                break;
            case queen:
                chessBoard->blackQueens |= to;
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
                chessBoard->whitePieces &= ~f1;
                chessBoard->whitePieces |= h1;
                chessBoard->allPieces &= ~f1;
                chessBoard->allPieces |= h1;
            }

            if (to == c1)
            {
                chessBoard->whiteRooks &= ~d1;
                chessBoard->whiteRooks |= a1;
                chessBoard->whitePieces &= ~d1;
                chessBoard->whitePieces |= a1;
                chessBoard->allPieces &= ~d1;
                chessBoard->allPieces |= a1;
            }
        }
    }
}

void unMakePawnMove(ChessBoard *chessBoard, Move *move)
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
                chessBoard->blackKnights &= ~to;
                break;
            case bishopPromotion:
                chessBoard->blackPawns |= to;
                chessBoard->blackBishops &= ~to;
                break;
            case rookPromotion:
                chessBoard->blackPawns |= to;
                chessBoard->blackRooks &= ~to;
                break;
            case queenPromotion:
                chessBoard->blackPawns |= to;
                chessBoard->blackQueens &= ~to;
                break;
            case 0:
                break;
        }

        chessBoard->blackPawns &= ~to;
        chessBoard->blackPawns |= from;
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
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case knight:
                chessBoard->whiteKnights |= moveTo;
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case bishop:
                chessBoard->whiteBishops |= moveTo;
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case rook:
                chessBoard->whiteRooks |= moveTo;
                chessBoard->whitePieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case queen:
                chessBoard->whiteQueens |= moveTo;
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
                chessBoard->whiteKnights &= ~to;
                break;
            case bishopPromotion:
                chessBoard->whitePawns |= to;
                chessBoard->whiteBishops &= ~to;
                break;
            case rookPromotion:
                chessBoard->whitePawns |= to;
                chessBoard->whiteRooks &= ~to;
                break;
            case queenPromotion:
                chessBoard->whitePawns |= to;
                chessBoard->whiteQueens &= ~to;
                break;
            case 0:
                break;
        }

        chessBoard->whitePawns &= ~to;
        chessBoard->whitePawns |= from;
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
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case knight:
                chessBoard->blackKnights |= moveTo;
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case bishop:
                chessBoard->blackBishops |= moveTo;
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case rook:
                chessBoard->blackRooks |= moveTo;
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case queen:
                chessBoard->blackQueens |= moveTo;
                chessBoard->blackPieces |= moveTo;
                chessBoard->allPieces |= moveTo;
                break;
            case 0:
                break;
        }
    }
}

void unMakeMove(ChessBoard* chessBoard, Move* move)
{
    revertMoveData(chessBoard);

    uint8_t piece = getPiece(*move);

    switch (piece)
    {
        case pawn:
            unMakePawnMove(chessBoard, move);
            break;
        case knight:
            unMakeKnightMove(chessBoard, move);
            break;
        case bishop:
            unMakeBishopMove(chessBoard, move);
            break;
        case rook:
            unMakeRookMove(chessBoard, move);
            break;
        case queen:
            unMakeQueenMove(chessBoard, move);
            break;
        case king:
            unMakeKingMove(chessBoard, move);
            break;
    }
    
    removeMovefromHistory(chessBoard);
}

void unMakeNullMove(ChessBoard* chessBoard)
{
    revertMoveData(chessBoard);
}