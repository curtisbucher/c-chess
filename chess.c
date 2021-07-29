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
    score_board(STARTING_BOARD);
}

int main()
{
    chessboard board = STARTING_BOARD;
    board.bp |= C7;
    board.wp |= D6;
    board.wp |= B6;

    board.wk |= gm_b_pawn(C7, board);

    print_board(board, false);
    printf("\n%s", bitboard_to_FEN(board));

    return 0;
}
