#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "chessboard.h"

const char *bitboard_to_FEN(chessboard board)
{
    //https://www.chess.com/terms/fen-chess
    char *fen = calloc(87, sizeof(char)); // longest possible fen

    // Calculating fen peice placement
    int f = -1;
    unsigned long map = 1L << 56;
    for (int i = 0; i < 64; i++)
    {
        // Possibly optimise by ORing all the bitboards together and seeing if any are on the spot.
        // Should happen half the time.

        if (board.wr & map)
            fen[++f] = 'R';
        else if (board.wn & map)
            fen[++f] = 'N';
        else if (board.wb & map)
            fen[++f] = 'B';
        else if (board.wq & map)
            fen[++f] = 'Q';
        else if (board.wk & map)
            fen[++f] = 'K';
        else if (board.wp & map)
            fen[++f] = 'P';
        else if (board.br & map)
            fen[++f] = 'r';
        else if (board.bn & map)
            fen[++f] = 'n';
        else if (board.bb & map)
            fen[++f] = 'b';
        else if (board.bq & map)
            fen[++f] = 'q';
        else if (board.bk & map)
            fen[++f] = 'k';
        else if (board.bp & map)
            fen[++f] = 'p';
        else if (fen[f] > '9' || fen[f] == '/')
            fen[++f] = '1';
        else if (fen[f] == 0)
            fen[f] = '1';
        else
            fen[f]++;

        if ((i + 1) % 8 == 0 && i != 63)
        {
            fen[++f] = '/';
            map >>= 15;
        }
        else
        {
            map <<= 1;
        }
    }

    // Active color
    fen[++f] = ' ';
    if (board.wtm)
        fen[++f] = 'w';
    else
        fen[++f] = 'b';

    // Castling rights
    fen[++f] = ' ';
    if (board.castling == 0)
        fen[++f] = '-';
    if (board.castling & WHITE_KINGSIDE)
        fen[++f] = 'K';
    if (board.castling & WHITE_QUEENSIDE)
        fen[++f] = 'Q';
    if (board.castling & BLACK_KINGSIDE)
        fen[++f] = 'k';
    if (board.castling & BLACK_QUEENSIDE)
        fen[++f] = 'q';

    // En passant
    fen[++f] = ' ';
    if (board.en_passant == 0)
        fen[++f] = '-';
    else
        for (int i = 0; i < 8; i++)
        {
            if (board.en_passant & (0x0000010000000000 << i))
            {
                fen[++f] = 'a' + i;
                fen[++f] = '3';
            }
            else if (board.en_passant & (0x0000000000100000 << i))
            {
                fen[++f] = 'a' + i;
                fen[++f] = '6';
            }
        }

    // Halfmove and fullmove clock
    fen[++f] = ' ';
    sprintf(fen + ++f, "%d %d", board.halfmove, board.fullmove);

    return fen;
}

chessboard FEN_to_board(const char *fen)
{
    // Converts a FEN string to a chessboard struct.
    chessboard board = DEFAULT_BOARD;
    int i = 0;
    int f = 0;
    board.wr = 0;
    board.wn = 0;
    board.wb = 0;
    board.wq = 0;
    board.wk = 0;
    board.wp = 0;
    board.br = 0;
    board.bn = 0;
    board.bb = 0;
    board.bq = 0;
    board.bk = 0;
    board.bp = 0;

    while (fen[i] != ' ')
    {
        //printf("%c\n", fen[i]);
        switch (fen[i++])
        {
        case 'r':
            board.br |= (1L << (63 - f++));
            break;
        case 'n':
            board.bn |= (1L << (63 - f++));
            break;
        case 'b':
            board.bb |= (1L << (63 - f++));
            break;
        case 'q':
            board.bq |= (1L << (63 - f++));
            break;
        case 'k':
            board.bk |= (1L << (63 - f++));
            break;
        case 'p':
            board.bp |= (1L << (63 - f++));
            break;
        case 'R':
            board.wr |= (1L << (63 - f++));
            break;
        case 'N':
            board.wn |= (1L << (63 - f++));
            break;
        case 'B':
            board.wb |= (1L << (63 - f++));
            break;
        case 'Q':
            board.wq |= (1L << (63 - f++));
            break;
        case 'K':
            board.wk |= (1L << (63 - f++));
            break;
        case 'P':
            board.wp |= (1L << (63 - f++));
            break;
        case '1':
            f += 1;
            break;
        case '2':
            f += 2;
            break;
        case '3':
            f += 3;
            break;
        case '4':
            f += 4;
            break;
        case '5':
            f += 5;
            break;
        case '6':
            f += 6;
            break;
        case '7':
            f += 7;
            break;
        case '8':
            f += 8;
            break;
        default:
            break;
        }
    }
    return board;
}

int main()
{
    // printf() displays the string inside quotation
    // chessboard board = DEFAULT_BOARD;
    // const char *fen = bitboard_to_FEN(board);
    // printf("%s", fen);

    const char fen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";
    printf("https://lichess.org/editor/%s\n", fen);
    chessboard board = FEN_to_board(fen);

    const char *fen2 = bitboard_to_FEN(board);
    printf("https://lichess.org/editor/%s", fen2);

    free((char *)fen2);
    return 0;
}
