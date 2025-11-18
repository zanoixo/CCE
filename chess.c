#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WHITE 1
#define BLACK 0

#define Q 9
#define K 1000
#define R 5
#define N 3
#define B 3
#define P 1

#define PINDEX 0
#define NINDEX 1
#define BINDEX 2
#define RINDEX 3
#define QINDEX 4
#define KINDEX 5

#define MAXMOVEHIST 1024


void sendError(char errorMsg[]){

    printf("[ERROR]: %s\n", errorMsg);
    exit(1);
}

typedef struct move{

    int fromX;
    int fromY;
    int toX;
    int toY;
    int captured;
    char piece;

}move;

typedef struct chessPiece{

    char piece;
    int color;
    int value;
    int x;
    int y;

}chessPiece;


typedef struct chessBoard{

    chessPiece position[8][8];
    int turnPlayer;
    move *whitePossibleMoves[6];
    move *blackPossibleMoves[6];
    move moveHistory[MAXMOVEHIST];
    int moveHistoryCounter;

}chessBoard;

void showPosition(chessBoard board){

    for (int y = 0; y < 8; y++){

        for (int x = 0; x < 8; x++){

            printf("%c ", board.position[y][x].piece);
        }

        printf("\n");
    }
}

void showMoveHistory(chessBoard board){

    for(int i = 0; i < board.moveHistoryCounter; i++){

        printf("%c: from:(%d, %d), to:(%d, %d)\n",board.moveHistory[i].piece, board.moveHistory[i].fromX, board.moveHistory[i].fromY, board.moveHistory[i].toX, board.moveHistory[i].toY);
    }
}

void addMoveToHistory(chessBoard *board, move newMove){

    board->moveHistory[board->moveHistoryCounter] = newMove;
    board->moveHistoryCounter++;
    
}

void removeMoveFromHistory(chessBoard *board){

    board->moveHistoryCounter--;
    board->moveHistory[board->moveHistoryCounter].fromX = -1;
    
}

void makeMove(chessBoard *board, int fromX, int fromY, int toX, int toY) {

    board->position[toY][toX].piece = board->position[fromY][fromX].piece;
    board->position[toY][toX].color = board->position[fromY][fromX].color;
    board->position[toY][toX].value = board->position[fromY][fromX].value;

    board->position[fromY][fromX].piece = '0';
    board->position[fromY][fromX].color = 0;
    board->position[fromY][fromX].value = 0;

    board->turnPlayer ^= 1;

    move newMove = {fromX, fromY, toX, toY, -1, board->position[toY][toX].piece}; //TODO capture cheking and replace int args with move arg
    addMoveToHistory(board, newMove);
}

void showValue(chessBoard board){

    for (int y = 0; y < 8; y++){

        for (int x = 0; x < 8; x++){

            printf("%d ", board.position[y][x].value);
        }

        printf("\n");
    }
}

void setPiece(chessBoard *board, char name, int color, int value, int x, int y){

    board->position[y][x].piece = name;
    board->position[y][x].color = color;
    board->position[y][x].value = value;
    board->position[y][x].x = x;
    board->position[y][x].y = y;
}

void initializeMovesArrays(chessBoard board){
    
    int pawnMaxMoves = 12;
    int knightMaxMoves = 8;
    int bishopMaxMoves = 13;
    int rookMaxMoves = 14;
    int queenMaxMoves = 27;
    int kingMaxMoves = 9;

    int numOfPawns = 8;
    int numOfKnights = 2;
    int numOfBishops = 2;
    int numOfRooks = 2;
    int numOfQueens = 1;
    int numOfKings = 1;

    board.whitePossibleMoves[PINDEX] = malloc(sizeof(move) * pawnMaxMoves * numOfPawns + 1);
    board.whitePossibleMoves[NINDEX] = malloc(sizeof(move) * knightMaxMoves * numOfKnights + 1);
    board.whitePossibleMoves[BINDEX] = malloc(sizeof(move) * bishopMaxMoves * numOfBishops + 1);
    board.whitePossibleMoves[RINDEX] = malloc(sizeof(move) * rookMaxMoves * numOfRooks + 1);
    board.whitePossibleMoves[QINDEX] = malloc(sizeof(move) * queenMaxMoves * numOfQueens + 1);
    board.whitePossibleMoves[KINDEX] = malloc(sizeof(move) * kingMaxMoves * numOfKings + 1);

    board.blackPossibleMoves[PINDEX] = malloc(sizeof(move) * pawnMaxMoves * numOfPawns + 1);
    board.blackPossibleMoves[NINDEX] = malloc(sizeof(move) * knightMaxMoves * numOfKnights + 1);
    board.blackPossibleMoves[BINDEX] = malloc(sizeof(move) * bishopMaxMoves * numOfBishops + 1);
    board.blackPossibleMoves[RINDEX] = malloc(sizeof(move) * rookMaxMoves * numOfRooks + 1);
    board.blackPossibleMoves[QINDEX] = malloc(sizeof(move) * queenMaxMoves * numOfQueens + 1);
    board.blackPossibleMoves[KINDEX] = malloc(sizeof(move) * kingMaxMoves * numOfKings + 1);

}


chessBoard createPosition(char fileName[]){
    
    chessBoard board;
    char whoStarts[2];
    int pieceCounter = 0;

    FILE *positionFile = fopen(fileName, "r");

    if (positionFile == NULL){
        
        sendError("failed to open file");
    }

    fscanf(positionFile, "%s", whoStarts);

    if (whoStarts[0] != 'W' && whoStarts[0] != 'B'){
        
        sendError("Wrong format in file. First line needs to specify who starts 'B' or 'W'");   
    }

    if (whoStarts[0] == 'W'){
        
        board.turnPlayer = WHITE;
    }else {

        board.turnPlayer = BLACK;
    }
    

    while (!feof(positionFile)){

        char piece[3];
        char pieceName;
        int pieceValue;
        int pieceColor;
        int pieceX;
        int pieceY;

        fscanf(positionFile, "%s", piece);

        if (piece[0] == 'W'){

            pieceColor = WHITE;

        } else if (piece[0] == 'B'){

            pieceColor = BLACK;

        }else {

            pieceColor = -1;
        }

        pieceName = piece[1];

        switch (pieceName){

        case 'Q': pieceValue = Q; break;
        case 'R': pieceValue = R; break;
        case 'B': pieceValue = B; break;
        case 'N': pieceValue = N; break;
        case 'P': pieceValue = P; break;
        case 'K': pieceValue = K; break;
        case '0': pieceValue = 0; break;
        default: sendError("Wrong format in file");   

        }

        pieceValue = pieceColor * pieceValue;
        pieceX = pieceCounter % 8;
        pieceY = pieceCounter / 8;

        setPiece(&board, pieceName, pieceColor, pieceValue, pieceX, pieceY);

        pieceCounter++;

    }
    
    initializeMovesArrays(board);

    return board;
    
}

int main(int argc, char const *argv[]){

    chessBoard startingPosition = createPosition("startingPosition.txt");

    showPosition(startingPosition);
    showMoveHistory(startingPosition);
    

    return 0;
}
