#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// The struct to hold the bitboard
#ifndef chessboard_h
#define chessboard_h

typedef unsigned long bitboard;
typedef unsigned long mask; // A bitboard with only one active bit.
typedef struct
{
    bitboard wp, bp, wr, br, wn, bn, wb, bb, wq, bq, wk, bk; //The bitboards for each peice
    bitboard en_passant;                                     //The en passant square
    bool wtm;                                                //The turn
    char castling, halfmove, fullmove;                       //The castling rights, and the fullmove and halfmove numbers

} chessboard;

#define WHITE (0xFFFFFFFFFFFFFFFF)
#define BLACK (0)

#define UL_TRIANGLE (0x7F3F1F0703010000)
#define UR_TRIANGLE (0xFEFCF8F0E0C08000)

#define FILE_A (0x0101010101010101L)
#define FILE_B (0x0202020202020202L)
#define FILE_C (0x0404040404040404L)
#define FILE_D (0x0808080808080808L)
#define FILE_E (0x1010101010101010L)
#define FILE_F (0x2020202020202020L)
#define FILE_G (0x4040404040404040L)
#define FILE_H (0x8080808080808080L)

#define RANK_1 (0x00000000000000FFL)
#define RANK_2 (0x000000000000FF00L)
#define RANK_3 (0x0000000000FF0000L)
#define RANK_4 (0x00000000FF000000L)
#define RANK_5 (0x000000FF00000000L)
#define RANK_6 (0x0000FF0000000000L)
#define RANK_7 (0x00FF000000000000L)
#define RANK_8 (0xFF00000000000000L)

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

#define WHITE_KINGSIDE (0b1000)
#define WHITE_QUEENSIDE (0b0100)
#define BLACK_KINGSIDE (0b0010)
#define BLACK_QUEENSIDE (0b0001)

static chessboard STARTING_BOARD = {
    .wp = RANK_2,                     // 0000 0000 .... 1111 1111 0000 1000
    .bp = RANK_7,                     // 0000 0000 1111 1111 .... 0000 0000
    .wr = A1 | H1,                    // 0000 0000 .... 1000 0001
    .br = A8 | H8,                    // 1000 0001 .... 0000 0000
    .wn = B1 | G1,                    // 0000 0000 .... 0100 0010
    .bn = B8 | G8,                    // 0100 0010 .... 0000 0000
    .wb = C1 | F1,                    // 0000 0000 .... 0010 0100
    .bb = C8 | F8,                    // 0010 0100 .... 0000 0000
    .wq = D1,                         // 0000 0000 .... 0000 1000
    .bq = D8,                         // 0000 1000 .... 0000 0000
    .wk = E1,                         // 0000 0000 .... 0001 0000
    .bk = E8,                         // 0001 0000 .... 0000 0000
    .wtm = true,                      // White to move
    .castling = 0b1111,               // whitekingside, whitequeenside, blackkingside, blackqueenside mask
    .en_passant = 0x0000000000000000, // a bitboard for the en passant square(s)
    .halfmove = 0,                    // the halfmove clock,
    .fullmove = 0,                    // the fullmove number
};

static chessboard EMPTY_BOARD = {0};

#endif