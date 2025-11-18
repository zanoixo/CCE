#ifndef CHESSSTRUCTSH

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
    move **moves;
    move moveHistory[MAXMOVEHIST];
    int moveHistoryCounter;

}chessBoard;

#endif