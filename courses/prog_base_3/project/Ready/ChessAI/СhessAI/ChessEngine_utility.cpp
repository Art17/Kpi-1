#include "ChessEngine.h"
#include <memory.h>
#include <iostream>

bool ChessEngine::isFigurePinned (int from, int to) // optimized
{
    int xFrom = from % 8;
    int yFrom = from / 8;
    int xTo = to % 8;
    int yTo = to / 8;
    bool bRet = false;

    int fromFigure = board[yFrom][xFrom];
    int toFigure = board[yTo][xTo];
    board[yTo][xTo] = fromFigure;
    board[yFrom][xFrom] = 0;
    if ( isBeaten ( isWhite (fromFigure) ? whiteKingPos : blackKingPos, !isWhite (fromFigure)  ))
        {
            bRet = true;
        }
    board[yFrom][xFrom] = fromFigure;
    board[yTo][xTo] = toFigure;

    return bRet;
}


int ChessEngine::isEnd ()
{
    bool whiteCanMove = false;
    bool blackCanMove = false;
    int whitePower = 0;
    int blackPower = 0;
    bool bPawnDetected = false;
#define WHITE_TILE_BISHOP 1
#define BLACK_TILE_BISHOP 2
#define OTHER_FIGURE 4
    int whiteBishops = 0;
    int blackBishops = 0;

    for (int i = 0; i < 64; i++)
    {
        int x = i % 8;
        int y = i / 8;
        if (board[y][x] != 0)
        {
            if (isWhite (board[y][x]))
            {
                int figure = board[y][x];
                whitePower += getFigurePower (figure);
                if (figure & Pawn)
                    bPawnDetected = true;
                else if (figure & Bishop)
                    whiteBishops |= (((i)%2) ? BLACK_TILE_BISHOP : WHITE_TILE_BISHOP);
                else if (figure != 0 && !(figure & King))
                    whiteBishops |= OTHER_FIGURE;
                byte moves[32];
                int l = 0;
                getValidMoves(i, moves, &l);
                if (l != 0)
                    whiteCanMove = true;
            }
            else
            {
                int figure = board[y][x];
                blackPower += getFigurePower(figure);
                if (figure & Pawn)
                    bPawnDetected = true;
                else if (figure & Bishop)
                    blackBishops |= (((i)%2) ? BLACK_TILE_BISHOP : WHITE_TILE_BISHOP);
                else if (figure != 0 && !(figure & King))
                    blackBishops |= OTHER_FIGURE;
                byte moves[32];
                int l = 0;
                getValidMoves(i, moves, &l);
                if (l != 0)
                    blackCanMove = true;
            }
        }
    }

    if (whiteTurn)
    {
        if (!whiteCanMove && isBeaten(whiteKingPos, false))
            return BLACK_WON;
        if (!whiteCanMove && !isBeaten(whiteKingPos, false))
            return DRAW;
    }
    else
    {
        if (!blackCanMove && isBeaten(blackKingPos, true))
            return WHITE_WON;
        if (!blackCanMove && !isBeaten(blackKingPos, true))
            return DRAW;
    }

    if (!bPawnDetected)
    {
        if (whitePower < 5 && blackPower < 5)
        {
            return DRAW;
        }
        if (blackPower < 5 && (whiteBishops == WHITE_TILE_BISHOP || whiteBishops == BLACK_TILE_BISHOP))
            return DRAW;
        if (whitePower < 5 && (blackBishops == WHITE_TILE_BISHOP || blackBishops == BLACK_TILE_BISHOP))
            return DRAW;
    }

    return ACTIVE_GAME;
}


bool ChessEngine::isBeaten (int from, bool bWhite) const // optimized
{
    int xFrom = from % 8;
    int yFrom = from / 8;

    /* Knight */
    int x [] = {1, 2, -1, -2, 1, 2, -1, -2};
    int y [] = {2, 1, -2, -1, -2, -1, 2, 1};

    for (int i = 0; i < 8; i++)
    {
        if (xFrom + x[i] >= 0 && xFrom + x[i] < 8 && yFrom + y[i] >= 0 && yFrom + y[i] < 8)
        {
            if ( board[yFrom + y[i]][xFrom + x[i]] & Knight && isWhite (board[yFrom + y[i]][xFrom + x[i]]) == bWhite )
                return true;
        }
    }
    /* ----- */

    /* Rook and Queen */
    for (int i = xFrom + 1; i < 8; i++)
        {
            if (board[yFrom][i] == 0)
                continue;
            else if (board[yFrom][i] & Rook || board[yFrom][i] & Queen)
            {
                if (isWhite (board[yFrom][i]) == bWhite)
                    return true;
                else
                    break;
            }
            else
                break;
        }
    for (int i = xFrom - 1; i >= 0; i--)
        {
            if (board[yFrom][i] == 0)
                continue;
            else if (board[yFrom][i] & Rook || board[yFrom][i] & Queen)
            {
                if (isWhite (board[yFrom][i]) == bWhite)
                    return true;
                else
                    break;
            }
            else
                break;
        }
    for (int i = yFrom + 1; i < 8; i++)
        {
            if (board[i][xFrom] == 0)
                continue;
            else if (board[i][xFrom] & Rook || board[i][xFrom] & Queen)
            {
                if (isWhite (board[i][xFrom]) == bWhite)
                    return true;
                else
                    break;
            }
            else
                break;
        }
    for (int i = yFrom - 1; i >= 0; i--)
        {
            if (board[i][xFrom] == 0)
                continue;
            else if (board[i][xFrom] & Rook || board[i][xFrom] & Queen)
            {
                if (isWhite (board[i][xFrom]) == bWhite)
                    return true;
                else
                    break;
            }
            else
                break;
        }

    /* ---- */

    /* Pawn */
    if (bWhite)
    {
        if (yFrom + 1 < 8)
        {
            if (xFrom+1 < 8 && board[yFrom+1][xFrom+1] & Pawn && bWhite == isWhite (board[yFrom+1][xFrom+1]))
                return true;
            if (xFrom-1 >= 0 && board[yFrom+1][xFrom-1] & Pawn && bWhite == isWhite (board[yFrom+1][xFrom-1]) )
                return true;
        }
    }
    else
    {
        if (yFrom-1 >= 0)
        {
            if (xFrom+1 < 8 && board[yFrom-1][xFrom+1] & Pawn && bWhite == isWhite (board[yFrom-1][xFrom+1]))
                return true;
            if (xFrom-1 >= 0 && board[yFrom-1][xFrom-1] & Pawn && bWhite == isWhite (board[yFrom-1][xFrom-1]) )
                return true;
        }
    }
    /* --- */

    /* King */
    {
        int x[] = {xFrom + 1, xFrom + 1, xFrom,     xFrom - 1, xFrom - 1, xFrom - 1, xFrom,     xFrom + 1};
        int y[] = {yFrom,     yFrom - 1, yFrom - 1, yFrom - 1, yFrom,     yFrom + 1, yFrom + 1, yFrom + 1};

        for (int i = 0; i < 8; i++)
        {
            if (x[i] >= 0 && x[i] < 8 && y[i] >= 0 && y[i] < 8 &&
                board[ y[i] ][ x[i] ] & King && bWhite == isWhite ( board[ y[i] ][ x[i] ] ) )
                return true;
        }
    }
    /* --- */

    /* Bishop and queen */
    int i, j;
    for (i = xFrom + 1, j = yFrom+1; i < 8 && j < 8; i++, j++)
        {
            if (board[j][i] == 0)
                continue;
            else if (board[j][i] & Bishop || board[j][i] & Queen)
            {
                if (isWhite (board[j][i]) == bWhite)
                    return true;
                else
                    break;
            }
            else
                break;
        }
    for (i = xFrom-1, j = yFrom+1; i >= 0 && j < 8; i--, j++)
        {
            if (board[j][i] == 0)
                continue;
            else if (board[j][i] & Bishop || board[j][i] & Queen)
            {
                if (isWhite (board[j][i]) == bWhite)
                    return true;
                else
                    break;
            }
            else
                break;
        }
    for (i = xFrom+1, j = yFrom-1; i < 8 && j >= 0; i++, j--)
        {
            if (board[j][i] == 0)
                continue;
            else if (board[j][i] & Bishop || board[j][i] & Queen)
            {
                if (isWhite (board[j][i]) == bWhite)
                    return true;
                else
                    break;
            }
            else
                break;
        }
    for (i = xFrom-1, j = yFrom-1; i >= 0 && j >= 0; i--, j--)
        {
            if (board[j][i] == 0)
                continue;
            else if (board[j][i] & Bishop || board[j][i] & Queen)
            {
                if (isWhite (board[j][i]) == bWhite)
                    return true;
                else
                    break;
            }
            else
                break;
        }
    /* --- */

    return false;
}

bool ChessEngine::isValidMove (const Move& move)
{
    int from = move.from;
    int to = move.to;

    if (from < 0 || from > 63 || to < 0 || to > 63 )
        return false;
    byte moves[32];
    int length;
    getValidMoves(from, moves, &length);

    for (int i = 0; i < length; i++)
        if ( to == moves[i] )
            return true;
    return false;
}

int ChessEngine::getKingPos(bool bWhite) const
{
    if (bWhite)
        return whiteKingPos;
    else
        return blackKingPos;
}

bool ChessEngine::isCheck (bool bWhite) const
{
    if (bWhite)
        return isBeaten (whiteKingPos, false);
    else
        return isBeaten (blackKingPos, true);
}
