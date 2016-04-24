#include "chessboard.h"
#include "resources.h"

#include <movethread.h>


ChessBoard::ChessBoard(QWidget* Parent, const QPoint& Position, const QSize& Size) :
QSFMLCanvas(Parent, Position, Size)
{

}

void ChessBoard::OnInit()
{
    iSelectedFigure = -1;

    loadBoard ();
    loadFigures ();

}


void ChessBoard::OnUpdate()
{
    this->clear(sf::Color(0, 0, 0));
    this->draw (s_Board);
    /*for (int i = 0; i < 32; i++)
        this->draw (s_Figures[i]);*/
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
           if (indexTable[i][j] != -1)
               this->draw (s_Figures[indexTable[i][j]]);
}

void ChessBoard::mousePressEvent(QMouseEvent* mouseEvent)
{
    int x = mouseEvent->x();
    int y = mouseEvent->y();

    if (x <= boardMarginLeft || y <= boardMarginTop)
        return;
    if (x >= boardMarginLeft + boardWidth || y >= boardMarginTop + boardHeight)
        return;

    x -= boardMarginLeft + 5;
    y -= boardMarginTop;

    int tileX = x / boardTileWidth;
    int tileY = y / boardTileHeight;

    if (iSelectedFigure == -1)
    {
        iSelectedFigure = indexTable[tileX][tileY];
        iSelectedTileX = tileX;
        iSelectedTileY = tileY;
    }
    else
    {
        /*s_Figures[iSelectedFigure].setPosition ( Vector2f (boardMarginLeft + tileX*boardTileWidth + figureMarginX,
                                                           boardMarginTop + tileY*boardTileHeight + figureMarginY) );*/

        QRect rect;
        rect.setCoords(s_Figures[iSelectedFigure].getPosition().x,
                       s_Figures[iSelectedFigure].getPosition().y,
                       boardMarginLeft + tileX*boardTileWidth + figureMarginX,
                       boardMarginTop + tileY*boardTileHeight + figureMarginY);
        MoveThread* moveThread = new MoveThread(rect,
                                                &s_Figures[iSelectedFigure]);
        moveThread->start ();

        indexTable[iSelectedTileX][iSelectedTileY] = -1;
        indexTable[tileX][tileY] = iSelectedFigure;
        iSelectedFigure = -1;
    }

}

/*void ChessBoard::mouseMoveEvent (QMouseEvent* mouseEvent)
{
    int x = mouseEvent->x();
    int y = mouseEvent->y();

    if (x <= boardMarginLeft || y <= boardMarginTop)
        return;
    if (x >= boardMarginLeft + boardWidth || y >= boardMarginTop + boardHeight)
        return;
    if (iSelectedFigure == -1)
        return;


    if (mouseEvent->buttons() & Qt::LeftButton)
    {
        s_Figures[iSelectedFigure].setPosition ( Vector2f (x - figureWidth/2,
                                                           y - figureHeight/2) );
    }
}

void ChessBoard::mouseReleaseEvent(QMouseEvent* mouseEvent)
{

    int x = mouseEvent->x();
    int y = mouseEvent->y();

    if (iSelectedFigure == -1)
        return;
    if (x <= boardMarginLeft || y <= boardMarginTop)
        return;
    if (x >= boardMarginLeft + boardWidth || y >= boardMarginTop + boardHeight)
        return;

    x -= boardMarginLeft + 5;
    y -= boardMarginTop;

    int tileX = x / boardTileWidth;
    int tileY = y / boardTileHeight;


    //if (mouseEvent->buttons() & Qt::LeftButton)
    //{
        s_Figures[iSelectedFigure].setPosition ( Vector2f (boardMarginLeft + tileX*boardTileWidth + figureMarginX,
                                                           boardMarginTop + tileY*boardTileHeight + figureMarginY) );
        indexTable[iSelectedTileX][iSelectedTileY] = -1;
        indexTable[tileX][tileY] = iSelectedFigure;
        iSelectedFigure = -1;
    //}
}*/

void ChessBoard::loadBoard ()
{
    t_Board.loadFromFile(szBoard);
    s_Board.setTexture(t_Board);

    int widgetWidth = this->getSize().x;
    int widgetheight = this->getSize().y;

    int spriteWidth = s_Board.getLocalBounds().width;
    int spriteHeight = s_Board.getLocalBounds().height;

    s_Board.setScale (Vector2f (
                                     ((float)widgetWidth) / (spriteWidth),
                                     ((float)widgetheight) / spriteHeight));

    boardMarginLeft = 58;
    boardMarginRight = 64;
    boardMarginTop = 59;
    boardMarginBottom  = 63;

    boardWidth = (spriteWidth - boardMarginLeft - boardMarginRight)*s_Board.getScale().x;
    boardHeight = (spriteHeight - boardMarginBottom - boardMarginTop)*s_Board.getScale().y;

    boardTileWidth = boardWidth / 8;
    boardTileHeight = boardHeight / 8;
}

void ChessBoard::loadFigures ()
{
    t_Figures.loadFromFile (szFigures);
    int figuresWidth = t_Figures.getSize().x;
    int figuresHeight = t_Figures.getSize().y;

    const int qFiguresPerWidth = 6;
    const int qFiguresPerHeight = 2;
    const int imageSequece[] = {King, Queen, Bishop, Knight, Rook, Pawn};

    figureWidth = figuresWidth / qFiguresPerWidth;
    figureHeight = figuresHeight / qFiguresPerHeight;

    figureMarginX = 7;
    figureMarginY = 6;

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
                                                                         boardMarginLeft + 4*boardTileWidth + figureMarginX,
                                                                         boardMarginTop  + figureMarginY) );
                        indexTable[4][0] = currentSprite;
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + 4*boardTileWidth + figureMarginX,
                                                                         boardMarginTop + boardHeight - boardTileHeight + figureMarginY) );
                        indexTable[4][7] = currentSprite;
                    }
                }
                else if ( imageSequece[figurePos % qFiguresPerWidth] == Queen )
                {
                    if (isBlack)
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + 3*boardTileWidth + figureMarginX,
                                                                         boardMarginTop + figureMarginY) );
                        indexTable[3][0] = currentSprite;
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + 3*boardTileWidth + figureMarginX,
                                                                         boardMarginTop + boardHeight - boardTileHeight + figureMarginY) );
                        indexTable[3][7] = currentSprite;
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
                                                                         boardMarginLeft + i*boardTileWidth  + figureMarginX,
                                                                         boardMarginTop + boardTileHeight + figureMarginY) );
                        indexTable[i][1] = currentSprite;
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + i*boardTileWidth + figureMarginX,
                                                                         boardMarginTop + boardHeight - 2*boardTileHeight + figureMarginY) );
                        indexTable[i][6] = currentSprite;
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
                                                                             boardMarginLeft + i*(boardWidth - boardTileWidth) + figureMarginX,
                                                                             boardMarginTop + figureMarginY) );
                            indexTable[i*7][0] = currentSprite;
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + i*(boardWidth - boardTileWidth) + figureMarginX,
                                                                             boardMarginTop + boardHeight - boardTileHeight + figureMarginY) );
                            indexTable[i*7][7] = currentSprite;

                        }
                    }
                    else if ( imageSequece[figurePos % qFiguresPerWidth] == Knight )
                    {
                        if (isBlack)
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + 1*boardTileWidth + 5*i*boardTileWidth + figureMarginX,
                                                                             boardMarginTop + figureMarginY) );
                            indexTable[1 + 5*i][0] = currentSprite;
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + 1*boardTileWidth + 5*i*boardTileWidth + figureMarginX,
                                                                             boardMarginTop + boardHeight - boardTileHeight + figureMarginY) );
                            indexTable[1 + 5*i][7] = currentSprite;
                        }
                    }
                    else
                    {
                        if (isBlack)
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + 2*boardTileWidth + 3*i*boardTileWidth + figureMarginX,
                                                                             boardMarginTop + figureMarginY) );
                            indexTable[2 + 3*i][0] = currentSprite;
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + 2*boardTileWidth + 3*i*boardTileWidth + figureMarginX,
                                                                             boardMarginTop + boardHeight - boardTileHeight + figureMarginY) );
                            indexTable[2 + 3*i][7] = currentSprite;
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
