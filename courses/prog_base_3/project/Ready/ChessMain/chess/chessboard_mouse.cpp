#include "chessboard.h"
#include "resources.h"

#include <chessboard_movethread.h>
#include <selectfiguredialog.h>

#include <iostream>

using namespace std;

void ChessBoard::mousePressEvent(QMouseEvent* mouseEvent)
{
    if (bLocked)
        return;

    int x = mouseEvent->x();
    int y = mouseEvent->y();

    if (x >= boardWidth || y >= boardHeight)
        return;

    int tileX = x / boardTileWidth;
    int tileY = y / boardTileHeight;

    if (tileX == iSelectedTileX && tileY == iSelectedTileY)
    {
        unselect ();
        return;
    }

    if (iSelectedFigure == -1)
    {
        select (tileX, tileY);
        rs_Selected.setPosition(boardTileWidth*iSelectedTileX,
                                 boardTileHeight*iSelectedTileY);
    }
    else
    {
        if ( bValid[tileY][tileX] )
        {
            Move move;
            move.from = (iSelectedTileY)*8 + iSelectedTileX;
            move.to = tileY*8 + tileX;
            int newFigure = 0;

            if (figuresTable[iSelectedTileY][iSelectedTileX] & Pawn)
            {
                if (tileY == 0 || tileY == 7)
                {
                    if ( selectDialog->exec() )
                    {
                        newFigure = selectDialog->getEnteredValue();
                    }
                }
            }
            if (newFigure != 0)
                move.extra = newFigure;

            if ( makeMove (move) > 0 )
            {
                bLocked = true;
                unselect ();
                return;
            }

            if (bAgainstComputer)
            {
                bLocked = true;
                cbct->start();
            }
        }
            unselect ();
    }
}

void ChessBoard::select (int tileX, int tileY)
{
    iSelectedFigure = indexTable[tileY][tileX];
    iSelectedTileX = tileX;
    iSelectedTileY = tileY;
    int from = 0;

    from = tileY*8 + tileX;
    byte validMoves[32];
    int l;

    chessEng->getValidMoves(from, (byte*)validMoves, &l);

    for (int i = 0; i < l; i++)
    {
        int x = validMoves[i] % 8;
        int y = validMoves[i] / 8;

         bValid[y][x] = true;

        if (figuresTable[y][x] != 0)
        {
            rs_ValidMoveHighlight[y][x].setFillColor(Color (255,0,0,128));
        }
        else if (figuresTable[iSelectedTileY][iSelectedTileX] & Pawn)
        {
            if (x+1 < 8 && iSelectedTileX == x+1)
            {
                rs_ValidMoveHighlight[y][x].setFillColor(Color (255,0,0,128));
            }
            else if (x-1 >= 0 && iSelectedTileX == x-1)
            {
                rs_ValidMoveHighlight[y][x].setFillColor(Color (255,0,0,128));
            }
            else if (y == 0 || y == 7)
            {
                rs_ValidMoveHighlight[y][x].setFillColor(Color (148,0,211,92));
            }
            else
                rs_ValidMoveHighlight[y][x].setFillColor (Color (0, 255, 0, 128));

        }
        else if (figuresTable[iSelectedTileY][iSelectedTileX] & King)
        {
            if (x+2 < 8 && iSelectedTileX == x+2)
            {
                rs_ValidMoveHighlight[y][x].setFillColor(Color (148,0,211,92));
            }
            else if (x-2 >= 0 && iSelectedTileX == x-2)
            {
                rs_ValidMoveHighlight[y][x].setFillColor(Color (148,0,211,92));
            }
            else
                rs_ValidMoveHighlight[y][x].setFillColor (Color (0, 255, 0, 128));
        }
        else
            rs_ValidMoveHighlight[y][x].setFillColor (Color (0, 255, 0, 128));
    }
}

