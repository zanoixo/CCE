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
    uint8_t isBlacksMove = isBlack(chessBoard);
    uint8_t promotion = getPromotionPiece(*move);

    uint64_t from = getFromBitboard(move->move);
    uint64_t to = getToBitboard(move->move);

    uint8_t fromSq = getSqInd(from);
    uint8_t toSq = getSqInd(to);
    
    uint64_t moveTo = to;

    uint8_t moveToSq = getSqInd(moveTo);

    uint8_t capture = getPieceFromSquare(toSq, chessBoard);

    moveData->movedPiece = chessBoard->pieceLookup[fromSq];

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