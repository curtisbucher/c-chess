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

    // Horizontal moves
    byte occupied = all_peices >> (rank * 8);
    byte slider = sq >> (rank * 8);

    byte rev_occupied = rev_byte(occupied);
    byte rev_slider = rev_byte(slider);

    byte r_moves = occupied ^ (occupied - (slider << 1)); // can be mostly parralleized
    byte l_moves = rev_byte(rev_occupied ^ (rev_occupied - (rev_slider << 1)));
    byte moves = (r_moves | l_moves) & ~(w_peices >> (rank * 8)); // can be parralleized

    //Vertical moves

    print_bitboard(moves, true);

    //printf("%d %d\n", right_blockers, rank * 8);
    return 0;
}

// byte calc(bitboard bb, byte index`)