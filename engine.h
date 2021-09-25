#include "chessboard.h"

#ifndef engine_h
#define engine_h

move get_best_move(chessboard board, bool wtm);
int alpha_beta_max(int alpha, int beta, int depth_left, chessboard board, bool wtm);
int alpha_beta_min(int alpha, int beta, int depth_left, chessboard board, bool wtm);
move calc_best_move(chessboard board, bool wtm);

#endif