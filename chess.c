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
    chessboard board = EMPTY_BOARD;
    board.wq = D4;
    bitboard moves[40];

    int num_moves = gen_moves(board, moves);

    for (int i = 0; i < num_moves; i++)
    {
        print_bitboard(moves[i], true);
    }

    print_board(board, true);

    //printf("%f\n", timeit(test_time, 10000));

    return 0;
}
