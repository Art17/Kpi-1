#include "ChessEngine.h"
#include <memory.h>
#include <iostream>

bool ChessEngine::isFigurePinned (int from, int to)
{
    int xFrom = from % 8;
    int yFrom = from / 8;
    int xTo = to % 8;
    int yTo = to / 8;
    bool bRet = false;

    if (xTo < 8 && xTo >= 0 && yTo >= 0 && yTo < 8 &&  board[yTo][xTo] == 0 || isDifferentColor( board[yFrom][xFrom], board[yTo][xTo] ) )
    {
        int fromFigure = board[yFrom][xFrom];
        int toFigure = board[yTo][xTo];
        int temp = board[yTo][xTo];
        board[yTo][xTo] = fromFigure;
        board[yFrom][xFrom] = 0;
        if ( isBeaten ( isWhite (fromFigure) ? whiteKingPos : blackKingPos, !isWhite (fromFigure)  ))
            {
                bRet = true;
            }
        board[yFrom][xFrom] = fromFigure;
        board[yTo][xTo] = toFigure;
    }

    return bRet;
}

inline bool ChessEngine::isDifferentColor(int x1, int x2) const
{
    return (((x1 & colorWhite) ^ (x2 & colorWhite)) == colorWhite);
}

inline bool ChessEngine::isWhite (int figure) const
{
    return (figure & colorWhite) == colorWhite;
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

    for (list<byte>::iterator it = whitePositions.begin (); it != whitePositions.end(); it++)
    {
        int figure = board[(*it)/8][(*it)%8];
        if (figure == 0)
            cout << "WHITE FIGURE HELL" << endl;
        whitePower += getFigurePower (figure);
        if (figure & Pawn)
            bPawnDetected = true;
        else if (figure & Bishop)
            whiteBishops |= (isWhiteTile(*it) ? BLACK_TILE_BISHOP : WHITE_TILE_BISHOP);
        else if (figure != 0 && !(figure & King))
            whiteBishops |= OTHER_FIGURE;
        byte moves[32];
        int l = 0;
        getValidMoves(*it, moves, &l);
        if (l != 0)
            whiteCanMove = true;
    }

    for (list<byte>::iterator it = blackPositions.begin (); it != blackPositions.end(); it++)
    {
        int figure = board[(*it)/8][(*it)%8];
        if (figure == 0)
            cout << "BLACK FIGURE HELL" << endl;
        blackPower += getFigurePower(figure);
        if (figure & Pawn)
            bPawnDetected = true;
        else if (figure & Bishop)
            blackBishops |= (isWhiteTile(*it) ? BLACK_TILE_BISHOP : WHITE_TILE_BISHOP);
        else if (figure != 0 && !(figure & King))
            blackBishops |= OTHER_FIGURE;
        byte moves[32];
        int l = 0;
        getValidMoves(*it, moves, &l);
        if (l != 0)
            blackCanMove = true;
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
    cout << "Bishops" << whiteBishops << " " << blackBishops << endl;
    cout << "Power" << whitePower << " " << blackPower << endl;
    cout << "Size " << whitePositions.size() << " " << blackPositions.size() << endl;

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

bool ChessEngine::isWhiteTile (int tile)
{
    int xFrom = tile % 8;
    int yFrom = tile / 8;

    if (yFrom % 2 == 0)
        return !(xFrom % 2);
    else
        return xFrom % 2;

}

int ChessEngine::getFigurePower (int figure)
{
    if (figure & Pawn)
        return 1;
    else if (figure & Knight || figure & Bishop)
        return 3;
    else if (figure & Rook)
        return 5;
    else if (figure & Queen)
        return 9;
    else if (figure & King)
        return 0;

    return 0;
}

bool ChessEngine::isBeaten (int from, bool bWhite) const
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
        if ( yFrom+1 < 8 && xFrom+1 < 8 && board[yFrom+1][xFrom+1] & Pawn && bWhite == isWhite (board[yFrom+1][xFrom+1]))
            return true;
        if ( yFrom+1 < 8 && xFrom-1 >= 0 && board[yFrom+1][xFrom-1] & Pawn && bWhite == isWhite (board[yFrom+1][xFrom-1]) )
            return true;
    }
    else
    {
        if ( yFrom-1 >= 0 && xFrom+1 < 8 && board[yFrom-1][xFrom+1] & Pawn && bWhite == isWhite (board[yFrom-1][xFrom+1]))
            return true;
        if ( yFrom-1 >= 0 && xFrom-1 >= 0 && board[yFrom-1][xFrom-1] & Pawn && bWhite == isWhite (board[yFrom-1][xFrom-1]) )
            return true;
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

int ChessEngine::cti (int x, int y) const
{
    return y*8 + x;
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
