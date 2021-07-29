#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "chessboard.h"
#include "board_io.h"
#include "startingboard.h"
#include "score.h"

#include "tools.h"

void test_time(void)
{
    score_board(STARTING_BOARD);
}

int main()
{
    printf("%f\n", timeit(test_time, 1000000));
    //printf("%i\n", score_board(STARTING_BOARD));
    //printf("%d\n", score_board_2(STARTING_BOARD));
    return 0;
}
