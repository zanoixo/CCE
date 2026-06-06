#include <stdio.h>
#include "ChessBoard.h"
#include "ChessMoveGenerator.h"
#include "ChessTests.h"

int userMove(char* from, char* to, char promotion, ChessBoard* chessBoard, AttackTables* attackTables)
{
    uint16_t promotionFlag = 0;

    uint8_t fromFile = from[0] - 'a';
    uint8_t fromRank = from[1] - '1';

    uint8_t toFile = to[0] - 'a';
    uint8_t toRank = to[1] - '1';

    uint8_t fromSq = fromRank * 8 + fromFile;
    uint8_t toSq = toRank * 8 + toFile;

    uint64_t fromBitboard = 1ULL << fromSq;
    uint64_t toBitboard = 1ULL << toSq;

    switch (promotion)
    {
        case 'q':
            promotionFlag |= queenPromotion;
            break;
        case 'r':
            promotionFlag |= rookPromotion;
            break;
        case 'k':
            promotionFlag |= knightPromotion;
            break;
        case 'b':
            promotionFlag |= bishopPromotion;
            break;
        case 'x':
            break;
        default:
            return 0;
    }

    MoveList* moveList = malloc(sizeof(MoveList));
    moveList->moves = malloc(sizeof(Move) * 256);
    moveList->nextIndex = 0;

    Move *playedMove = NULL;

    generateMoves(chessBoard, attackTables, moveList);

    for (int i = 0; i < moveList->nextIndex; i++)
    {
        if (fromBitboard == moveList->moves[i].from && toBitboard == moveList->moves[i].to && promotionFlag == (moveList->moves[i].flags & promotionPieceMask))
        {
            playedMove = &moveList->moves[i];
            break;
        }
            
    }

    if (playedMove == NULL)
    {
        free(moveList->moves);
        free(moveList);
        return 0;   
    }
    

    makeMove(chessBoard, playedMove);

    free(moveList->moves);
    free(moveList);

    return 1;
}

int main()
{
    ChessBoard *chessBoard = initChessBoard();
    AttackTables* attackTables = initAttackTables();
    chessBoard->flags = whiteShortCastleMask | whiteLongCastleMask | blackShortCastleMask | blackLongCastleMask;

    char fileName[] = "startingPosition.txt";

    createPosition(fileName, chessBoard);

    //runAllTests();

    while(1)
    {
        char from[3];
        char to[3];
        char promotion;

        printf("from: ");
        scanf("%2s", from);

        printf("to: ");
        scanf("%2s", to);

        printf("promotion piece (q/r/b/n, enter x if none): ");
        scanf(" %c", &promotion); 
        
        int isMoveValid = userMove(from, to, promotion, chessBoard, attackTables);

        if (!isMoveValid)
        {
            printf("Invalid move\n");
        }

        showPosition(chessBoard);
        
    }

    return 0;
}