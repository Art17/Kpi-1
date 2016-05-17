#include "ChessEngine.h"
#include <memory.h>
#include <iostream>

bool ChessEngine::getBoard (byte* pBoard)
{
    memcpy (pBoard, &board, sizeof(byte)*8*8);

    return whiteTurn;
}

void ChessEngine::setBoard(byte* pBoard, bool bWhiteTurn)
{
    reload ();
    whiteTurn = bWhiteTurn;

    memcpy (&board, pBoard, sizeof (byte)*8*8);
}
