#include "ChessEngine.h"
#include <memory.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>

int ChessEngine::makeMove (const Move& move)
{

    /*for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << setw(2) << (int)board[i][j] << " ";
        }
        cout << endl;
    }*/
    if ( isValidMove(move) )
    {
        int ret = makeMoveLow (move);
        /*for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << setw(2) << (int)board[i][j] << " ";
            }
            cout << endl;
        }*/
        return ret;
    }
    return -1;
}

int ChessEngine::makeMoveLow (const Move& move)
{
    int from = move.from;
    int xFrom = from % 8;
    int yFrom = from / 8;

    int to = move.to;
    int xTo = to % 8;
    int yTo = to / 8;

    if (isWhite (board[yFrom][xFrom]))
    {
        whitePositions.push_back ( cti (xTo, yTo) );
        whitePositions.remove ( cti(xFrom, yFrom) );
    }
    else
    {
        blackPositions.push_back ( cti (xTo, yTo) );
        blackPositions.remove ( cti(xFrom, yFrom) );
    }


    ExtraMove eMove;
    eMove.from = move.from;
    eMove.to = move.to;
    eMove.extraFigure = 0;
    eMove.beatenFigure = 0;
    eMove.canCastling = canCastling;

    if ( board[yFrom][xFrom] & Rook && yFrom == 7 && xFrom == 0 )
        if (canCastling & WHITE_LEFT_CASTLING)
            canCastling ^= WHITE_LEFT_CASTLING;
    if ( board[yFrom][xFrom] & Rook && yFrom == 7 && xFrom == 7 )
        if (canCastling & WHITE_RIGHT_CASTLING)
            canCastling ^= WHITE_RIGHT_CASTLING;
    if ( board[yFrom][xFrom] & King && isWhite (board[yFrom][xFrom]) )
    {
        if (canCastling & WHITE_LEFT_CASTLING)
            canCastling ^= WHITE_LEFT_CASTLING;
        if (canCastling & WHITE_RIGHT_CASTLING)
            canCastling ^= WHITE_RIGHT_CASTLING;
        whiteKingPos = to;
    }

    if ( board[yFrom][xFrom] & Rook && yFrom == 0 && xFrom == 0 )
        if (canCastling & BLACK_LEFT_CASTLING)
            canCastling ^= BLACK_LEFT_CASTLING;
    if ( board[yFrom][xFrom] & Rook && yFrom == 0 && xFrom == 7 )
        if (canCastling & BLACK_RIGHT_CASTLING)
            canCastling ^= BLACK_RIGHT_CASTLING;
    if ( board[yFrom][xFrom] & King && !isWhite (board[yFrom][xFrom]) )
    {
        if (canCastling & BLACK_LEFT_CASTLING)
            canCastling ^= BLACK_LEFT_CASTLING;
        if (canCastling & BLACK_RIGHT_CASTLING)
            canCastling ^= BLACK_RIGHT_CASTLING;
        blackKingPos = to;
    }

    if ( board[yFrom][xFrom] & King && xTo == xFrom+2 )
    {
        if ( isWhite (board[yFrom][xFrom]) )
        {
            board[7][5] = board[7][7];
            board[7][7] = 0;
            whitePositions.remove (cti(7,7));
            whitePositions.push_back (cti(5,7));
        }
        else
        {
            board[0][5] = board[0][7];
            board[0][7] = 0;
            blackPositions.remove (cti(7,0));
            blackPositions.push_back (cti(5,0));
        }
    }
    if ( board[yFrom][xFrom] & King && xTo == xFrom-2 )
    {
        if ( isWhite (board[yFrom][xFrom]) )
        {
            board[7][3] = board[7][0];
            board[7][0] = 0;
            whitePositions.remove (cti(0,7));
            whitePositions.push_back (cti(3,7));
        }
        else
        {
            board[0][3] = board[0][0];
            board[0][0] = 0;
            blackPositions.remove (cti(0,0));
            blackPositions.push_back (cti(3,0));
        }
    }

    if ( board[yTo][xTo] != 0 )
        eMove.beatenFigure = board[yTo][xTo];

    if (yTo == 0 && board[yTo][xTo] & Pawn )
        board[yTo][xTo] = move.extra | colorWhite;
    if (yTo == 7 && board[yTo][xTo] & Pawn)
        board[yTo][xTo] = move.extra;

    ExtraMove lastMove ;
    if (lastMoves.size() == 0)
    {
        lastMove.from = 0;
        lastMove.to = 0;
    }
    else
    {
        lastMove = lastMoves.top();
    }
    int lastFrom = lastMove.from;
    int lastTo = lastMove.to;
    int lastXFrom = lastFrom % 8;
    int lastYFrom = lastFrom / 8;
    int lastXTo = lastTo % 8;
    int lastYTo = lastTo / 8;

    if ( yFrom == 3 )
    {
        if (xFrom+1 < 8 && lastYFrom == 1 && lastXFrom == xFrom+1 && lastYTo == 3 && lastXTo == xFrom+1 && xTo == xFrom+1)
        {
            if ( board[3][xFrom+1] & Pawn && board[yFrom][xFrom] & Pawn)
            {
                board[3][xFrom+1] = 0;
                blackPositions.remove (cti(xFrom+1, 3));
            }
        }
        if (xFrom-1 >= 0 && lastYFrom == 1 && lastXFrom == xFrom-1 && lastYTo == 3 && lastXTo == xFrom-1 && xTo == xFrom-1)
        {
            if ( board[3][xFrom-1] & Pawn && board[yFrom][xFrom] & Pawn )
            {
                board[3][xFrom-1] = 0;
                blackPositions.remove (cti(xFrom-1, 3));
            }
        }
    }

    if ( yFrom == 4 )
    {
        if (xFrom+1 < 8 && lastYFrom == 6 && lastXFrom == xFrom+1 && lastYTo == 4 && lastXTo == xFrom+1 && xTo == xFrom+1)
        {
            if ( board[4][xFrom+1] & Pawn && board[yFrom][xFrom] & Pawn )
            {
                whitePositions.remove (cti(xFrom+1, 4));
                board[4][xFrom+1] = 0;
            }
        }
        if (xFrom-1 >= 0 && lastYFrom == 6 && lastXFrom == xFrom-1 && lastYTo == 4 && lastXTo == xFrom-1 && xTo == xFrom-1)
        {
            if ( board[4][xFrom-1] & Pawn && board[yFrom][xFrom] & Pawn )
            {
                whitePositions.remove (cti(xFrom-1, 4));
                board[4][xFrom-1] = 0;
            }
        }
    }
    int newFigure = 0;
    if ( board[yFrom][xFrom] & Pawn )
    {
        if (yTo == 0)
            newFigure = move.extra | colorWhite;
        else if (yTo == 7)
            newFigure = move.extra;
    }

    board[yTo][xTo] = board[yFrom][xFrom];
    board[yFrom][xFrom] = 0;

    if (newFigure != 0)
    {
        board[yTo][xTo] = newFigure;
        eMove.extraFigure = newFigure;
    }

    whiteTurn = !whiteTurn;

    lastMoves.push (eMove);
    int ret = isEnd ();



    return ret;

}
