// Generates possible moves for the current position.
#include "gen_moves.h"

bitboard gm_w_pawn(bitboard sq, chessboard board)
{
    bitboard w_peices = board.wp | board.wr | board.wn | board.wb | board.wq | board.wk;
    bitboard b_peices = board.bp | board.br | board.bn | board.bb | board.bq | board.bk;
    bitboard all_peices = w_peices | b_peices;

    bitboard moves = (sq << 8 & ~all_peices) |                               //T
                     (sq << 9 & b_peices) |                                  //TL if black peice
                     (sq << 7 & b_peices) |                                  //TR if black peice
                     (sq << 16 & ~all_peices & ~(all_peices << 8)) & RANK_4; //TT if Rank 2
    return moves;
}

bitboard gm_b_pawn(bitboard sq, chessboard board)
{
    bitboard w_peices = board.wp | board.wr | board.wn | board.wb | board.wq | board.wk;
    bitboard b_peices = board.bp | board.br | board.bn | board.bb | board.bq | board.bk;
    bitboard all_peices = w_peices | b_peices;

    bitboard moves = (sq >> 8 & ~all_peices) |                               //T
                     (sq >> 9 & w_peices) |                                  //TL if black peice
                     (sq >> 7 & w_peices) |                                  //TR if black peice
                     (sq >> 16 & ~all_peices & ~(all_peices >> 8)) & RANK_5; //TT if Rank 2
    return moves;
}