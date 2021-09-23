#include "chessboard.h"
#include "engine.h"
#include "evaluate.h"
#include "gen_moves.h"

#include "tools.h"

/**
 * @brief Main engine function. Returns best move through alpha-beta search tree.
 * @param board The current chessboard to calculate the best move for.
 * @param wtm (True) white to move, (false) black to move
 * @return The best move.
**/
move
calc_best_move(chessboard board, bool wtm){
    move moves[116];
    int num_moves = gen_moves(board, moves, wtm);

    int max_score = INT32_MIN;
    int max_score_index = -1;
    int score = 0;

    for (int i = 0; i < num_moves; i++){

        board = apply_move(board, moves[i], wtm);
        score = evaluate(board, wtm);
        board = apply_move(board, moves[i], wtm);

        if (score > max_score){
            max_score = score;
            max_score_index = i;
        }
    }
    IF_DEBUG(printf("Move Score: %d\n", max_score));
    return moves[max_score_index];
}