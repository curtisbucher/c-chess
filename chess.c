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
    board.wr = D4;
    board.bp = B4;
    board.wp = G4;
    board.bk = D5;

    board.wk = gm_rook(D4, board);
    // board.bp |= C7;
    // board.wp |= D6;
    // board.wp |= B6;

    // board.wk |= gm_b_pawn(C7, board);

    print_board(board, true);
    // printf("\n%s", bitboard_to_FEN(board));
    //gm_rook(C7, board);

    //printf("%f\n", timeit(test_time, 10000));

    return 0;
}
