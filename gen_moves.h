#include "chessboard.h"
#include "tools.h"

bitboard gen_moves(bitboard sq, chessboard board);

//Sliders
bitboard gm_queen(bitboard sq, bitboard occupied, bitboard w_pieces);
bitboard gm_rook(bitboard sq, bitboard occupied, bitboard b_pieces);
bitboard gm_bishop(bitboard sq, bitboard occupied, bitboard b_pieces);
bitboard gm_pos_slider(bitboard sq, bitboard occupied, bitboard w_pieces, bitboard filemask);
bitboard gm_neg_slider(bitboard sq, bitboard occupied, bitboard w_pieces, bitboard filemask);

bitboard gm_w_pawn(bitboard sq, bitboard occupied, bitboard b_pieces);
bitboard gm_b_pawn(bitboard sq, bitboard occupied, bitboard w_pieces);

bitboard gm_knight(bitboard sq, bitboard w_pieces);
bitboard gm_king(bitboard sq, bitboard w_pieces);