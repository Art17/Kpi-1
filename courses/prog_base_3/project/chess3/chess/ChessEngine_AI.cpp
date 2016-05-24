#include "ChessEngine.h"
#include <memory.h>
#include <iostream>
#include <time.h>

#define MIN_VALUE -1000007
#define MAX_VALUE  1000007
#define CHECKMATE  1007

void ChessEngine::getBestMove(Move* pRes)
{    
    minmax (pRes, getOptimalDepth());
    //AlphaBetaPruning (MIN_VALUE, MAX_VALUE, getOptimalDepth(), whiteTurn, pRes, 0, 0);

}

int ChessEngine::getOptimalDepth ()
{
    return 4;

    int qFigures = 0;
    for (int i = 0; i < 64; i++)
    {
        int x = i % 8;
        int y = i / 8;
        if ( board[y][x] != 0 )
        {
            qFigures++;
        }
    }

    if (qFigures > 20)
        return 4;
    else if (qFigures > 10)
        return 5;
    else if (qFigures > 5)
        return 6;
    else if (qFigures > 3)
        return 7;

    return 4;
}

int ChessEngine::minmax (Move* pRes, int depth)
{
    if (depth < 1)
        return 0;

    dbyte allMoves[128];
    int len = 0;
    getAllMoves(allMoves, 128, &len, whiteTurn);

    if (len == 0)
    {
        if (whiteTurn)
        {
            if (isBeaten (whiteKingPos, false))
                return -10000;
            else
                return 0;

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
        if ((board[yFrom][xFrom] & Pawn) && (yTo == 0 || yTo == 7))
        {
            maximized -= getFigurePower (Pawn);
            maximized += getFigurePower(Queen);
        }
        if ( (board[yFrom][xFrom] & Pawn) )
        {
            maximized += rand () % 1000 + 1000;
        }
        if ((board[yFrom][xFrom] & King) && xTo == xFrom+2 || xTo == xFrom-2)
        {
            maximized += 1;
        }

        makeMoveLL(move);
        int minimized = minmax (NULL, depth-1);

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

int ChessEngine::EvaluatePlayerPosition (bool bWhite)
{
    int res = 0;

    for (int i = 0; i < 64; i++)
    {
        int x = i % 8;
        int y = i / 8;

        if ( board[y][x] != 0 && (isWhite (board[y][x]) == bWhite) )
            res += getFigurePower (board[y][x]);
    }

    return res;
}

int ChessEngine::AlphaBetaPruning (int alpha, int beta, int depth, bool curPlayer, Move* pRes, int curPlayerPos, int oppositePlayerPos)
{
    int value;

    dbyte allMoves[64];
    int len = 0;
    getAllMoves(allMoves, 64, &len, curPlayer);

    Move res;

    if (len == 0)
    {
        if (curPlayer)
        {
            if (isBeaten (whiteKingPos, false))
                return -777;
            else
                return 0;

        }
        else
        {
            if (isBeaten (blackKingPos, true))
                return -777;
            else
                return 0;
        }
    }

    for (int i = 0; i < len; i++)
    {
        int from = LOBYTE (allMoves[i]);
        int to = HIBYTE (allMoves[i]);

        Move move;
        move.from = from;
        move.to = to;
        move.extra = Queen;

        int maximized = 0;
        int xTo = to%8;
        int yTo = to/8;
        int xFrom = from % 8;
        int yFrom = from / 8;
        if (board[yTo][xTo] != 0)
            maximized = getFigurePower(board[yTo][xTo]);
        if ((board[yFrom][xFrom] & Pawn) && (yTo == 0 || yTo == 7))
        {
            maximized -= getFigurePower (Pawn);
            maximized += getFigurePower(Queen);
        }

        oppositePlayerPos -= maximized;

        makeMoveLL(move);

        if (depth > 0)
            value = -AlphaBetaPruning (-beta, -alpha, depth - 1, !curPlayer, pRes, oppositePlayerPos, curPlayerPos);
        else
            value = curPlayerPos - oppositePlayerPos;

        undo();
        oppositePlayerPos += maximized;

        if (value > alpha)
        {
            res = move;
            if (value >= beta)
                return beta;
            alpha = value;
        }
    }

    if (pRes != NULL)
        memcpy (pRes, &res, sizeof (Move));

    return alpha;
}


/*int ChessEngine::minmax (Move* pRes, int depth)
{
    if (depth >= 4)
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
        if ((board[yFrom][xFrom] & Pawn) && (yTo == 0 || yTo == 7))
        {
            maximized -= getFigurePower (Pawn);
            maximized += getFigurePower(Queen);
        }

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
}*/

void ChessEngine::getRandomBeatMove (Move* pRes)
{
    srand (time (NULL));
    dbyte allMoves[128];
    int len = 0;

    getAllMoves(allMoves, 128, &len, whiteTurn);

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

    getAllMoves(allMoves, 128, &len, whiteTurn);

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
