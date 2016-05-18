#include "ChessEngine.h"
#include <memory.h>
#include <iostream>

ChessEngine::ChessEngine() : colorWhite(64)
{
    memset (&board, 0, sizeof(byte)*8*8);
}

void ChessEngine::newGame()
{
    reload ();
    fillBoard ();
}

void ChessEngine::setTestMode(bool b)
{
    bTestMode = b;
}

