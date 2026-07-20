#include "ChessBitboards.h"

//FILES

const uint64_t aFile = 0b00000001ULL << 56 |
                       0b00000001ULL << 48 |
                       0b00000001ULL << 40 |
                       0b00000001ULL << 32 |
                       0b00000001ULL << 24 |
                       0b00000001ULL << 16 |
                       0b00000001ULL << 8  |
                       0b00000001ULL;

const uint64_t bFile = 0b00000010ULL << 56 |
                       0b00000010ULL << 48 |
                       0b00000010ULL << 40 |
                       0b00000010ULL << 32 |
                       0b00000010ULL << 24 |
                       0b00000010ULL << 16 |
                       0b00000010ULL << 8  |
                       0b00000010ULL;

const uint64_t cFile = 0b00000100ULL << 56 |
                       0b00000100ULL << 48 |
                       0b00000100ULL << 40 |
                       0b00000100ULL << 32 |
                       0b00000100ULL << 24 |
                       0b00000100ULL << 16 |
                       0b00000100ULL << 8  |
                       0b00000100ULL; 

const uint64_t dFile = 0b00001000ULL << 56 |
                       0b00001000ULL << 48 |
                       0b00001000ULL << 40 |
                       0b00001000ULL << 32 |
                       0b00001000ULL << 24 |
                       0b00001000ULL << 16 |
                       0b00001000ULL << 8  |
                       0b00001000ULL;
                       
const uint64_t eFile = 0b00010000ULL << 56 |
                       0b00010000ULL << 48 |
                       0b00010000ULL << 40 |
                       0b00010000ULL << 32 |
                       0b00010000ULL << 24 |
                       0b00010000ULL << 16 |
                       0b00010000ULL << 8  |
                       0b00010000ULL;
                       

const uint64_t fFile = 0b00100000ULL << 56 |
                       0b00100000ULL << 48 |
                       0b00100000ULL << 40 |
                       0b00100000ULL << 32 |
                       0b00100000ULL << 24 |
                       0b00100000ULL << 16 |
                       0b00100000ULL << 8  |
                       0b00100000ULL;

const uint64_t gFile = 0b01000000ULL << 56 |
                       0b01000000ULL << 48 |
                       0b01000000ULL << 40 |
                       0b01000000ULL << 32 |
                       0b01000000ULL << 24 |
                       0b01000000ULL << 16 |
                       0b01000000ULL << 8  |
                       0b01000000ULL;

const uint64_t hFile = 0b10000000ULL << 56 |
                       0b10000000ULL << 48 |
                       0b10000000ULL << 40 |
                       0b10000000ULL << 32 |
                       0b10000000ULL << 24 |
                       0b10000000ULL << 16 |
                       0b10000000ULL << 8  |
                       0b10000000ULL;


//LINES

const uint64_t line1 = 0b00000000ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b11111111ULL;

const uint64_t line2 = 0b00000000ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b11111111ULL << 8  |
                       0b00000000ULL;

const uint64_t line3 = 0b00000000ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b11111111ULL << 16 |
                       0b00000000ULL << 8  |
                       0b00000000ULL;
            
const uint64_t line4 = 0b00000000ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b11111111ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b00000000ULL;

const uint64_t line5 = 0b00000000ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b11111111ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b00000000ULL;

const uint64_t line6 = 0b00000000ULL << 56 |
                       0b00000000ULL << 48 |
                       0b11111111ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b00000000ULL;

const uint64_t line7 = 0b00000000ULL << 56 |
                       0b11111111ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b00000000ULL;

const uint64_t line8 = 0b11111111ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b00000000ULL;


//CASTLE BITBOARDS

const uint64_t whiteKingSideInnerPawnShield = 0b00000000ULL << 56 |
                                              0b00000000ULL << 48 |
                                              0b00000000ULL << 40 |
                                              0b00000000ULL << 32 |
                                              0b00000000ULL << 24 |
                                              0b00000000ULL << 16 |
                                              0b11100000ULL << 8  |
                                              0b00000000ULL;

const uint64_t whiteKingSideOuterPawnShield = 0b00000000ULL << 56 |
                                              0b00000000ULL << 48 |
                                              0b00000000ULL << 40 |
                                              0b00000000ULL << 32 |
                                              0b00000000ULL << 24 |
                                              0b11100000ULL << 16 |
                                              0b00000000ULL << 8  |
                                              0b00000000ULL;

const uint64_t whiteKingSideCastleSquares = 0b00000000ULL << 56 |
                                            0b00000000ULL << 48 |
                                            0b00000000ULL << 40 |
                                            0b00000000ULL << 32 |
                                            0b00000000ULL << 24 |
                                            0b00000000ULL << 16 |
                                            0b11100000ULL << 8  |
                                            0b11100000ULL;
                                
const uint64_t whiteQueenSideInnerPawnShield = 0b00000000ULL << 56 |
                                               0b00000000ULL << 48 |
                                               0b00000000ULL << 40 |
                                               0b00000000ULL << 32 |
                                               0b00000000ULL << 24 |
                                               0b00000000ULL << 16 |
                                               0b00001110ULL << 8  |
                                               0b00000000ULL;

const uint64_t whiteQueenSideOuterPawnShield = 0b00000000ULL << 56 |
                                               0b00000000ULL << 48 |
                                               0b00000000ULL << 40 |
                                               0b00000000ULL << 32 |
                                               0b00000000ULL << 24 |
                                               0b00001110ULL << 16 |
                                               0b00000000ULL << 8  |
                                               0b00000000ULL;

const uint64_t whiteQueenSideCastleSquares = 0b00000000ULL << 56 |
                                             0b00000000ULL << 48 |
                                             0b00000000ULL << 40 |
                                             0b00000000ULL << 32 |
                                             0b00000000ULL << 24 |
                                             0b00000000ULL << 16 |
                                             0b00001111ULL << 8  |
                                             0b00001111ULL;

const uint64_t blackKingSideInnerPawnShield = 0b00000000ULL << 56 |
                                              0b11100000ULL << 48 |
                                              0b00000000ULL << 40 |
                                              0b00000000ULL << 32 |
                                              0b00000000ULL << 24 |
                                              0b00000000ULL << 16 |
                                              0b00000000ULL << 8  |
                                              0b00000000ULL;

const uint64_t blackKingSideOuterPawnShield = 0b00000000ULL << 56 |
                                              0b00000000ULL << 48 |
                                              0b11100000ULL << 40 |
                                              0b00000000ULL << 32 |
                                              0b00000000ULL << 24 |
                                              0b00000000ULL << 16 |
                                              0b00000000ULL << 8  |
                                              0b00000000ULL;

const uint64_t blackKingSideCastleSquares = 0b11100000ULL << 56 |
                                            0b11100000ULL << 48 |
                                            0b00000000ULL << 40 |
                                            0b00000000ULL << 32 |
                                            0b00000000ULL << 24 |
                                            0b00000000ULL << 16 |
                                            0b00000000ULL << 8  |
                                            0b00000000ULL;
                                
const uint64_t blackQueenSideInnerPawnShield = 0b00000000ULL << 56 |
                                               0b00001110ULL << 48 |
                                               0b00000000ULL << 40 |
                                               0b00000000ULL << 32 |
                                               0b00000000ULL << 24 |
                                               0b00000000ULL << 16 |
                                               0b00000000ULL << 8  |
                                               0b00000000ULL;

const uint64_t blackQueenSideOuterPawnShield = 0b00000000ULL << 56 |
                                               0b00000000ULL << 48 |
                                               0b00001110ULL << 40 |
                                               0b00000000ULL << 32 |
                                               0b00000000ULL << 24 |
                                               0b00000000ULL << 16 |
                                               0b00000000ULL << 8  |
                                               0b00000000ULL;

const uint64_t blackQueenSideCastleSquares = 0b00001111ULL << 56 |
                                             0b00001111ULL << 48 |
                                             0b00000000ULL << 40 |
                                             0b00000000ULL << 32 |
                                             0b00000000ULL << 24 |
                                             0b00000000ULL << 16 |
                                             0b00000000ULL << 8  |
                                             0b00000000ULL;

//NEEDED SQUARES

const uint64_t e1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00010000ULL; 

const uint64_t e8 = 0b00010000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL;

const uint64_t a1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000001ULL; 

const uint64_t b1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000010ULL; 

const uint64_t c1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000100ULL; 

const uint64_t d1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00001000ULL; 

const uint64_t f1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00100000ULL; 

const uint64_t g1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b01000000ULL;
                    
const uint64_t h1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b10000000ULL; 

const uint64_t a8 = 0b00000001ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t b8 = 0b00000010ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t c8 = 0b00000100ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t d8 = 0b00001000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t f8 = 0b00100000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t g8 = 0b01000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL;
                
const uint64_t h8 = 0b10000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 
