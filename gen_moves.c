// Generates possible moves for the current position.
#include "gen_moves.h"
#include "board_io.h"

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

bitboard gm_rook(bitboard sq, chessboard board)
{
    bitboard w_peices = board.wp | board.wr | board.wn | board.wb | board.wq | board.wk;
    bitboard b_peices = board.bp | board.br | board.bn | board.bb | board.bq | board.bk;
    bitboard all_peices = w_peices | b_peices;

    // Calculating horizontal moves
    byte index = get_index(sq); // Index of the current square
    byte rank = index % 8;      //getting rank index of rook
    byte file = index / 8;      //getting file of rook

    byte blocker_rank = (all_peices & ~sq) >> (rank * 8);
    byte b_rank = (b_peices & ~sq) >> (rank * 8);

    byte left_map = 0xFF >> (file + 1);
    byte l_blockers = left_map & blocker_rank;
    byte r_blockers = ~left_map & blocker_rank;
    byte l_blocker = highest_bit(l_blockers);
    byte r_blocker = lowest_bit(r_blockers);
    byte moves = ~((l_blocker << 1) - 1) & left_map | (r_blocker - 1) & ~left_map;

    print_bitboard((moves | b_rank) << rank * 8, true);

    //printf("%d %d\n", right_blockers, rank * 8);
    return 0;
}