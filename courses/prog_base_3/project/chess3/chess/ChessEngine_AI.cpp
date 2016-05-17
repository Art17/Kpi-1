#include "ChessEngine.h"
#include <memory.h>
#include <iostream>
#include <time.h>

void ChessEngine::getBestMove(Move* pRes)
{
    getRandomMove (pRes);
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

    /*int xFrom = pRes->from % 8;
    int yFrom = pRes->from / 8;
    int yTo = pRes->to / 8;

    if (yTo == 0 || yTo == 7)
    {
        if (board[yFrom][xFrom] & Pawn)
        {
            int figures [] = {Knight, Bishop, Rook, Queen};
            pRes->extra = figures [ rand () % 4 ];
        }
    }*/
}
