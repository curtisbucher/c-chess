#include "chessboard.h"
#include "engine.h"
#include "evaluate.h"
#include "gen_moves.h"

#include "tools.h"
#include "board_io.h"
#include <time.h>

#define MAX_MOVES (116)

unsigned long position_count = 0;
/**
 * @brief Main engine function. Returns best move through alpha-beta search tree.
 * @param board The current chessboard to calculate the best move for.
 * @param wtm (True) white to move, (false) black to move
 * @note https://en.wikipedia.org/wiki/Alpha–beta_pruning
 * @return The best move.
**/
move
get_best_move(chessboard board, bool wtm)
{
    move moves[116];
    int num_moves = gen_moves(board, moves, wtm);

    int max_score = INT32_MIN;
    int max_score_index = -1;
    int score = 0;

    double start_time = clock();
    for (int i = 0; i < num_moves; i++){

        board = apply_move(board, moves[i], wtm);
        score = alpha_beta_max(INT32_MIN, INT32_MAX, 5, board, !wtm);
        board = apply_move(board, moves[i], wtm);

        if (score > max_score){
            max_score = score;
            max_score_index = i;
        }
        IF_DEBUG(print_progress(i, num_moves, position_count, ((double)(clock() - start_time)) / CLOCKS_PER_SEC, 20));
    }
    IF_DEBUG(printf("\n\n\n\n"));
    IF_DEBUG(printf("Move Score: %d\n", max_score));
    position_count = 0;
    return moves[max_score_index];
}

int
alpha_beta_max(int alpha, int beta, int depth_left, chessboard board, bool wtm)
{
    position_count++;
    if(depth_left == 0) return evaluate(board, WHITE);
    move moves[MAX_MOVES];
    int num_moves = gen_moves(board, moves, wtm);
    int score = 0;

    for(int i = 0; i < num_moves; i++){

        board = apply_move(board, moves[i], wtm);
        score = alpha_beta_min(alpha, beta, depth_left - 1, board, !wtm);
        board = apply_move(board, moves[i], wtm);

        // Fail hard beta-cutoff
        if(score >= beta)
            return beta;

        if(score > alpha)
            alpha = score;
    }
    return alpha;
}

int
alpha_beta_min(int alpha, int beta, int depth_left, chessboard board, bool wtm){
    position_count++;
    if(depth_left == 0) return -evaluate(board, WHITE);
    move moves[MAX_MOVES];
    int num_moves = gen_moves(board, moves, wtm);
    int score = 0;

    for(int i = 0; i < num_moves; i++){
        board = apply_move(board, moves[i], wtm);
        score = alpha_beta_max(alpha, beta, depth_left - 1, board, !wtm);
        board = apply_move(board, moves[i], wtm);
        // Fail hard alpha-cutoff
        if(score <= alpha)
            return alpha;

        if(score < beta)
            beta = score;
    }
    return beta;
}