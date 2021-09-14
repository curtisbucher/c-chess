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
    int num_moves = gen_moves(STARTING_BOARD, moves, 0);
}

int main()
{
    //Initializing random generator
    time_t t;
    srand((unsigned)time(&t));

    chessboard board = STARTING_BOARD;
    bitboard moves[116]; //naive max number of moves is 116
    move m = 0;
    move m_player = 0;
    int num_moves;
    bool exit = false;

    while (!exit)
    {
        //WHITE's turn
        printf("\e[1;1H\e[2J");
        print_board(board, board.wtm);
        while (!m_player)
            m_player = get_move_input(board, board.wtm);

        if (m_player == 0xFFFFFFFFFFFFFFFF)
            return 0;

        board = apply_move(board, m_player, board.wtm);
        board.wtm = !board.wtm;
        board.halfmove++;
        board.fullmove++;
        m_player = 0;

        //BLACK's turn
        num_moves = gen_moves(board, moves, board.wtm);
        m = moves[rand() % num_moves];

        board = apply_move(board, m, board.wtm);

        board.wtm = !board.wtm;
        board.halfmove++;
        board.fullmove++;
    }

    return 0;
}
