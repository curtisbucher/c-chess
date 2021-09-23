// Generates possible moves for the current position.
#include "gen_moves.h"
#include "board_io.h"

/**
 * @brief Generate a list of legal moves, and compare to check that given move is legal
 * @param m The move to check for legality
 * @param board The board to check the move on
 * @param wtm White to Move. True or False
 * @return True if the move is legal, false otherwise
**/
bool
is_legal(move m, chessboard board, bool wtm){
    move moves[116];
    int num_moves = gen_moves(board, moves, wtm);

    for (int i = 0; i < num_moves; i++){
        if (moves[i] == m){
            return true;
        }
    }
    return false;
}

/**
 * @brief Generate all possible moves for the current position.
 * @param board A chessboard type representing the current board.
 * @param moves An array of `move` types. Modified in place.
 * @param wtm An integer, equal to WHITE or BLACK representing the piece to move.
 * @return The number of moves generated.
*/
int
gen_moves(chessboard board, move *moves, move wtm)
{
    bitboard w_pieces = board.wp | board.wr | board.wn | board.wb | board.wq | board.wk;
    bitboard b_pieces = board.bp | board.br | board.bn | board.bb | board.bq | board.bk;
    bitboard occupied = w_pieces | b_pieces;

    int i = 0;

    mask pieces[8];
    mask p_moves[28];

    // Pawns
    int num_pieces = bitboard_to_mask(wtm ? board.wp : board.bp, pieces, 8);
    int num_moves;

    // for each white pawn
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(
            wtm ? gm_w_pawn(pieces[p], occupied, b_pieces) : gm_b_pawn(pieces[p], occupied, w_pieces),
            p_moves, 28);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = pieces[p] | p_moves[m];
        }
    }

    // Rooks
    num_pieces = bitboard_to_mask(wtm ? board.wr : board.br, pieces, 2);

    // for each rook
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_rook(pieces[p], occupied, wtm ? w_pieces : b_pieces), p_moves, 14);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = pieces[p] | p_moves[m];
        }
    }

    // Bishops
    num_pieces = bitboard_to_mask(wtm ? board.wb : board.bb, pieces, 2);

    // for each bishop
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_bishop(pieces[p], occupied, wtm ? w_pieces : b_pieces), p_moves, 14);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = pieces[p] | p_moves[m];
        }
    }

    // Queens
    num_pieces = bitboard_to_mask(wtm ? board.wq : board.bq, pieces, 2);

    // for each queen
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_queen(pieces[p], occupied, wtm ? w_pieces : b_pieces), p_moves, 28);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = pieces[p] | p_moves[m];
        }
    }

    // Knight
    num_pieces = bitboard_to_mask(wtm ? board.wn : board.bn, pieces, 2);

    // for each king
    for (int p = 0; p < num_pieces; p++)
    {
        num_moves = bitboard_to_mask(gm_knight(pieces[p], wtm ? w_pieces : b_pieces), p_moves, 4);
        // for each possible move
        for (int m = 0; m < num_moves; m++)
        {
            moves[i++] = pieces[p] | p_moves[m];
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

/**
 * @brief Calculating the moves of a slider in the positive ray direction
 * @param sq The square of the peice
 * @param occupied A bitboard of the occupied squares
 * @param w_pieces A bitboard of the white pieces
 * @param file_mask A bitboard of the file or rank mask of the slider.
 * @note Follows o ^ (o - 2r)
 * @note https://www.chessprogramming.org/Subtracting_a_Rook_from_a_Blocking_Piece
**/
bitboard
gm_pos_slider(bitboard sq, bitboard occupied, bitboard w_pieces, bitboard filemask)
{
    bitboard pot_blockers = occupied & filemask;
    bitboard diff = pot_blockers - 2 * sq;
    bitboard changed = diff ^ occupied;
    bitboard b_moves = changed & filemask & ~w_pieces;

    return b_moves;
}