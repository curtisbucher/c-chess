#include "chessboard.h"

enum peices
{
    EMPTY,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};
static int peice_values[8] = {0, 100, 300, 300, 500, 900, 100000000}; //in centi-pawns

int score_board(chessboard board);