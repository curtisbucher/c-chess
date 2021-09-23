//#include "chessboard.h"

#define DARK_BACKGROUND "\x1B[44m"
#define LIGHT_BACKGROUND "\x1B[46m"
#define NORMAL_BACKGROUND "\x1B[0m"

#define DARK_TEXT "\x1B[30m"
#define LIGHT_TEXT "\x1B[37m"

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void print_header(void);
void clear_screen(void);
void print_board(const chessboard board, bool wtp);
const char *bitboard_to_FEN(chessboard board);
chessboard FEN_to_board(const char *fen);
void print_bitboard(bitboard b, bool wtp);
move get_move_input(chessboard board, bool wtm);

#endif