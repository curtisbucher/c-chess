//#include "chessboard.h"

#define DARK_BACKGROUND "\x1B[100m"
#define LIGHT_BACKGROUND "\x1B[47m"
#define NORMAL_BACKGROUND "\x1B[0m"

#define DARK_TEXT "\x1B[30m"
#define LIGHT_TEXT "\x1B[37m"

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void print_board(const chessboard board);
const char *bitboard_to_FEN(chessboard board);
chessboard FEN_to_board(const char *fen);

#endif