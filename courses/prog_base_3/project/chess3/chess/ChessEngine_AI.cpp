#include "ChessEngine.h"
#include <memory.h>
#include <iostream>
#include <time.h>

void ChessEngine::getBestMove(Move* pRes)
{
    minmax (pRes, 0);
}

int ChessEngine::minmax (Move* pRes, int depth)
{
    if (depth >= 5)
        return 0;

    dbyte allMoves[64];
    int len = 0;
    getAllMoves(allMoves, &len, whiteTurn);

    if (len == 0)
    {
        if (whiteTurn)
        {
            if (isBeaten (whiteKingPos, false))
                return -777;
            else
                return -1;

        }
        else
        {
            if (isBeaten (blackKingPos, true))
                return -777;
            else
                return -1;
        }
    }

    int bestAdv = -12222;
    Move res;

    for (int i = 0; i < len; i++)
    {
        int from = LOBYTE (allMoves[i]);
        int to = HIBYTE (allMoves[i]);

        Move move;
        move.from = from;
        move.to = to;
        move.extra = Queen;

        int maximized  = 0;
        int xTo = to%8;
        int yTo = to/8;
        int xFrom = from % 8;
        int yFrom = from / 8;
        if (board[yTo][xTo] != 0)
            maximized = getFigurePower(board[yTo][xTo]);

        makeMoveLL(move);
        int minimized = minmax (NULL, depth+1);

        if (maximized - minimized > bestAdv)
        {
            bestAdv = maximized - minimized;
            res = move;
        }

        undo ();
    }
    if (pRes != NULL)
        memcpy (pRes, &res, sizeof (Move));

    return bestAdv;
}

void ChessEngine::getRandomBeatMove (Move* pRes)
{
    srand (time (NULL));
    dbyte allMoves[128];
    int len = 0;

    getAllMoves(allMoves, &len, whiteTurn);

    if (len == 0)
        return;

    for (int i = 0; i < len; i++)
    {
        int from = LOBYTE (allMoves[i]);
        int to = HIBYTE (allMoves[i]);
        if ( board[to/8][to%8] != 0 )
        {
            pRes->from = from;
            pRes->to = to;
            pRes->extra = Queen;
            return;
        }
    }
    getRandomMove(pRes);
}

void ChessEngine::getRandomMove(Move* pRes)
{
    srand (time (NULL));
    dbyte allMoves[128];
    int len = 0;

    getAllMoves(allMoves, &len, whiteTurn);

    if (len == 0)
        return;

    dbyte randMove = allMoves [rand() % len];

    pRes->from = LOBYTE (randMove);
    pRes->to = HIBYTE (randMove);
    pRes->extra = Queen;

    int xFrom = pRes->from % 8;
    int yFrom = pRes->from / 8;
    int yTo = pRes->to / 8;

    if (yTo == 0 || yTo == 7)
    {
        if (board[yFrom][xFrom] & Pawn)
        {
            int figures [] = {Knight, Bishop, Rook, Queen};
            pRes->extra = figures [ rand () % 4 ];
        }
    }
}
