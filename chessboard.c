#include "chessboard.h"

chessboard apply_move(chessboard board, move m, int color)
{
    if (color)
    {
        // Applying move
        if (m & board.wp)
            board.wp ^= m;
        else if (m & board.wr)
            board.wr ^= m;
        else if (m & board.wb)
            board.wb ^= m;
        else if (m & board.wn)
            board.wn ^= m;
        else if (m & board.wq)
            board.wq ^= m;
        else if (m & board.wk)
            board.wk ^= m;

        // Removing taken pieces
        board.bp &= ~m;
        board.br &= ~m;
        board.bn &= ~m;
        board.bb &= ~m;
        board.bq &= ~m;
        board.bk &= ~m;
    }
    else
    {
        // Applying move
        if (m & board.bp)
            board.bp ^= m;
        else if (m & board.br)
            board.br ^= m;
        else if (m & board.bb)
            board.bb ^= m;
        else if (m & board.bn)
            board.bn ^= m;
        else if (m & board.bq)
            board.bq ^= m;
        else if (m & board.bk)
            board.bk ^= m;

        // Removing taken pieces
        board.wp &= ~m;
        board.wr &= ~m;
        board.wn &= ~m;
        board.wb &= ~m;
        board.wq &= ~m;
        board.wk &= ~m;
    }
    return board;
}