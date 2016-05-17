#include "ChessEngine.h"
#include <memory.h>
#include <iostream>
#include <time.h>

void ChessEngine::engineMove(Move* pRes)
{
    getRandomMove (pRes);
}

void ChessEngine::getRandomMove(Move* pRes)
{
    srand (time (NULL));
    dbyte allMoves[64];
    int len = 0;

    getAllMoves(allMoves, &len, whiteTurn);

    dbyte randMove = allMoves [rand() % len];

    pRes->from = LOBYTE (randMove);
    pRes->to = HIBYTE (randMove);
    pRes->extra = Queen;
}
