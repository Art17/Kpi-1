#include "chessboard.h"
#include "resources.h"

#include <chessboard_movethread.h>
#include <selectfiguredialog.h>

#include <iostream>

using namespace std;

void ChessBoard::undo ()
{
    if (bAgainstComputer)
    {
        if (bLocked)
        {
            cbct->terminate ();
            bLocked = false;
            undoLow ();
        }
        else
        {
            undoLow ();
            if (!undoLow ())
            {
                cbct->start();
                bLocked = true;
            }
        }
    }
    else
    {
        undoLow ();
        bLocked = false;
    }

    if (figureMoveThread->isRunning())
        figureMoveThread->terminate();
    if (extraFigureMoveThread->isRunning())
        extraFigureMoveThread->terminate();
}

bool ChessBoard::undoLow()
{
    if (journal.isEmpty())
        return false;

    FigureMovedInfo fmi = journal.pop();
    int tileX1, tileY1, tileX2, tileY2;
    fmi.figureMove.getCoords(&tileX1, &tileY1, &tileX2, &tileY2);
    fmi.s_Figure->setPosition(Vector2f (tileX1*boardTileWidth,
                                        tileY1*boardTileHeight));
    bool bWhite = isWhite (fmi.figure);

    indexTable[tileY2][tileX2] = -1;
    indexTable[tileY1][tileX1] = fmi.figureIndex;

    figuresTable[tileY2][tileX2] = 0;
    figuresTable[tileY1][tileX1] = fmi.figure;

    if ( fmi.extraFigureIndex != -1 )
    {
        int tileX1, tileY1, tileX2, tileY2;
        fmi.extraFigureMove.getCoords(&tileX1, &tileY1, &tileX2, &tileY2);
        fmi.s_ExtraFigure->setPosition( Vector2f (
                                                  tileX1*boardTileWidth,
                                                  tileY1*boardTileHeight)  );
        figuresTable[tileY1][tileX1] = fmi.extraFigure;
        indexTable[tileY1][tileX1] = fmi.extraFigureIndex;

        if (tileX2 >= 0 && tileY2 >= 0)
        {
            indexTable[tileY2][tileX2] = -1;
            figuresTable[tileY2][tileX2] = 0;
        }
    }
    if (fmi.bPromoted)
    {
        setSpriteRect(&s_Figures[fmi.figureIndex], Pawn | ((bWhite) ? colorWhite : 0));
    }
    unselect ();

    chessEng->undo();
    bWhiteCheck = chessEng->isCheck (true);
    bBlackCheck = chessEng->isCheck (false);

    return true;
}
