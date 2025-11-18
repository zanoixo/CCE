#include "chessStructs.h"

#ifndef CHESSFUNCSH

void showPosition(chessBoard board);
void showValue(chessBoard board);

void showMoveHistory(chessBoard board);
void addMoveToHistory(chessBoard *board, move newMove);
void removeMoveFromHistory(chessBoard *board);

void setPiece(chessBoard *board, char name, int color, int value, int x, int y);
move **initializeMovesArrays(chessBoard board);
chessBoard createPosition(char fileName[]);

void makeMove(chessBoard *board, int fromX, int fromY, int toX, int toY);


#endif