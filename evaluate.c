#include "chessboard.h"
#include "tools.h"

// Relative Piece Values
#define p_val (1)
#define r_val (5)
#define n_val (3)
#define b_val (3)
#define q_val (9)
#define k_val (100)

/**
 * @brief Main board evaluation function
 * @param board Chessboard to evaluate
 * @param color Color of the player to evaluate
 * @return Evaluation score
**/
move
evaluate(chessboard board) {
    int score = 0;
    score +=  pop_cnt(board.wp) * p_val
            + pop_cnt(board.wn) * n_val
            + pop_cnt(board.wb) * b_val
            + pop_cnt(board.wr) * r_val
            + pop_cnt(board.wq) * q_val
            + pop_cnt(board.wk) * k_val
            - pop_cnt(board.bp) * p_val
            - pop_cnt(board.bn) * n_val
            - pop_cnt(board.bb) * b_val
            - pop_cnt(board.br) * r_val
            - pop_cnt(board.bq) * q_val
            - pop_cnt(board.bk) * k_val;
    return score;
}