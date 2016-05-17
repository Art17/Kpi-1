#include "chessboard.h"
#include "resources.h"

#include <movethread.h>
#include <selectfiguredialog.h>

#include <iostream>

using namespace std;

void ChessBoard::moveReady (Move move)
{
    bComputerMove = false;
    makeMove(move);
}

int ChessBoard::makeMove (const Move& move)
{
    int iSelectedTileX = move.from % 8;
    int iSelectedTileY = move.from / 8;
    int tileX = move.to % 8;
    int tileY = move.to / 8;

    int iSelectedFigure = indexTable[iSelectedTileY][iSelectedTileX];

    QRect rect;
    rect.setCoords(s_Figures[iSelectedFigure].getPosition().x,
                   s_Figures[iSelectedFigure].getPosition().y,
                   tileX*boardTileWidth,
                   tileY*boardTileHeight);
    MoveThread* figureMoveThread = new MoveThread(rect,
                                            &s_Figures[iSelectedFigure]);
    MoveThread* castlingMoveThread = NULL;
    figureMoveThread->start ();

    rect.setCoords(iSelectedTileX, iSelectedTileY, tileX, tileY);
    FigureMovedInfo fmi;
    memset (&fmi, 0, sizeof (FigureMovedInfo));
    fmi.s_Figure = &s_Figures[iSelectedFigure];
    fmi.figureIndex = iSelectedFigure;
    fmi.figure = figuresTable[iSelectedTileY][iSelectedTileX];
    fmi.figureMove = rect;
    fmi.extraFigureIndex = -1;

    if (figuresTable[tileY][tileX] != 0)
    {
        s_Figures[ indexTable[tileY][tileX] ].setPosition(Vector2f (-100, -100));
        rect.setCoords (tileX, tileY, -100, -100);
        fmi.s_ExtraFigure = &s_Figures[ indexTable[tileY][tileX] ];
        fmi.extraFigureIndex = indexTable[tileY][tileX];
        fmi.extraFigure = figuresTable [tileY][tileX];
        fmi.extraFigureMove = rect;
    }
    else if ( figuresTable[iSelectedTileY][iSelectedTileX] & King )
    {
        if ( tileX == iSelectedTileX+2 )
        {
            if ( isWhite (figuresTable[iSelectedTileY][iSelectedTileX]) )
            {
                rect.setCoords(7*boardTileWidth, 7*boardTileHeight, 5*boardTileWidth, 7*boardTileHeight);
                castlingMoveThread = new MoveThread(rect,
                                                        &s_Figures[indexTable[7][7]]);
                rect.setCoords(7, 7, 5, 7);
                castlingMoveThread->start();
                fmi.s_ExtraFigure = &s_Figures[ indexTable[7][7] ];
                fmi.extraFigureIndex = indexTable[7][7];
                fmi.extraFigure = figuresTable [7][7];
                fmi.extraFigureMove = rect;

                indexTable[7][5] = indexTable[7][7];
                indexTable[7][7] = -1;

                figuresTable[7][5] = figuresTable[7][7];
                figuresTable[7][7] = 0;
            }
            else
            {
                rect.setCoords(7*boardTileWidth, 0*boardTileHeight, 5*boardTileWidth, 0*boardTileHeight);
                castlingMoveThread = new MoveThread(rect,
                                                        &s_Figures[indexTable[0][7]]);
                castlingMoveThread->start();
                rect.setCoords(7, 0, 5, 0);
                fmi.s_ExtraFigure = &s_Figures[ indexTable[0][7] ];
                fmi.extraFigureIndex = indexTable[0][7];
                fmi.extraFigure = figuresTable [0][7];
                fmi.extraFigureMove = rect;

                indexTable[0][5] = indexTable[0][7];
                indexTable[0][7] = -1;

                figuresTable[0][5] = figuresTable[0][7];
                figuresTable[0][7] = 0;
            }
        }
        if ( tileX == iSelectedTileX-2 )
        {
            if ( isWhite (figuresTable[iSelectedTileY][iSelectedTileX]) )
            {
                rect.setCoords(0*boardTileWidth, 7*boardTileHeight, 3*boardTileWidth, 7*boardTileHeight);
                castlingMoveThread = new MoveThread(rect,
                                                        &s_Figures[indexTable[7][0]]);
                castlingMoveThread->start();
                rect.setCoords(0, 7, 3, 7);
                fmi.s_ExtraFigure = &s_Figures[ indexTable[7][0] ];
                fmi.extraFigureIndex = indexTable[7][0];
                fmi.extraFigure = figuresTable [7][0];
                fmi.extraFigureMove = rect;

                indexTable[7][3] = indexTable[7][0];
                indexTable[7][0] = -1;

                figuresTable[7][3] = figuresTable[7][0];
                figuresTable[7][0] = 0;

            }
            else
            {
                rect.setCoords(0*boardTileWidth, 0*boardTileHeight, 3*boardTileWidth, 0*boardTileHeight);
                castlingMoveThread = new MoveThread(rect,
                                                        &s_Figures[indexTable[0][0]]);
                castlingMoveThread->start();
                rect.setCoords(0, 0, 3, 0);
                fmi.s_ExtraFigure = &s_Figures[ indexTable[0][0] ];
                fmi.extraFigureIndex = indexTable[0][0];
                fmi.extraFigure = figuresTable [0][0];
                fmi.extraFigureMove = rect;

                indexTable[0][3] = indexTable[0][0];
                indexTable[0][0] = -1;

                figuresTable[0][3] = figuresTable[0][0];
                figuresTable[0][0] = 0;
            }
        }
    }
    FigureMovedInfo lastFmi;
    if (journal.isEmpty())
    {
        memset (&lastFmi, 0, sizeof (FigureMovedInfo));
    }
    else
        lastFmi = journal.top();
    int xFrom = iSelectedTileX;
    int yFrom = iSelectedTileY;
    int xTo = tileX;
    int yTo = tileY;
    int lastXFrom, lastYFrom, lastXTo, lastYTo;
    lastFmi.figureMove.getCoords(&lastXFrom, &lastYFrom, &lastXTo, &lastYTo);

    if ( yFrom == 3 )
    {
        if (xFrom+1 < 8 && lastYFrom == 1 && lastXFrom == xFrom+1 && lastYTo == 3 && lastXTo == xFrom+1 && xTo == xFrom+1)
        {
            if ( figuresTable[3][xFrom+1] & Pawn && figuresTable[yFrom][xFrom] & Pawn)
            {
                rect.setCoords (xFrom+1, 3, -100, -100);
                fmi.s_ExtraFigure = &s_Figures[ indexTable[3][xFrom+1] ];
                fmi.extraFigureIndex = indexTable[3][xFrom+1];
                fmi.extraFigure = figuresTable [3][xFrom+1];
                fmi.extraFigureMove = rect;

                figuresTable[3][xFrom+1] = 0;
                s_Figures[ indexTable[3][xFrom+1] ].setPosition(Vector2f (-100, -100));
                indexTable[3][xFrom+1] = -1;
            }
        }
        if (xFrom-1 >= 0 && lastYFrom == 1 && lastXFrom == xFrom-1 && lastYTo == 3 && lastXTo == xFrom-1 && xTo == xFrom-1)
        {
            if ( figuresTable[3][xFrom-1] & Pawn && figuresTable[yFrom][xFrom] & Pawn )
            {
                rect.setCoords (xFrom-1, 3, -100, -100);
                fmi.s_ExtraFigure = &s_Figures[ indexTable[3][xFrom-1] ];
                fmi.extraFigureIndex = indexTable[3][xFrom-1];
                fmi.extraFigure = figuresTable [3][xFrom-1];
                fmi.extraFigureMove = rect;

                figuresTable[3][xFrom-1] = 0;
                s_Figures[ indexTable[3][xFrom-1] ].setPosition(Vector2f (-100, -100));
                indexTable[3][xFrom-1] = -1;
            }
        }
    }

    if ( yFrom == 4 )
    {
        if (xFrom+1 < 8 && lastYFrom == 6 && lastXFrom == xFrom+1 && lastYTo == 4 && lastXTo == xFrom+1 && xTo == xFrom+1)
        {
            if ( figuresTable[4][xFrom+1] & Pawn && figuresTable[yFrom][xFrom] & Pawn )
            {
                rect.setCoords (xFrom+1, 4, -100, -100);
                fmi.s_ExtraFigure = &s_Figures[ indexTable[4][xFrom+1] ];
                fmi.extraFigureIndex = indexTable[4][xFrom+1];
                fmi.extraFigure = figuresTable [4][xFrom+1];
                fmi.extraFigureMove = rect;

                figuresTable[4][xFrom+1] = 0;
                s_Figures[ indexTable[4][xFrom+1] ].setPosition(Vector2f (-100, -100));
                indexTable[4][xFrom+1] = -1;
            }
        }
        if (xFrom-1 >= 0 && lastYFrom == 6 && lastXFrom == xFrom-1 && lastYTo == 4 && lastXTo == xFrom-1 && xTo == xFrom-1)
        {
            if ( figuresTable[4][xFrom-1] & Pawn && figuresTable[yFrom][xFrom] & Pawn )
            {
                rect.setCoords (xFrom-1, 3, -100, -100);
                fmi.s_ExtraFigure = &s_Figures[ indexTable[4][xFrom-1] ];
                fmi.extraFigureIndex = indexTable[4][xFrom-1];
                fmi.extraFigure = figuresTable [4][xFrom-1];
                fmi.extraFigureMove = rect;
                figuresTable[4][xFrom-1] = 0;
                s_Figures[ indexTable[4][xFrom-1] ].setPosition(Vector2f (-100, -100));
                indexTable[4][xFrom-1] = -1;
            }

        }
    }
    bool bPromoted = false;
    if (figuresTable[iSelectedTileY][iSelectedTileX] & Pawn)
    {
        if (tileY == 0 || tileY == 7)
        {
            figuresTable[tileY][tileX] = move.extra |
                                            isWhite (figuresTable[iSelectedTileY][iSelectedTileX]) ? colorWhite : 0;
            fmi.bPromoted = true;
            setSpriteRect ( &s_Figures[ indexTable[iSelectedTileY][iSelectedTileX] ],
                                move.extra | ( (tileY==0 ? colorWhite : 0) ) );
            bPromoted = true;

        }

    }
    if (!bPromoted)
    {
        figuresTable[tileY][tileX] = figuresTable[iSelectedTileY][iSelectedTileX];
        fmi.bPromoted = false;
    }

    figuresTable[iSelectedTileY][iSelectedTileX] = 0;

    indexTable[iSelectedTileY][iSelectedTileX] = -1;
    indexTable[tileY][tileX] = iSelectedFigure;

    int ret = chessEng->makeMove (move);
    bWhiteCheck = chessEng->isCheck (true);
    bBlackCheck = chessEng->isCheck (false);

    journal.push(fmi);

    if (ret > 0)
        endGame (ret);

    return ret;
}
