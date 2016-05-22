#include "ChessEngine.h"
#include <memory.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>

int ChessEngine::makeMove (const Move& move)
{
    if ( isValidMove(move) )
    {
        int ret = makeMoveLow (move);
        return ret;
    }
    return -1;
}

int ChessEngine::makeMoveLow (const Move& move)
{
    makeMoveLL (move);
    return isEnd ();
}

/*void ChessEngine::fastMove (const Move& move, byte pBoard[8][8])
{
    int from = move.from;
    int xFrom = from % 8;
    int yFrom = from / 8;

    int to = move.to;
    int xTo = to % 8;
    int yTo = to / 8;

    int newFigure = 0;

    if ( pBoard[yFrom][xFrom] & Rook )
    {
        if (yFrom == 7)
        {
            if (xFrom == 0)
            {
                if (canCastlingT & WHITE_LEFT_CASTLING)
                    canCastlingT ^= WHITE_LEFT_CASTLING;
            }
            else if (xFrom == 7)
            {
                if (canCastlingT & WHITE_RIGHT_CASTLING)
                    canCastlingT ^= WHITE_RIGHT_CASTLING;
            }

        }
        else if (yFrom == 0)
        {
            if (xFrom == 0)
            {
                if (canCastlingT & BLACK_LEFT_CASTLING)
                    canCastlingT ^= BLACK_LEFT_CASTLING;
            }
            else if (xFrom == 7)
            {
                if (canCastlingT & BLACK_RIGHT_CASTLING)
                    canCastlingT ^= BLACK_RIGHT_CASTLING;
            }
        }
    }
    else if ( pBoard[yFrom][xFrom] & King )
    {
        if ( isWhite (pBoard[yFrom][xFrom]) )
        {
            if (canCastlingT & WHITE_LEFT_CASTLING)
                canCastlingT ^= WHITE_LEFT_CASTLING;
            if (canCastlingT & WHITE_RIGHT_CASTLING)
                canCastlingT ^= WHITE_RIGHT_CASTLING;
            whiteKingPos = to;

            if (xTo == xFrom+2)
            {
                pBoard[7][5] = pBoard[7][7];
                pBoard[7][7] = 0;
            }
            else if (xTo == xFrom-2)
            {
                pBoard[7][3] = pBoard[7][0];
                pBoard[7][0] = 0;
            }

        }
        else
        {
            if (canCastlingT & BLACK_LEFT_CASTLING)
                canCastlingT ^= BLACK_LEFT_CASTLING;
            if (canCastlingT & BLACK_RIGHT_CASTLING)
                canCastlingT ^= BLACK_RIGHT_CASTLING;
            blackKingPos = to;

            if (xTo == xFrom+2)
            {
                pBoard[0][5] = pBoard[0][7];
                pBoard[0][7] = 0;
            }
            else if (xTo == xFrom-2)
            {
                pBoard[0][3] = pBoard[0][0];
                pBoard[0][0] = 0;
            }
        }
    }
    else if (pBoard[yFrom][xFrom] & Pawn)
    {
        if (yTo == 0)
            newFigure = move.extra | colorWhite;
        else if (yTo == 7)
            newFigure = move.extra;
        else if (pBoard[yTo][xTo] == 0)
        {
            if (xTo == xFrom+1)
            {
                pBoard[yFrom][xFrom+1] = 0;
            }
            else if (xTo == xFrom-1)
            {
                pBoard[yFrom][xFrom-1] = 0;
            }
        }
    }

    pBoard[yTo][xTo] = pBoard[yFrom][xFrom];
    pBoard[yFrom][xFrom] = 0;

    if (newFigure != 0)
    {
        pBoard[yTo][xTo] = newFigure;
    }
}*/

void ChessEngine::makeMoveLL (const Move& move)
{
    int from = move.from;
    int xFrom = from % 8;
    int yFrom = from / 8;

    int to = move.to;
    int xTo = to % 8;
    int yTo = to / 8;

    int newFigure = 0;

    ExtraMove eMove;
    eMove.from = move.from;
    eMove.to = move.to;
    eMove.extraFigure = 0;
    eMove.beatenFigure = 0;
    eMove.beatenFigurePos = -1;
    byte beatenFigureX = -1;
    byte beatenFigureY = -1;

    eMove.castlingFigureFrom = -1;
    eMove.castlingFigureTo = -1;

    eMove.canCastling = canCastling;

    if ( board[yFrom][xFrom] & Rook )
    {
        if (yFrom == 7)
        {
            if (xFrom == 0)
            {
                if (canCastling & WHITE_LEFT_CASTLING)
                    canCastling ^= WHITE_LEFT_CASTLING;
            }
            else if (xFrom == 7)
            {
                if (canCastling & WHITE_RIGHT_CASTLING)
                    canCastling ^= WHITE_RIGHT_CASTLING;
            }

        }
        else if (yFrom == 0)
        {
            if (xFrom == 0)
            {
                if (canCastling & BLACK_LEFT_CASTLING)
                    canCastling ^= BLACK_LEFT_CASTLING;
            }
            else if (xFrom == 7)
            {
                if (canCastling & BLACK_RIGHT_CASTLING)
                    canCastling ^= BLACK_RIGHT_CASTLING;
            }
        }
    }
    else if ( board[yFrom][xFrom] & King )
    {
        if ( isWhite (board[yFrom][xFrom]) )
        {
            if (canCastling & WHITE_LEFT_CASTLING)
                canCastling ^= WHITE_LEFT_CASTLING;
            if (canCastling & WHITE_RIGHT_CASTLING)
                canCastling ^= WHITE_RIGHT_CASTLING;
            whiteKingPos = to;

            if (xTo == xFrom+2)
            {
                eMove.castlingFigureFrom = cti (7,7);
                eMove.castlingFigureTo = cti (5, 7);
                board[7][5] = board[7][7];
                board[7][7] = 0;
            }
            else if (xTo == xFrom-2)
            {
                eMove.castlingFigureFrom = cti (0,7);
                eMove.castlingFigureTo = cti (3, 7);
                board[7][3] = board[7][0];
                board[7][0] = 0;
            }

        }
        else
        {
            if (canCastling & BLACK_LEFT_CASTLING)
                canCastling ^= BLACK_LEFT_CASTLING;
            if (canCastling & BLACK_RIGHT_CASTLING)
                canCastling ^= BLACK_RIGHT_CASTLING;
            blackKingPos = to;

            if (xTo == xFrom+2)
            {
                eMove.castlingFigureFrom = cti (7,0);
                eMove.castlingFigureTo = cti (5, 0);
                board[0][5] = board[0][7];
                board[0][7] = 0;
            }
            else if (xTo == xFrom-2)
            {
                eMove.castlingFigureFrom = cti (0,0);
                eMove.castlingFigureTo = cti (3, 0);
                board[0][3] = board[0][0];
                board[0][0] = 0;
            }
        }
    }
    else if (board[yFrom][xFrom] & Pawn)
    {
        if (yTo == 0)
            newFigure = move.extra | colorWhite;
        else if (yTo == 7)
            newFigure = move.extra;
        else if (board[yTo][xTo] == 0)
        {
            if (xTo == xFrom+1)
            {
                eMove.beatenFigure = board[yFrom][xFrom+1];
                board[yFrom][xFrom+1] = 0;
                beatenFigureX = xFrom+1;
                beatenFigureY = yFrom;
            }
            else if (xTo == xFrom-1)
            {
                eMove.beatenFigure = board[yFrom][xFrom-1];
                board[yFrom][xFrom-1] = 0;
                beatenFigureX = xFrom-1;
                beatenFigureY = yFrom;
            }
        }
    }
    if ( board[yTo][xTo] != 0 )
    {
        eMove.beatenFigure = board[yTo][xTo];
        beatenFigureX = xTo;
        beatenFigureY = yTo;
    }

    board[yTo][xTo] = board[yFrom][xFrom];
    board[yFrom][xFrom] = 0;

    if (newFigure != 0)
    {
        board[yTo][xTo] = newFigure;
        eMove.extraFigure = newFigure;
    }

    whiteTurn = !whiteTurn;

    if (eMove.beatenFigure != 0)
        eMove.beatenFigurePos = cti (beatenFigureX, beatenFigureY);

    lastMoves.push (eMove);
}

