#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// The struct to hold the bitboard
typedef struct
{
    unsigned long wp, bp, wr, br, wn, bn, wb, bb, wq, bq, wk, bk; //The bitboards for each peice
    unsigned long en_passant;                                     //The en passant square
    bool wtm;                                                     //The turn
    char castling, halfmove, fullmove;                            //The castling rights, and the fullmove and halfmove numbers

} chessboard;

#define FILE_A (0x0101010101010101)
#define FILE_B (0x0202020202020202)
#define FILE_C (0x0404040404040404)
#define FILE_D (0x0808080808080808)
#define FILE_E (0x1010101010101010)
#define FILE_F (0x2020202020202020)
#define FILE_G (0x4040404040404040)
#define FILE_H (0x8080808080808080)

#define RANK_1 (0x00000000000000FF)
#define RANK_2 (0x000000000000FF00)
#define RANK_3 (0x0000000000FF0000)
#define RANK_4 (0x00000000FF000000)
#define RANK_5 (0x000000FF00000000)
#define RANK_6 (0x0000FF0000000000)
#define RANK_7 (0x00FF000000000000)
#define RANK_8 (0xFF00000000000000)

#define A1 (0x0000000000000001)
#define B1 (0x0000000000000002)
#define C1 (0x0000000000000004)
#define D1 (0x0000000000000008)
#define E1 (0x0000000000000010)
#define F1 (0x0000000000000020)
#define G1 (0x0000000000000040)
#define H1 (0x0000000000000080)
#define A2 (0x0000000000000100)
#define B2 (0x0000000000000200)
#define C2 (0x0000000000000400)
#define D2 (0x0000000000000800)
#define E2 (0x0000000000001000)
#define F2 (0x0000000000002000)
#define G2 (0x0000000000004000)
#define H2 (0x0000000000008000)
#define A3 (0x0000000000010000)
#define B3 (0x0000000000020000)
#define C3 (0x0000000000040000)
#define D3 (0x0000000000080000)
#define E3 (0x0000000000100000)
#define F3 (0x0000000000200000)
#define G3 (0x0000000000400000)
#define H3 (0x0000000000800000)
#define A4 (0x0000000001000000)
#define B4 (0x0000000002000000)
#define C4 (0x0000000004000000)
#define D4 (0x0000000008000000)
#define E4 (0x0000000010000000)
#define F4 (0x0000000020000000)
#define G4 (0x0000000040000000)
#define H4 (0x0000000080000000)
#define A5 (0x0000000100000000)
#define B5 (0x0000000200000000)
#define C5 (0x0000000400000000)
#define D5 (0x0000000800000000)
#define E5 (0x0000001000000000)
#define F5 (0x0000002000000000)
#define G5 (0x0000004000000000)
#define H5 (0x0000008000000000)
#define A6 (0x0000010000000000)
#define B6 (0x0000020000000000)
#define C6 (0x0000040000000000)
#define D6 (0x0000080000000000)
#define E6 (0x0000100000000000)
#define F6 (0x0000200000000000)
#define G6 (0x0000400000000000)
#define H6 (0x0000800000000000)
#define A7 (0x0001000000000000)
#define B7 (0x0002000000000000)
#define C7 (0x0004000000000000)
#define D7 (0x0008000000000000)
#define E7 (0x0010000000000000)
#define F7 (0x0020000000000000)
#define G7 (0x0040000000000000)
#define H7 (0x0080000000000000)
#define A8 (0x0100000000000000)
#define B8 (0x0200000000000000)
#define C8 (0x0400000000000000)
#define D8 (0x0800000000000000)
#define E8 (0x1000000000000000)
#define F8 (0x2000000000000000)
#define G8 (0x4000000000000000)
#define H8 (0x8000000000000000)

#define DIAGONAL (0x8040201008040201)
#define ANTIDIAGONAL (0x0102040810204080)
#define LIGHT_SQUARES (0x55AA55AA55AA55AA)
#define DARK_SQUARES (0xAA55AA55AA55AA55)

#define WHITE (1)
#define BLACK (0)
#define WHITE_KINGSIDE (0b1000)
#define WHITE_QUEENSIDE (0b0100)
#define BLACK_KINGSIDE (0b0010)
#define BLACK_QUEENSIDE (0b0001)