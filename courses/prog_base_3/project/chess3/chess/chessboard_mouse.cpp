#include "chessboard.h"
#include "resources.h"

#include <movethread.h>
#include <selectfiguredialog.h>

#include <iostream>

using namespace std;

void ChessBoard::mouseMoveEvent(QMouseEvent *e)
{
    movingTileX = e->x() / boardTileWidth;
    movingTileY = e->y() / boardTileHeight;
}

void ChessBoard::mousePressEvent(QMouseEvent* mouseEvent)
{
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
        byte board[8][8];
        chessEng->getBoard((byte*)board);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << (int)board[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        if ( bValid[tileY][tileX] )
        {
            QRect rect;
            rect.setCoords(s_Figures[iSelectedFigure].getPosition().x,
                           s_Figures[iSelectedFigure].getPosition().y,
                           tileX*boardTileWidth,
                           tileY*boardTileHeight);
            MoveThread* moveThread = new MoveThread(rect,
                                                    &s_Figures[iSelectedFigure]);
            moveThread->start ();



            rect.setCoords(iSelectedTileX, iSelectedTileY, tileX, tileY);
            FigureMovedInfo fmi;
            memset (&fmi, 0, sizeof (FigureMovedInfo));
            fmi.s_Figure = &s_Figures[iSelectedFigure];
            fmi.figureIndex = iSelectedFigure;
            fmi.figure = figuresTable[iSelectedTileY][iSelectedTileX];
            fmi.figureMove = rect;


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
                        MoveThread* moveThread = new MoveThread(rect,
                                                                &s_Figures[indexTable[7][7]]);
                        rect.setCoords(7, 7, 5, 7);
                        moveThread->start();
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
                        MoveThread* moveThread = new MoveThread(rect,
                                                                &s_Figures[indexTable[0][7]]);
                        moveThread->start();
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
                        MoveThread* moveThread = new MoveThread(rect,
                                                                &s_Figures[indexTable[7][0]]);
                        moveThread->start();
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
                        MoveThread* moveThread = new MoveThread(rect,
                                                                &s_Figures[indexTable[0][0]]);
                        moveThread->start();
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
            int newFigure = 0;
            if (figuresTable[iSelectedTileY][iSelectedTileX] & Pawn)
            {
                if (tileY == 0 || tileY == 7)
                {
                    if (selectDialog->exec())
                    {
                        selectDialog->move(100, 100);
                        newFigure = selectDialog->getEnteredValue();
                        setSpriteRect ( &s_Figures[ indexTable[iSelectedTileY][iSelectedTileX] ],
                                            newFigure | ( (tileY==0 ? colorWhite : 0) ) );
                    }
                }
            }
            if (newFigure != 0)
            {
                figuresTable[tileY][tileX] = newFigure |
                                                isWhite (figuresTable[iSelectedTileY][iSelectedTileX]) ? colorWhite : 0;
                fmi.bPromoted = true;
            }
            else
            {
                figuresTable[tileY][tileX] = figuresTable[iSelectedTileY][iSelectedTileX];
                fmi.bPromoted = false;
            }
            figuresTable[iSelectedTileY][iSelectedTileX] = 0;

            indexTable[iSelectedTileY][iSelectedTileX] = -1;
            indexTable[tileY][tileX] = iSelectedFigure;

            Move move;
            move.from = iSelectedTileY*8 + iSelectedTileX;
            move.to = tileY*8 + tileX;
            move.extra = newFigure;
            cout << newFigure << endl;
            cout << iSelectedTileY*8 + iSelectedTileX << " " << tileY*8 + tileX << endl;
            chessEng->makeMove (move);
            bWhiteCheck = chessEng->isCheck (true);
            bBlackCheck = chessEng->isCheck (false);

            journal.push(fmi);
        }
            unselect ();
    }

}
