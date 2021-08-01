#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "chessboard.h"
#include "board_io.h"
#include "score.h"
#include "gen_moves.h"

#include "tools.h"

bitboard moves[40];

void test_time(void)
{
    gen_moves(STARTING_BOARD, moves, 0);
}

int main()
{
    // Initializing random generator
    time_t t;
    srand((unsigned)time(&t));

    chessboard board = STARTING_BOARD;
    bitboard moves[40];
    board.wtm = WHITE;

    int num_moves = gen_moves(board, moves, board.wtm);

    bitboard move = moves[rand() % num_moves];

    print_board(board, board.wtm);

    // Applying move
    if (move & board.wp)
        board.wp ^= move;
    else if (move & board.wr)
        board.wr ^= move;
    else if (move & board.wb)
        board.wb ^= move;
    else if (move & board.wn)
        board.wn ^= move;
    else if (move & board.wq)
        board.wq ^= move;
    else if (move & board.wk)
        board.wk ^= move;

    // Removing taken peices
    board.bp &= ~move;
    board.br &= ~move;
    board.bn &= ~move;
    board.bb &= ~move;
    board.bq &= ~move;
    board.bk &= ~move;

    print_board(board, board.wtm);

    // printf("%f\n", timeit(test_time, 10000));

    return 0;
}
