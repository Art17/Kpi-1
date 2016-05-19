#include "ChessEngine.h"
#include <memory.h>
#include <iostream>

bool ChessEngine::undo ()
{
    if ( lastMoves.size() == 0 )
        return false;

    ExtraMove lastMove = lastMoves.top ();
    lastMoves.pop ();
    int lastFrom = lastMove.from;
    int lastTo = lastMove.to;
    int lastXFrom = lastFrom % 8;
    int lastYFrom = lastFrom / 8;
    int lastXTo = lastTo % 8;
    int lastYTo = lastTo / 8;

    if (board[lastYTo][lastXTo] & Pawn)
    {
        if ( isWhite (board[lastYTo][lastXTo]) )
        {
            if ( lastYFrom == 3 && lastYTo == 2 && lastMove.beatenFigure == 0)
            {
                if ( lastXFrom + 1 == lastXTo)
                {
                    board[lastYFrom][lastXFrom+1] = Pawn;
                    blackPositions.push_back (cti (lastXFrom+1, lastYFrom));
                }
                else if (lastXFrom - 1 == lastXTo)
                {
                    board[lastYFrom][lastXFrom-1] = Pawn;
                    blackPositions.push_back (cti (lastXFrom-1, lastYFrom));
                }
            }
        }
        else
        {
            if ( lastYFrom == 4 && lastYTo == 5  && lastMove.beatenFigure == 0)
            {
                if ( lastXFrom + 1 == lastXTo)
                {
                    whitePositions.push_back (cti (lastXFrom+1, lastYFrom));
                    board[lastYFrom][lastXFrom+1] = Pawn | colorWhite;
                }
                else if (lastXFrom == lastXTo - 1)
                {
                    whitePositions.push_back (cti (lastXFrom-1, lastYFrom));
                    board[lastYFrom][lastXFrom-1] = Pawn | colorWhite;
                }
            }
        }
    }
    else if ( board[lastYTo][lastXTo] & King )
    {
        if (isWhite (board[lastYTo][lastXTo]))
            whiteKingPos = cti (lastXFrom, lastYFrom);
        else if (!isWhite (board[lastYTo][lastXTo]))
            blackKingPos = cti (lastXFrom, lastYFrom);
        if ( lastXTo == lastXFrom-2)
        {
            board[lastYTo][0] = board[lastYTo][lastXTo+1];
            board[lastYTo][lastXTo+1] = 0;

            if (isWhite (board[lastYTo][lastXTo]))
            {
                whitePositions.remove (cti(lastXTo+1, lastYTo));
                whitePositions.push_back (cti(0, lastYTo));
            }
            else
            {
                blackPositions.remove (cti(lastXTo+1, lastYTo));
                blackPositions.push_back (cti(0, lastYTo));
            }

        }
        else if ( lastXTo == lastXFrom+2)
        {
            board[lastYTo][7] = board[lastYTo][lastXTo-1];
            board[lastYTo][lastXTo-1] = 0;


            if (isWhite (board[lastYTo][lastXTo]))
            {
                whitePositions.remove (cti(lastXTo-1, lastYTo));
                whitePositions.push_back (cti(7, lastYTo));
            }
            else
            {
                blackPositions.remove (cti(lastXTo-1, lastYTo));
                blackPositions.push_back (cti(7, lastYTo));
            }

        }
    }
    if (isWhite (board[lastYTo][lastXTo]))
    {
        whitePositions.remove (cti(lastXTo, lastYTo));
        whitePositions.push_back (cti(lastXFrom, lastYFrom));
        if (lastMove.beatenFigure != 0)
        {
            blackPositions.push_back(cti (lastXTo, lastYTo));
        }
    }
    else
    {
        blackPositions.remove (cti(lastXTo, lastYTo));
        blackPositions.push_back (cti(lastXFrom, lastYFrom));
        if (lastMove.beatenFigure != 0)
        {
            whitePositions.push_back(cti (lastXTo, lastYTo));
        }
    }

    board[lastYFrom][lastXFrom] = board[lastYTo][lastXTo];
    board[lastYTo][lastXTo] = lastMove.beatenFigure;


    if (lastMove.extraFigure != 0)
        board[lastYFrom][lastXFrom] = Pawn | (lastMove.extraFigure & colorWhite);

    canCastling = lastMove.canCastling;
    whiteTurn = !whiteTurn;

    return true;
}
