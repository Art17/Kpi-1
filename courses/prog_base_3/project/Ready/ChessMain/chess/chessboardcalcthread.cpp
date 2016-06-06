#include "chessboardcalcthread.h"

#include <iostream>

using namespace std;

ChessBoardCalcThread::ChessBoardCalcThread(ChessEngine* ce)
{
    chessEng = ce;
}


void ChessBoardCalcThread::run ()
{
    QThread::msleep(500);
    Move move;
    chessEng->getBestMove(&move);

    emit moveReady(move);
}
