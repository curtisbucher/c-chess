#include "chessboard.h"
#include "board_io.h"

void print_header()
{
    printf("\n ██████  ██████   ██████  ████████ ██   ██ ███████ ██████  ███████     ██████   █████  ███    ██ ███████\n \
██   ██ ██   ██ ██    ██    ██    ██   ██ ██      ██   ██ ██          ██   ██ ██   ██ ████   ██ ██\n \
██████  ██████  ██    ██    ██    ███████ █████   ██████  ███████     ██████  ███████ ██ ██  ██ █████\n \
██   ██ ██   ██ ██    ██    ██    ██   ██ ██      ██   ██      ██     ██   ██ ██   ██ ██  ██ ██ ██\n \
██████  ██   ██  ██████     ██    ██   ██ ███████ ██   ██ ███████     ██████  ██   ██ ██   ████ ███████\n \
\tBy Curtis Bucher                                                            MIT License 2021\n\n");
}

void print_bitboard(bitboard b, bool wtp)
{
    // Prints the binary representation of a bitboard.

    unsigned long map = wtp ? 1L << 56 : 1L;
    int color = 1;
    char peice = ' ';

    for (int i = 0; i < 64; i++)
    {
        printf(b & map ? "1 " : "0 ");

        if ((i + 1) % 8 == 0)
        {
            printf("%s%s%d%s%s\n", LIGHT_BACKGROUND, DARK_TEXT, wtp ? 8 - i / 8 : i / 8, NORMAL_BACKGROUND, LIGHT_TEXT);
            if (wtp)
                map >>= 15;
            else
                map <<= 1;
            color = !color;
        }
        else
        {

            map <<= 1;
        }
    }
    printf("%s%sA B C D E F G H%s%s\n", LIGHT_BACKGROUND, DARK_TEXT, NORMAL_BACKGROUND, LIGHT_TEXT);
}

void print_board(const chessboard board, bool wtp)
{
    unsigned long map = wtp ? 1L << 56 : 1L << 7;
    int color = 1;
    char peice = ' ';

    for (int i = 0; i < 64; i++)
    {
        color = !color;
        if (board.wr & map)
            peice = 'r';
        else if (board.wn & map)
            peice = 'n';
        else if (board.wb & map)
            peice = 'b';
        else if (board.wq & map)
            peice = 'q';
        else if (board.wk & map)
            peice = 'k';
        else if (board.wp & map)
            peice = 'p';
        else if (board.br & map)
            peice = 'R';
        else if (board.bn & map)
            peice = 'N';
        else if (board.bb & map)
            peice = 'B';
        else if (board.bq & map)
            peice = 'Q';
        else if (board.bk & map)
            peice = 'K';
        else if (board.bp & map)
            peice = 'P';
        else
            peice = ' ';

        printf("%s%s %c %s", peice < 'a' ? DARK_TEXT : LIGHT_TEXT, color ? DARK_BACKGROUND : LIGHT_BACKGROUND, peice, NORMAL_BACKGROUND);

        if ((i + 1) % 8 == 0)
        {
            printf(" %d", wtp ? 8 - i / 8 : 1 + i / 8);
            switch (i / 8)
            {
            case 0:
                printf("\t\tTurn:\t\t\t%s", board.wtm ? "White" : "Black");
                break;
            case 1:
                printf("\t\tCastling Rights:\t%s", (board.castling & WHITE_KINGSIDE) ? "K" : "");
                printf("%s", (board.castling & WHITE_QUEENSIDE) ? "Q" : "");
                printf("%s", (board.castling & BLACK_KINGSIDE) ? "k" : "");
                printf("%s", (board.castling & BLACK_QUEENSIDE) ? "q" : "");
                break;
            case 2:
                printf("\t\tEn Passant Square:\t%s", "empty for now");
                break;
            case 3:
                printf("\t\tHalfmove clock:\t\t%d", board.halfmove);
                break;
            case 4:
                printf("\t\tFullmove number:\t%d", board.fullmove);
                break;
            }
            printf("\n");

            if (wtp)
                map >>= 15;
            else
                map <<= 15;
            color = !color;
        }
        else
        {
            if (wtp)
                map <<= 1;
            else
                map >>= 1;
        }
    }
    if (wtp)
        printf(" A  B  C  D  E  F  G  H  ");
    else
        printf(" H  G  F  E  D  C  B  A  ");
}

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
                fen[++f] = '6';
            }
            else if (board.en_passant & (0x0000000000010000 << i))
            {
                fen[++f] = 'a' + i;
                fen[++f] = '3';
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
    chessboard board = {0};
    int i = 0;
    int f = 0;

    while (fen[i] != ' ')
    {
        //Generating a mask by using gnarly math to iterate from the left to right, top to bottom.
        unsigned long mask = (1L << (((63 - f) / 8) * 8 + (7 - (63 - f) % 8)));
        switch (fen[i++])
        {
        case 'r':
            board.br |= mask;
            f++;
            break;
        case 'n':
            board.bn |= mask;
            f++;
            break;
        case 'b':
            board.bb |= mask;
            f++;
            break;
        case 'q':
            board.bq |= mask;
            f++;
            break;
        case 'k':
            board.bk |= mask;
            f++;
            break;
        case 'p':
            board.bp |= mask;
            f++;
            break;
        case 'R':
            board.wr |= mask;
            f++;
            break;
        case 'N':
            board.wn |= mask;
            f++;
            break;
        case 'B':
            board.wb |= mask;
            f++;
            break;
        case 'Q':
            board.wq |= mask;
            f++;
            break;
        case 'K':
            board.wk |= mask;
            f++;
            break;
        case 'P':
            board.wp |= mask;
            f++;
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
    // White to move
    board.wtm = (fen[++i] == 'w');

    // Castling rights
    i += 2;
    while (fen[i] != ' ')
    {
        switch (fen[i++])
        {
        case 'K':
            board.castling |= WHITE_KINGSIDE;
            break;
        case 'Q':
            board.castling |= WHITE_QUEENSIDE;
            break;
        case 'k':
            board.castling |= BLACK_KINGSIDE;
            break;
        case 'q':
            board.castling |= BLACK_QUEENSIDE;
            break;
        default:
            break;
        }
    }
    i += 1;

    // // En passant
    if (fen[i] == '-')
    {
        board.en_passant = 0;
        i++;
    }
    else
    {
        for (int j = 0; j < 8; j++)
        {
            if (fen[i] == 'a' + j)
            {
                board.en_passant |= ((1L << j) << (fen[++i] - '1') * 8);
            }
        }
    }

    // Fullmove and halfmove clock
    i += 1;
    board.halfmove = atoi(fen + i);

    while (fen[i] != ' ')
        i++;

    board.fullmove = atoi(fen + i);

    return board;
}
