#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "chessboard.h"
#include "board_io.h"
#include "score.h"
#include "gen_moves.h"

#include "tools.h"

void test_time(void)
{
    get_index(16777216L);
}

int main()
{
    chessboard board = STARTING_BOARD;
    bitboard moves[40];

    gen_moves(board, moves);

    print_board(board, true);

    //printf("%f\n", timeit(test_time, 10000));

    return 0;
}
