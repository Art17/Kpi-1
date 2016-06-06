#include "ChessEngine.h"
#include <memory.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

#define INF        100000007
#define CHECKMATE  10000007

#define MAKE_CASTLING 50
#define PAWN_MOVE     1
#define BREAK_CASTLING -50
#define BREAK_LEFT_CASTLING -25
#define BREAK_RIGHT_CASTLING -25
#define E4E5 5
#define C4C5 5

void ChessEngine::getBestMove(Move* pRes)
{
    minmax (pRes, getOptimalDepth());
}

int ChessEngine::evaluateMove (const Move& move)
{
    int maximized  = 0;
    int xTo = move.to%8;
    int yTo = move.to/8;
    int xFrom = move.from % 8;
    int yFrom = move.from / 8;
    if (board[yTo][xTo] != 0)
        maximized = getFigurePower(board[yTo][xTo]);
    if ((board[yFrom][xFrom] & Pawn) && (yTo == 0 || yTo == 7))
    {
        maximized -= getFigurePower (Pawn);
        maximized += getFigurePower (move.extra);
    }
    if ( (board[yFrom][xFrom] & King) )
    {
        if ( xTo == xFrom + 2 || xTo == xFrom - 2 )
            maximized += MAKE_CASTLING;
        else
        {
            if (whiteTurn)
            {
                if (canCastling & WHITE_LEFT_CASTLING || canCastling & WHITE_RIGHT_CASTLING)
                    maximized += BREAK_CASTLING;
            }
            else
            {
                if (canCastling & BLACK_LEFT_CASTLING || canCastling & BLACK_RIGHT_CASTLING)
                    maximized += BREAK_CASTLING;
            }
        }
    }
    else if ( board[yFrom][xFrom] & Rook )
    {
        if (whiteTurn)
        {
            if (xFrom == 0 && canCastling & WHITE_LEFT_CASTLING)
                maximized += BREAK_LEFT_CASTLING;
            else if (xFrom == 7 && canCastling & WHITE_RIGHT_CASTLING)
                maximized += BREAK_RIGHT_CASTLING;
        }
        else
        {
            if (xFrom == 0 && canCastling & BLACK_LEFT_CASTLING)
                maximized += BREAK_LEFT_CASTLING;
            else if (xFrom == 7 && canCastling & BLACK_RIGHT_CASTLING)
                maximized += BREAK_RIGHT_CASTLING;
        }
    }
    else if ( board[yFrom][xFrom] & Pawn )
    {
        if (whiteTurn)
        {
            if (xFrom == 4 && yFrom == 6 && yTo == 4)
                maximized += E4E5;
            else if (xFrom == 2 && yFrom == 6 && yTo == 4)
                maximized += C4C5;
        }
        else
        {
            if (xFrom == 4 && yFrom == 1 && yTo == 3)
                maximized += E4E5;
            else if (xFrom == 2 && yFrom == 1 && yTo == 3)
                maximized += C4C5;
        }
        if ( getPlayerPower (true) + getPlayerPower(false) < getFigurePower(Queen)*2 )
            maximized += PAWN_MOVE;
    }

    return maximized;
}

int ChessEngine::minmax (Move* pRes, int depth)
{
    srand (time(NULL));
    if (depth < 1)
        return 0;

    dbyte allMoves[164];
    int len = 0;
    getAllMoves(allMoves, 164, &len, whiteTurn);
    vector<Move> bestMoves;

    if (len == 0)
    {
        if (whiteTurn)
        {
            if (isBeaten (whiteKingPos, false))
                return -CHECKMATE;
            else
                return getPlayerPower(false) - getPlayerPower(true);

        }
        else
        {
            if (isBeaten (blackKingPos, true))
                return -CHECKMATE;
            else
                return getPlayerPower(true) - getPlayerPower(false);
        }
    }

    int bestAdv = -INF;

    for (int i = 0; i < len; i++)
    {
        int from = LOBYTE (allMoves[i]);
        int to = HIBYTE (allMoves[i]);

        Move move;
        move.from = from;
        move.to = to;
        move.extra = Queen;

        int maximized = evaluateMove (move);

        makeMoveLL(move);
        int minimized = minmaxLow (depth-1);

        if (maximized - minimized == bestAdv)
        {
            bestMoves.push_back(move);
        }
        else if (maximized - minimized > bestAdv)
        {
            bestMoves.clear();
            bestAdv = maximized - minimized;
            bestMoves.push_back(move);
        }

        undo ();
    }
    if (pRes != NULL)
        memcpy (pRes, &bestMoves.at( rand () % bestMoves.size() ), sizeof (Move));

    return bestAdv;
}


int ChessEngine::getOptimalDepth ()
{
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

    if (qFigures > 10)
        return 4;
    else
        return 5;
}

int ChessEngine::getPlayerPower (bool bWhite)
{
    int power = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ( board[i][j] != 0 && isWhite (board[i][j]) == bWhite ) {
                power += getFigurePower(board[i][j]);
            }
        }
    }

    return power;
}

int ChessEngine::minmaxLow (int depth)
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
                return -CHECKMATE;
            else
                return getPlayerPower(false) - getPlayerPower(true);

        }
        else
        {
            if (isBeaten (blackKingPos, true))
                return -CHECKMATE;
            else
                return getPlayerPower(true) - getPlayerPower(false);
        }
    }

    int bestAdv = -INF;

    for (int i = 0; i < len; i++)
    {
        int from = LOBYTE (allMoves[i]);
        int to = HIBYTE (allMoves[i]);

        Move move;
        move.from = from;
        move.to = to;
        move.extra = Queen;

        int maximized = evaluateMove (move);

        makeMoveLL(move);
        int minimized = minmaxLow (depth-1);

        if (maximized - minimized > bestAdv)
            bestAdv = maximized - minimized;

        undo ();
    }

    return bestAdv;
}
