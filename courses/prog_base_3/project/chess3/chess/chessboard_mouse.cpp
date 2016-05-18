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
        iSelectedFigure = indexTable[tileY][tileX];
        iSelectedTileX = tileX;
        iSelectedTileY = tileY;
        int from = 0;
        if (bFlipped)
            from = (7-tileY)*8 + tileX;
        else
            from = tileY*8 + tileX;
        byte validMoves[32];
        int l;

        chessEng->getValidMoves(from, (byte*)validMoves, &l);

        for (int i = 0; i < l; i++)
        {
            int x = validMoves[i] % 8;
            int y = validMoves[i] / 8;

            if (bFlipped)
                bValid[7-y][x] = true;
            else
                bValid[y][x] = true;

            /*if (figuresTable[y][x] != 0)
                rs_ValidMoveHighlight[y][x].setFillColor(Color (255,0,0,128));
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
            }
            else
                rs_ValidMoveHighlight[y][x].setFillColor (Color (0, 255, 0, 128));*/
        }
    }
    else
    {
        if ( bValid[tileY][tileX] )
        {
            Move move;
            if (bFlipped)
                move.from = (7-iSelectedTileY)*8 + iSelectedTileX;
            else
                move.from = (iSelectedTileY)*8 + iSelectedTileX;
            if (bFlipped)
                move.to = (7-tileY)*8 + tileX;
            else
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
