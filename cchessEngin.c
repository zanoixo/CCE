#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chessFuncs.h"
#include "chessStructs.h"

int pawnMoveCounter = 0;
int knightMoveCounter = 0;
int bishopMoveCounter = 0;
int rookMoveCounter = 0;
int queenMoveCounter = 0;
int kingMoveCounter = 0;

move *generatePawnMoves(chessBoard board, move **playableMoves, int x, int y){
    
    return playableMoves[PINDEX];
}

move *generateKnightMoves(chessBoard board, move **playableMoves, int x, int y){

    return playableMoves[NINDEX];
}

move *generateBishopMoves(chessBoard board, move **playableMoves, int x, int y){

    return playableMoves[BINDEX];
}

move *generateRookMoves(chessBoard board, move **playableMoves, int x, int y){

    return playableMoves[RINDEX];
}

move *generateQueenMoves(chessBoard board, move **playableMoves, int x, int y){

    return playableMoves[QINDEX];
}

move *generateKingMoves(chessBoard board, move **playableMoves, int x, int y){

    return playableMoves[KINDEX];
}

move **generateMoves(chessBoard board, move **availableMoves){

    move **playableMoves = initializeMovesArrays(board);

    for (int y = 0; y < 8; y++){

        for (int x = 0; x < 8; x++){
            
            switch (board.position[y][x].piece){

                case '0': break;
                case 'P': generatePawnMoves(board, playableMoves, x, y); break;
                case 'N': generateKnightMoves(board, playableMoves, x, y); break;
                case 'B': generateBishopMoves(board, playableMoves, x, y); break;
                case 'R': generateRookMoves(board, playableMoves, x, y); break;
                case 'Q': generateQueenMoves(board, playableMoves, x, y); break;
                case 'K': generateKingMoves(board, playableMoves, x, y); break;
            }

        }

    }
    
    return playableMoves;
}

int main(int argc, char const *argv[]){
    
    chessBoard startingPosition = createPosition("startingPosition.txt");
    
    makeMove(&startingPosition, 0, 1, 0, 3);
    showPosition(startingPosition);
    initializeMovesArrays(startingPosition);

    return 0;
}
