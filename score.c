#include "score.h"
#include "tools.h"

int score_board(chessboard board)
{
    // Simple algorithm for now, count the number of pieces on the board, and apply standard peice values
    int score = pop_cnt(board.wp) * peice_values[PAWN] +
                pop_cnt(board.wr) * peice_values[ROOK] +
                pop_cnt(board.wn) * peice_values[KNIGHT] +
                pop_cnt(board.wb) * peice_values[BISHOP] +
                pop_cnt(board.wq) * peice_values[QUEEN] +
                pop_cnt(board.wk) * peice_values[KING];
    return score;
}