#include "chessboard.h"
#include "resources.h"

#include <movethread.h>

#include <iostream>

using namespace std;


ChessBoard::ChessBoard(QWidget* Parent, const QPoint& Position, const QSize& Size) :
QSFMLCanvas(Parent, Position, Size), colorWhite (64)
{
    setMouseTracking(true);
}

void ChessBoard::OnInit()
{
    iSelectedFigure = -1;

    loadBoard ();
    loadFigures ();

    rs_Selected = RectangleShape ( Vector2f (boardTileWidth, boardTileHeight) );
    rs_Selected.setFillColor(Color (0, 255, 0, 64));

    rs_Moving = RectangleShape ( Vector2f (boardTileWidth, boardTileHeight) );
    rs_Moving.setFillColor(Color (0, 255, 0, 32));

    memset (bValid, 0, sizeof (bool)*8*8);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            rs_ValidMoveHighlight[i][j] = RectangleShape ( Vector2f (boardTileWidth, boardTileHeight) );
            rs_ValidMoveHighlight[i][j].setFillColor (Color (0, 255, 0, 48));
            rs_ValidMoveHighlight[i][j].setPosition (j*boardTileWidth, i*boardTileHeight );
        }
    chessEng = new ChessEngine ();
    chessEng->newGame();

}


void ChessBoard::OnUpdate()
{
    this->clear(sf::Color(0, 0, 0));
    this->draw (s_Board);
    if (iSelectedFigure >= 0)
    {
        rs_Selected.setPosition(boardTileWidth*iSelectedTileX,
                                 boardTileHeight*iSelectedTileY);

        this->draw (rs_Selected);
    }

    rs_Moving.setPosition( boardTileWidth*movingTileX, movingTileY*boardTileHeight );
    this->draw(rs_Moving);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (bValid[i][j])
                this->draw(rs_ValidMoveHighlight[i][j]);

    for (int i = 0; i < 32; i++)
    {
        this->draw (s_Figures[i]);
    }
}
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

            journal.push(fmi);

            figuresTable[tileY][tileX] = figuresTable[iSelectedTileY][iSelectedTileX];
            figuresTable[iSelectedTileY][iSelectedTileX] = 0;

            indexTable[iSelectedTileY][iSelectedTileX] = -1;
            indexTable[tileY][tileX] = iSelectedFigure;

            Move move;
            move.from = iSelectedTileY*8 + iSelectedTileX;
            move.to = tileY*8 + tileX;
            cout << iSelectedTileY*8 + iSelectedTileX << " " << tileY*8 + tileX << endl;
            chessEng->makeMove (move);
        }
            unselect ();
    }

}

void ChessBoard::loadBoard ()
{
    qWhiteDestroyed = 0;
    qBlackDestroyed = 0;

    memset (figuresTable, 0, sizeof(int)*64);

    figuresTable[0][0] = Rook;
    figuresTable[0][1] = Knight;
    figuresTable[0][2] = Bishop;
    figuresTable[0][3] = Queen;
    figuresTable[0][4] = King;
    figuresTable[0][5] = Bishop;
    figuresTable[0][6] = Knight;
    figuresTable[0][7] = Rook;

    for (int i = 0; i < 8; i++)
        figuresTable[1][i] = Pawn;

    for (int i = 0; i < 8; i++)
        figuresTable[6][i] = Pawn | colorWhite;

    figuresTable[7][0] = Rook | colorWhite;
    figuresTable[7][1] = Knight | colorWhite;
    figuresTable[7][2] = Bishop | colorWhite;
    figuresTable[7][3] = Queen | colorWhite;
    figuresTable[7][4] = King | colorWhite;
    figuresTable[7][5] = Bishop | colorWhite;
    figuresTable[7][6] = Knight | colorWhite;
    figuresTable[7][7] = Rook | colorWhite;

    t_Board.loadFromFile(szBoard);
    s_Board.setTexture(t_Board);

    int widgetWidth = this->getSize().x;
    int widgetheight = this->getSize().y;

    int spriteWidth = s_Board.getLocalBounds().width;
    int spriteHeight = s_Board.getLocalBounds().height;

    s_Board.setScale (Vector2f (
                                     ((float)widgetWidth) / (spriteWidth),
                                     ((float)widgetheight) / spriteHeight));


    boardWidth = (spriteWidth)*s_Board.getScale().x;
    boardHeight = (spriteHeight)*s_Board.getScale().y;

    boardTileWidth = boardWidth / 8;
    boardTileHeight = boardHeight / 8;
}

void ChessBoard::loadFigures ()
{
    t_Figures.loadFromFile (szFigures);
    t_Figures.setSmooth(true);
    int figuresWidth = t_Figures.getSize().x;
    int figuresHeight = t_Figures.getSize().y;

    const int qFiguresPerWidth = 6;
    const int qFiguresPerHeight = 2;
    const int imageSequece[] = {King, Queen, Bishop, Knight, Rook, Pawn};

    figureWidth = figuresWidth / qFiguresPerWidth;
    figureHeight = figuresHeight / qFiguresPerHeight;

    int figurePos = 0;
    int currentSprite = 0;
    int qFigures = 32;


    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            indexTable[i][j] = -1;

        while (currentSprite < qFigures)
        {
            bool isBlack = figurePos / 6;
            if ( imageSequece[figurePos % qFiguresPerWidth] == King || imageSequece[figurePos % qFiguresPerWidth] == Queen)
            {
                s_Figures[currentSprite].setTexture (t_Figures);
                s_Figures[currentSprite].setTextureRect ( IntRect (
                                                    (figurePos % qFiguresPerWidth)*figuresWidth/qFiguresPerWidth,
                                                    (int)(figurePos / qFiguresPerWidth)*figuresHeight/qFiguresPerHeight,
                                                    figureWidth,
                                                    figureHeight ) );

                s_Figures[currentSprite].setScale (Vector2f (
                                              (float)(boardTileWidth) / figureWidth,
                                              (float)(boardTileHeight) / figureHeight ));

                if ( imageSequece[figurePos % qFiguresPerWidth] == King )
                {
                    if (isBlack)
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                          4*boardTileWidth,
                                                                           0) );
                        indexTable[0][4] = currentSprite;
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         4*boardTileWidth,
                                                                         boardHeight - boardTileHeight) );
                        indexTable[7][4] = currentSprite;
                    }
                }
                else if ( imageSequece[figurePos % qFiguresPerWidth] == Queen )
                {
                    if (isBlack)
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         3*boardTileWidth,
                                                                         0) );
                        indexTable[0][3] = currentSprite;
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         3*boardTileWidth,
                                                                          boardHeight - boardTileHeight) );
                        indexTable[7][3] = currentSprite;
                    }
                }

                currentSprite++;
            }
            else if ( imageSequece[figurePos % qFiguresPerWidth] == Pawn)
            {
                for (int i = 0; i < 8; i++)
                {
                    s_Figures[currentSprite].setTexture (t_Figures);
                    s_Figures[currentSprite].setTextureRect ( IntRect (
                                                    (figurePos % qFiguresPerWidth)*figuresWidth/qFiguresPerWidth,
                                                    (int)(figurePos / qFiguresPerWidth)*figuresHeight/qFiguresPerHeight,
                                                    figureWidth,
                                                    figureHeight ) );

                    s_Figures[currentSprite].setScale (Vector2f (
                                                  (float)(boardTileWidth) / figureWidth,
                                                  (float)(boardTileHeight) / figureHeight ));

                    if (isBlack)
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         i*boardTileWidth,
                                                                         boardTileHeight) );
                        indexTable[1][i] = currentSprite;
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         i*boardTileWidth,
                                                                         boardHeight - 2*boardTileHeight) );
                        indexTable[6][i] = currentSprite;
                    }
                    currentSprite++;
                }
            }
            else
            {
                for (int i = 0; i < 2; i++)
                {
                    s_Figures[currentSprite].setTexture (t_Figures);
                    s_Figures[currentSprite].setTextureRect ( IntRect (
                                                    (figurePos % qFiguresPerWidth)*figuresWidth/qFiguresPerWidth,
                                                    ((int)(figurePos / qFiguresPerWidth))*figuresHeight/qFiguresPerHeight,
                                                    figureWidth,
                                                    figureHeight ) );
                    s_Figures[currentSprite].setScale (Vector2f (
                                                  (float)(boardTileWidth) / figureWidth,
                                                  (float)(boardTileHeight) / figureHeight ));

                    if ( imageSequece[figurePos % qFiguresPerWidth] == Rook )
                    {
                        if (isBlack)
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             i*(boardWidth - boardTileWidth),
                                                                              0) );
                            indexTable[0][i*7] = currentSprite;
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             i*(boardWidth - boardTileWidth),
                                                                             boardHeight - boardTileHeight) );
                            indexTable[7][i*7] = currentSprite;

                        }
                    }
                    else if ( imageSequece[figurePos % qFiguresPerWidth] == Knight )
                    {
                        if (isBlack)
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             1*boardTileWidth + 5*i*boardTileWidth ,
                                                                              0) );
                            indexTable[0][1+5*i] = currentSprite;
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             1*boardTileWidth + 5*i*boardTileWidth,
                                                                              boardHeight - boardTileHeight) );
                            indexTable[7][1+5*i] = currentSprite;
                        }
                    }
                    else
                    {
                        if (isBlack)
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                              2*boardTileWidth + 3*i*boardTileWidth,
                                                                              0) );
                            indexTable[0][2+3*i] = currentSprite;
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             2*boardTileWidth + 3*i*boardTileWidth,
                                                                             boardHeight - boardTileHeight) );
                            indexTable[7][2+3*i] = currentSprite;
                        }
                    }

                    currentSprite++;
                }
            }
            figurePos++;
        }
        figureWidth *= s_Figures[0].getScale().x;
        figureHeight *= s_Figures[0].getScale().y;
}

void ChessBoard::undo()
{
    if (journal.isEmpty())
        return;
    FigureMovedInfo fmi = journal.pop();
    int tileX1, tileY1, tileX2, tileY2;
    fmi.figureMove.getCoords(&tileX1, &tileY1, &tileX2, &tileY2);
    fmi.s_Figure->setPosition(Vector2f (tileX1*boardTileWidth,
                                        tileY1*boardTileHeight));

    indexTable[tileY2][tileX2] = -1;
    indexTable[tileY1][tileX1] = fmi.figureIndex;

    figuresTable[tileY2][tileX2] = 0;
    figuresTable[tileY1][tileX1] = fmi.figure;

    if ( fmi.extraFigureIndex != 0 )
    {
        cout << "hell" << endl;
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
    unselect ();
    chessEng->undo();
}

void ChessBoard::unselect()
{
    iSelectedTileX = -1;
    iSelectedTileY = -1;
    iSelectedFigure = -1;

    memset (bValid, 0, sizeof (bool)*8*8);
}

inline bool ChessBoard::isWhite (int figure)
{
    return (figure & colorWhite) == colorWhite;
}
