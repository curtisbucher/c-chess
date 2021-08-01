// Generates possible moves for the current position.
#include "gen_moves.h"
#include "board_io.h"

// Generate all possible moves for the current position. A move is represented as two bits active on a bitboard.
int gen_moves(chessboard board, bitboard *moves)
{
    bitboard w_pieces = board.wp | board.wr | board.wn | board.wb | board.wq | board.wk;
    bitboard b_pieces = board.bp | board.br | board.bn | board.bb | board.bq | board.bk;
    bitboard occupied = w_pieces | b_pieces;

    int i = 0;

    // White Pawns
    mask wp[8];
    int num_pieces = bitboard_to_mask(board.wp, wp, 8);

    mask wp_moves[3];
    int num_moves;
    // for each white pawn
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_w_pawn(wp[p], occupied, b_pieces), wp_moves, 3);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = wp[p] | wp_moves[m];
        }
    }

    // Rooks
    mask wr[2];
    num_pieces = bitboard_to_mask(board.wr, wr, 2);

    mask r_moves[14];
    // for each rook
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_rook(wr[p], occupied, w_pieces), r_moves, 14);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = wr[p] | r_moves[m];
        }
    }

    // Bishops
    mask bish[2];
    num_pieces = bitboard_to_mask(board.wb, bish, 2);

    mask bish_moves[14];
    // for each bishop
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_bishop(bish[p], occupied, w_pieces), bish_moves, 14);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = bish[p] | bish_moves[m];
        }
    }

    // Queens
    mask qn[2];
    num_pieces = bitboard_to_mask(board.wq, qn, 2);

    mask qn_moves[28];
    // for each queen
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_queen(qn[p], occupied, w_pieces), qn_moves, 28);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = qn[p] | qn_moves[m];
        }
    }

    // Knight
    mask kn[2];
    num_pieces = bitboard_to_mask(board.wn, kn, 2);

    mask kn_moves[4];
    // for each king
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_knight(kn[p], w_pieces), kn_moves, 4);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = kn[p] | kn_moves[m];
        }
    }

    return i;
}

bitboard
gm_w_pawn(bitboard sq, bitboard occupied, bitboard b_pieces)
{

    bitboard moves = (sq << 8 & ~occupied) |
                     (sq << 9 & b_pieces) |
                     (sq << 7 & b_pieces) |
                     (sq << 16 & ~occupied & ~(occupied << 8)) & RANK_4;
    return moves;
}

bitboard
gm_b_pawn(bitboard sq, bitboard occupied, bitboard w_pieces)
{
    bitboard moves = (sq >> 8 & ~occupied) |
                     (sq >> 9 & w_pieces) |
                     (sq >> 7 & w_pieces) |
                     (sq >> 16 & ~occupied & ~(occupied >> 8)) & RANK_5;
    return moves;
}

// TODO: Include checks for castling. Too slow.
bitboard
gm_rook(bitboard sq, bitboard occupied, bitboard w_pieces)
{
    // Calculating horizontal moves
    byte index = get_index(sq); // Index of the current square
    byte file = index % 8;      // getting rank index of rook
    byte rank = index / 8;      // getting file of rook

    bitboard hor_filemask = gen_shift(RANK_1, (rank * 8));
    bitboard vert_filemask = gen_shift(FILE_A, file);

    // Positive horizontal
    bitboard hor_pos_moves = gm_pos_slider(sq, occupied, w_pieces, hor_filemask);

    //Positive vertical
    bitboard vert_pos_moves = gm_pos_slider(sq, occupied, w_pieces, vert_filemask);

    // Negative Horizontal
    bitboard hor_neg_moves =
        hor_mirror_board(
            gm_pos_slider(
                hor_mirror_board(sq),
                hor_mirror_board(occupied),
                hor_mirror_board(w_pieces),
                hor_filemask));

    // Negative Vertical
    bitboard vert_neg_moves =
        vert_mirror_board(
            gm_pos_slider(
                vert_mirror_board(sq),
                vert_mirror_board(occupied),
                vert_mirror_board(w_pieces),
                vert_filemask));

    bitboard moves = (hor_pos_moves | vert_pos_moves | hor_neg_moves | vert_neg_moves);
    return moves;
}

// TODO: Too slow.
bitboard
gm_bishop(bitboard sq, bitboard occupied, bitboard w_pieces)
{
    // Calculating horizontal moves
    byte index = get_index(sq); // Index of the current square
    byte file = index % 8;      //getting rank index of rook
    byte rank = index / 8;      //getting file of rook

    bitboard diag_filemask = gen_shift(DIAGONAL, (file - rank)) & gen_shift(0xFFFFFFFFFFFFFFFF, -(8 * (file - rank)));
    bitboard anti_filemask = gen_shift(ANTIDIAGONAL, -(7 - rank - file)) & ((rank > 4) ? UR_TRIANGLE : ~UR_TRIANGLE);

    // Rotating the boards
    bitboard rot_sq = rot_board(sq);
    bitboard rot_occupied = rot_board(occupied);
    bitboard rot_w_pieces = rot_board(w_pieces);
    bitboard rot_diag_filemask = rot_board(diag_filemask);
    bitboard rot_anti_filemask = rot_board(anti_filemask);

    // Positive diagonal
    bitboard diag_pos_moves = gm_pos_slider(sq, occupied, w_pieces, diag_filemask);

    //Positive antidiagonal
    bitboard anti_pos_moves = gm_pos_slider(sq, occupied, w_pieces, anti_filemask);

    // Negative diagonal
    bitboard diag_neg_moves = rot_board(
        gm_pos_slider(rot_sq, rot_occupied, rot_w_pieces, rot_diag_filemask));

    // Negative antidiagonal
    bitboard anti_neg_moves = rot_board(
        gm_pos_slider(rot_sq, rot_occupied, rot_w_pieces, rot_anti_filemask));

    bitboard moves = (diag_pos_moves | diag_neg_moves | anti_pos_moves | anti_neg_moves);

    return moves;
}

bitboard
gm_queen(bitboard sq, bitboard occupied, bitboard w_pieces)
{
    bitboard moves = gm_rook(sq, occupied, w_pieces) | gm_bishop(sq, occupied, w_pieces);
    return moves;
}

bitboard
gm_knight(bitboard sq, bitboard w_pieces)
{
    int index = get_index(sq);
    int rank = index / 8;
    unsigned long rank_mask = (RANK_1 << (rank * 8));

    bitboard moves = (sq << 17 | sq << 15) & (rank_mask << 16) | //Up two
                     (sq >> 17 | sq >> 15) & (rank_mask >> 16) | //Down two
                     (sq << 10 | sq << 6) & (rank_mask << 8) |   //Up one
                     (sq >> 10 | sq >> 6) & (rank_mask >> 8);    //Down one

    moves &= ~w_pieces;
    return moves;
}

// TODO: include a check for check, castling etc.
bitboard
gm_king(bitboard sq, bitboard w_pieces)
{
    bitboard moves = sq << 1 | sq >> 1 | sq << 9 | sq >> 9 | sq << 7 | sq >> 7 | sq << 8 | sq >> 8;
    moves &= ~w_pieces;
    return moves;
}

// Calculating the moves of a slider in the positive ray direction
// Follows o ^ (o - 2r)
// https://www.chessprogramming.org/Subtracting_a_Rook_from_a_Blocking_Piece
bitboard
gm_pos_slider(bitboard sq, bitboard occupied, bitboard w_pieces, bitboard filemask)
{
    bitboard pot_blockers = (occupied & filemask);
    bitboard diff = pot_blockers - (2 * sq);
    bitboard changed = diff ^ occupied;
    bitboard b_moves = changed & filemask & ~w_pieces;

    return b_moves;
}