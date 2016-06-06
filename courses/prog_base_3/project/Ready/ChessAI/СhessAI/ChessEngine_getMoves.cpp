#include "ChessEngine.h"
#include <memory.h>
#include <iostream>
#include <cstdlib>

dbyte* ChessEngine::getAllMoves (dbyte* allMoves, int maxLen, int* res, bool bWhite) // optimized
{
    *res = 0;
    int i = rand () % 64;
    if (bWhite)
    {
        for (int c = 0; c < 64; c++)
        {
            i++;
            i %= 64;
            int x = i % 8;
            int y = i / 8;
            if ( board[y][x] != 0 && isWhite (board[y][x]) )
            {
                byte moves[32];
                int l = 0;
                getValidMovesLow(i, moves, &l);
                if (*res + l >= maxLen)
                    break;
                for (int j = 0; j < l; j++)
                    allMoves[*res+j] = MAKEWORD (i, moves[j]);
                *res += l;
            }
        }
    }
    else
    {
        for (int c = 0; c < 64; c++)
        {
            i++;
            i %= 64;
            int x = i % 8;
            int y = i / 8;
            if ( board[y][x] != 0 && !isWhite (board[y][x]) )
            {
                byte moves[32];
                int l = 0;
                getValidMovesLow(i, moves, &l);
                if (*res + l > maxLen)
                    break;
                for (int j = 0; j < l; j++)
                    allMoves[*res+j] = MAKEWORD (i, moves[j]);
                *res += l;
            }
        }
    }

    return allMoves;
}

byte* ChessEngine::getValidMoves (int from, byte moves[], int* lPtr) // optimized
{
    *lPtr = 0;
    int xFrom = from % 8;
    int yFrom = from / 8;
    if (from < 0 || from > 63)
        return (byte*)moves;
    bool bWhite = isWhite (board[yFrom][xFrom]);
    if (bWhite != whiteTurn)
        return (byte*)moves;

    return getValidMovesLow (from, moves, lPtr);
}


byte* ChessEngine::getValidMovesLow (int from, byte moves[], int* lPtr) // optimized
{
    int xFrom = from % 8;
    int yFrom = from / 8;

    if ( board[yFrom][xFrom] == 0 )
        return (byte*)moves;
    else if ( board[yFrom][xFrom] & Pawn )
        getPawnMoves(from, moves, lPtr);
    else if ( board[yFrom][xFrom] & Knight )
        getKnightMoves(from, moves, lPtr);
    else if ( board[yFrom][xFrom] & Bishop )
        getBishopMoves(from, moves, lPtr);
    else if ( board[yFrom][xFrom] & Rook )
        getRookMoves(from, moves, lPtr);
    else if ( board[yFrom][xFrom] & Queen )
        getQueenMoves(from, moves, lPtr);
    else if ( board[yFrom][xFrom] & King )
        getKingMoves(from, moves, lPtr);

    return (byte*)moves;
}

byte* ChessEngine::getRookMoves (int from, byte moves[], int* lPtr) // optimized
{
    int c = 0;

    int yFrom = from / 8;
    int xFrom = from % 8;


    for (int i = xFrom + 1; i < 8; i++)
        {
            if (board[yFrom][i] == 0)
            {
                if ( !isFigurePinned(from, cti(i, yFrom)) )
                    moves[c++] = cti(i, yFrom);
            }
            else if (isDifferentColor (board[yFrom][xFrom], board[yFrom][i]) )
            {
                if ( !isFigurePinned(from, cti(i, yFrom)) )
                    moves[c++] = cti(i, yFrom);
                break;
            }
            else
                break;

        }
    for (int i = xFrom - 1; i >= 0; i--)
    {
        if (board[yFrom][i] == 0)
        {
            if ( !isFigurePinned(from, cti(i, yFrom)) )
                moves[c++] = cti(i, yFrom);
        }
        else if (isDifferentColor (board[yFrom][xFrom], board[yFrom][i]) )
        {
            if ( !isFigurePinned(from, cti(i, yFrom)) )
                moves[c++] = cti (i, yFrom);
            break;
        }
        else
            break;

    }

    for (int i = yFrom + 1; i < 8; i++)
    {
        if (board[i][xFrom] == 0)
        {
            if ( !isFigurePinned(from, cti(xFrom, i)) )
                moves[c++] = cti(xFrom, i);
        }
        else if (isDifferentColor (board[yFrom][xFrom], board[i][xFrom]) )
        {
            if ( !isFigurePinned(from, cti(xFrom, i)) )
                moves[c++] = cti (xFrom, i);
            break;
        }
        else
            break;

    }

    for (int i = yFrom - 1; i >= 0; i--)
    {
        if (board[i][xFrom] == 0)
        {
            if ( !isFigurePinned(from, cti(xFrom, i)) )
                moves[c++] = cti(xFrom, i);
        }
        else if (isDifferentColor (board[yFrom][xFrom], board[i][xFrom]) )
        {
            if ( !isFigurePinned(from, cti(xFrom, i)) )
                moves[c++] = cti (xFrom, i);
            break;
        }
        else
            break;

    }

    *lPtr = c;
    return (byte*)moves;
}
byte* ChessEngine::getKnightMoves (int from, byte moves[], int* lPtr) // optimized
{
    int c = 0;
    *lPtr = 0;

    int yFrom = from / 8;
    int xFrom = from % 8;

    int x [] = {1, 2, -1, -2, 1, 2, -1, -2};
    int y [] = {2, 1, -2, -1, -2, -1, 2, 1};

    for (int i = 0; i < 8; i++)
    {
        if (xFrom + x[i] >= 0 && xFrom + x[i] < 8 && yFrom + y[i] >= 0 && yFrom + y[i] < 8)
        {
            if ( board[yFrom + y[i]][xFrom + x[i]] == 0 ||
                isDifferentColor(board[yFrom][xFrom], board[yFrom + y[i]][xFrom + x[i]]) )
                if (!isFigurePinned(from, cti (xFrom + x[i],yFrom + y[i])))
                    moves[c++] = (yFrom+y[i])*8 + xFrom + x[i];
        }
    }
    *lPtr = c;
    return (byte*)moves;
}
byte* ChessEngine::getBishopMoves (int from, byte moves[], int* lPtr) // optimized
{
    int c = 0;
    *lPtr = 0;

    int yFrom = from / 8;
    int xFrom = from % 8;

    int i, j;
    for (i = xFrom + 1, j = yFrom + 1; i < 8 && j < 8; i++, j++)
                {
                    if (board[j][i] == 0)
                    {
                        if ( !isFigurePinned(from, cti(i, j)) )
                            moves[c++] = cti (i, j);
                    }
                    else if (isDifferentColor (board[yFrom][xFrom], board[j][i]) )
                    {
                        if ( !isFigurePinned(from, cti(i, j)) )
                            moves[c++] = cti(i, j);
                        break;
                    }
                    else
                        break;

                }

    for (i = xFrom + 1, j = yFrom - 1; i < 8 && j >= 0; i++, j--)
            {
                if (board[j][i] == 0)
                {
                    if ( !isFigurePinned(from, cti(i, j)) )
                        moves[c++] = cti (i, j);
                }
                else if (isDifferentColor (board[yFrom][xFrom], board[j][i]) )
                {
                    if ( !isFigurePinned(from, cti(i, j)) )
                        moves[c++] = cti(i, j);
                    break;
                }
                else
                    break;

            }

    for (i = xFrom - 1, j = yFrom + 1; i >= 0 && j < 8; i--, j++)
            {
                if (board[j][i] == 0)
                {
                    if ( !isFigurePinned(from, cti(i, j)) )
                        moves[c++] = cti (i, j);
                }
                else if (isDifferentColor (board[yFrom][xFrom], board[j][i]) )
                {
                    if ( !isFigurePinned(from, cti(i, j)) )
                        moves[c++] = cti(i, j);
                    break;
                }
                else
                    break;

            }

    for (i = xFrom - 1, j = yFrom - 1; i >= 0 && j >= 0; i--, j--)
    {
                if (board[j][i] == 0)
                {
                    if ( !isFigurePinned(from, cti(i, j)) )
                        moves[c++] = cti (i, j);
                }
                else if (isDifferentColor (board[yFrom][xFrom], board[j][i]) )
                {
                    if ( !isFigurePinned(from, cti(i, j)) )
                        moves[c++] = cti(i, j);
                    break;
                }
                else
                    break;

     }
    *lPtr = c;
    return (byte*)moves;
}
byte* ChessEngine::getQueenMoves (int from, byte moves[], int* lPtr)  // optimized
{
    byte moves1[16];
    byte moves2[16];
    int l1 = 0;
    int l2 = 0;

    getRookMoves (from, moves1, &l1);
    getBishopMoves (from, moves2, &l2);

    int c = l1 + l2;

    for (int i = 0; i < l1; i++)
        moves[i] = moves1[i];
    for (int i = l1; i < l1 + l2; i++)
        moves[i] = moves2[i-l1];
    *lPtr = c;
}
byte* ChessEngine::getKingMoves (int from, byte moves[], int* lPtr) // optimized
{
    int c = 0;
    int yFrom = from / 8;
    int xFrom = from % 8;

    int x[] = {xFrom + 1, xFrom + 1, xFrom,     xFrom - 1, xFrom - 1, xFrom - 1, xFrom,     xFrom + 1};
    int y[] = {yFrom,     yFrom - 1, yFrom - 1, yFrom - 1, yFrom,     yFrom + 1, yFrom + 1, yFrom + 1};

    for (int i = 0; i < 8; i++)
    {
        if (x[i] >= 0 && x[i] < 8 && y[i] >= 0 && y[i] < 8)
        {
            if ( board[ y[i] ][ x[i] ] == 0 || isDifferentColor ( board[yFrom][xFrom], board[ y[i] ][ x[i] ] ) )
            {
                byte temp = board[yFrom][xFrom];
                bool bWhite = !isWhite (board[yFrom][xFrom] );
                board[yFrom][xFrom] = 0;
                if ( !isBeaten ( cti (x[i], y[i]), bWhite) )
                    moves[c++] = cti (x[i], y[i]);
                board[yFrom][xFrom] = temp;
            }
        }
    }

    bool bWhite = isWhite (board[yFrom][xFrom]);

    if (bWhite)
    {
            if ( canCastling & WHITE_LEFT_CASTLING )
            {
                bool bCastling = true;
                for (int i = 2; i < 4; i++)
                    if ( board[7][i] != 0 || isBeaten(cti(i, 7), false) )
                    {
                        bCastling = false;
                        break;
                    }
                if (board[7][1] != 0)
                    bCastling = false;
                else if (board[7][0] != (Rook | colorWhite))
                    bCastling = false;
                else if ( isBeaten ( cti(4, 7), false ) )
                    bCastling = false;

                if (bCastling)
                {
                    moves[c++] = 58;
                }

            }
            if ( canCastling & WHITE_RIGHT_CASTLING )
            {
                bool bCastling = true;
                for (int i = 5; i < 7; i++)
                    if ( board[7][i] != 0 || isBeaten(cti(i, 7), false) )
                    {
                        bCastling = false;
                        break;
                    }
                if ( isBeaten ( cti(4, 7), false ) )
                    bCastling = false;
                else if (board[7][7] != (Rook | colorWhite))
                    bCastling = false;

                if (bCastling)
                {
                    moves[c++] = 62;
                }
            }
    }
    else
    {
            if ( canCastling & BLACK_LEFT_CASTLING )
            {
                bool bCastling = true;
                for (int i = 2; i < 4; i++)
                    if ( board[0][i] != 0 || isBeaten(cti(i, 0), true) )
                    {
                        bCastling = false;
                        break;
                    }
                if (board[0][2] != 0)
                    bCastling = false;
                else if ( isBeaten ( cti(4, 0), true ) )
                    bCastling = false;
                else if (board[0][0] != Rook)
                    bCastling = false;
                if (bCastling)
                {
                    moves[c++] = 2;
                }

            }
            if ( canCastling & BLACK_RIGHT_CASTLING )
            {
                bool bCastling = true;
                for (int i = 5; i < 7; i++)
                    if ( board[0][i] != 0 || isBeaten(cti(i, 0), true) )
                    {
                        bCastling = false;
                        break;
                    }
                if ( isBeaten ( cti(4, 0), true ) )
                    bCastling = false;
                else if (board[0][7] != Rook)
                    bCastling = false;

                if (bCastling)
                {
                    moves[c++] = 6;
                }
            }
    }

    *lPtr = c;
    return (byte*)moves;
}
byte* ChessEngine::getPawnMoves (int from, byte moves[], int* lPtr) // optimized
{
    int c = 0;
    *lPtr = 0;
    int yFrom = from / 8;
    int xFrom = from % 8;

    ExtraMove lastMove;
    if (lastMoves.size() == 0)
    {
        lastMove.from = 0;
        lastMove.to = 0;
    }
    else
        lastMove = lastMoves.top ();
    int lastFrom = lastMove.from;
    int lastTo = lastMove.to;
    int lastXFrom = lastFrom % 8;
    int lastYFrom = lastFrom / 8;
    int lastXTo = lastTo % 8;
    int lastYTo = lastTo / 8;

    if (isWhite (board[yFrom][xFrom]))
        {
            if (board[yFrom - 1][xFrom] == 0)
            {
                if ( !isFigurePinned( from, cti (xFrom, yFrom-1) ) )
                    moves[c++] = cti (xFrom, yFrom-1);

                if (yFrom == 6 && board[yFrom - 2][xFrom] == 0 )
                {
                    if ( !isFigurePinned( from, cti (xFrom, yFrom-2) ) )
                        moves[c++] = cti (xFrom, yFrom-2);
                }
            }
            if (xFrom+1 < 8 && board[yFrom-1][xFrom+1] != 0 && !isWhite (board[yFrom-1][xFrom+1]))
            {
                if ( !isFigurePinned( from, cti (xFrom+1, yFrom-1) ) )
                    moves[c++] = cti (xFrom+1, yFrom - 1);
            }
            if (xFrom-1 >= 0 && board[yFrom-1][xFrom-1] != 0 && !isWhite (board[yFrom-1][xFrom-1]) )
            {
                if ( !isFigurePinned( from, cti (xFrom-1, yFrom-1) ) )
                    moves[c++] = cti (xFrom-1, yFrom - 1);
            }

            if ( yFrom == 3 && lastYFrom == 1 && lastYTo == 3)
            {
                if (lastXFrom == xFrom+1 && lastXTo == xFrom+1)
                {
                    if ( board[3][xFrom+1] & Pawn )
                    {
                        if ( !isFigurePinned( from, cti (xFrom+1, yFrom-1) ) )
                            moves[c++] = cti (xFrom+1, yFrom-1);
                    }
                }
                if (lastXFrom == xFrom-1 && lastXTo == xFrom-1)
                {
                    if ( board[3][xFrom-1] & Pawn )
                    {
                        if ( !isFigurePinned( from, cti (xFrom-1, yFrom-1) ) )
                            moves[c++] = cti (xFrom-1, yFrom-1);
                    }
                }
            }
        }
        else
        {
            if (board[yFrom + 1][xFrom] == 0)
            {
                if ( !isFigurePinned( from, cti (xFrom, yFrom+1) ) )
                    moves[c++] = cti (xFrom, yFrom+1);

                if (yFrom == 1 && board[yFrom + 2][xFrom] == 0 )
                {
                    if ( !isFigurePinned( from, cti (xFrom, yFrom+2) ) )
                        moves[c++] = cti (xFrom, yFrom+2);
                }
            }
            if (xFrom+1 < 8 && board[yFrom+1][xFrom+1] != 0 && isWhite (board[yFrom+1][xFrom+1]))
            {
                if ( !isFigurePinned( from, cti (xFrom+1, yFrom+1) ) )
                    moves[c++] = cti (xFrom+1, yFrom+1);
            }
            if (xFrom-1 >= 0 && board[yFrom+1][xFrom-1] != 0 && isWhite (board[yFrom+1][xFrom-1]) )
            {
                if ( !isFigurePinned( from, cti (xFrom-1, yFrom+1) ) )
                    moves[c++] = cti (xFrom-1, yFrom + 1);
            }

            if ( yFrom == 4 && lastYFrom == 6 && lastYTo == 4)
            {
                if (lastXFrom == xFrom+1 && lastXTo == xFrom+1)
                {
                    if ( board[4][xFrom+1] & Pawn )
                    {
                        if ( !isFigurePinned( from, cti (xFrom+1, yFrom+1) ) )
                            moves[c++] = cti (xFrom+1, yFrom+1);
                    }
                }
                if (lastXFrom == xFrom-1 && lastXTo == xFrom-1)
                {
                    if ( board[4][xFrom-1] & Pawn )
                    {
                        if ( !isFigurePinned( from, cti (xFrom-1, yFrom+1) ) )
                            moves[c++] = cti (xFrom-1, yFrom+1);
                    }
                }
            }
        }
    *lPtr = c;
    return (byte*)moves;
}
