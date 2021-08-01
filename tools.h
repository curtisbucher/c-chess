#include "chessboard.h"
#include <time.h>

typedef unsigned char byte;
int rev_byte(byte n);
int pop_cnt(bitboard n);
int lowest_bit(bitboard n);
int highest_bit(bitboard n);
int get_index(bitboard n);
bitboard gen_shift(bitboard n, int s);
bitboard hor_mirror_board(bitboard b);
bitboard vert_mirror_board(bitboard b);
bitboard rot_board(bitboard b);
double timeit(void (*f)(), int n);