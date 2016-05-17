#include "chessboard.h"
#include "resources.h"

#include <movethread.h>
#include <selectfiguredialog.h>

#include <iostream>

using namespace std;

void ChessBoard::mousePressEvent(QMouseEvent* mouseEvent)
{
    if (bComputerMove)
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

        int from = tileY*8 + tileX;
        byte validMoves[32];
        int l;

        chessEng->getValidMoves(from, (byte*)validMoves, &l);

        for (int i = 0; i < l; i++)
        {
            int x = validMoves[i] % 8;
            int y = validMoves[i] / 8;

            bValid[y][x] = true;
        }
    }
    else
    {
        if ( bValid[tileY][tileX] )
        {
            Move move;
            move.from = iSelectedTileY*8 + iSelectedTileX;
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
            move.extra = newFigure;

            if ( makeMove (move) > 0 )
            {
                unselect ();
                return;
            }

            if (bAgainstComputer)
            {
                bComputerMove = true;
                cbct->start();
            }
        }
            unselect ();
    }
}
