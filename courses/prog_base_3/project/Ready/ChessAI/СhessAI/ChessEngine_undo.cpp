#include "ChessEngine.h"
#include <memory.h>
#include <iostream>

bool ChessEngine::undo ()  // optimized
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
    int beatenFigure = lastMove.beatenFigure;
    int beatenFigureX = lastMove.beatenFigurePos % 8;
    int beatenFigureY = lastMove.beatenFigurePos / 8;

    int castlingFigureXFrom = lastMove.castlingFigureFrom % 8;
    int castlingFigureYFrom = lastMove.castlingFigureFrom / 8;
    int castlingFigureXTo = lastMove.castlingFigureTo % 8;
    int castlingFigureYTo = lastMove.castlingFigureTo / 8;

    if ( board[lastYTo][lastXTo] & King )
    {
        if (isWhite (board[lastYTo][lastXTo]))
            whiteKingPos = cti (lastXFrom, lastYFrom);
        else if (!isWhite (board[lastYTo][lastXTo]))
            blackKingPos = cti (lastXFrom, lastYFrom);
        if ( lastMove.castlingFigureFrom != -1 )
        {
            board[castlingFigureYFrom][castlingFigureXFrom] = board[castlingFigureYTo][castlingFigureXTo];
            board[castlingFigureYTo][castlingFigureXTo] = 0;
        }
    }

    board[lastYFrom][lastXFrom] = board[lastYTo][lastXTo];
    board[lastYTo][lastXTo] = 0;
    if (beatenFigure != 0)
    {
        board[beatenFigureY][beatenFigureX] = beatenFigure;
    }

    if (lastMove.extraFigure != 0)
        board[lastYFrom][lastXFrom] = Pawn | (lastMove.extraFigure & colorWhite);

    canCastling = lastMove.canCastling;
    whiteTurn = !whiteTurn;

    return true;
}
