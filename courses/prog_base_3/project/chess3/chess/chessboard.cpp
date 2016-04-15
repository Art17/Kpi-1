#include "chessboard.h"
#include "resources.h"

ChessBoard::ChessBoard(QWidget* Parent, const QPoint& Position, const QSize& Size) :
QSFMLCanvas(Parent, Position, Size)
{

}

void ChessBoard::OnInit()
{
    t_Board.loadFromFile(szBoard);
    s_Board.setTexture(t_Board);

    int widgetWidth = this->getSize().x;
    int widgetheight = this->getSize().y;

    int spriteWidth = s_Board.getLocalBounds().width;
    int spriteHeight = s_Board.getLocalBounds().height;

    s_Board.setScale (Vector2f (
                                     ((float)widgetWidth) / spriteWidth,
                                     ((float)widgetheight) / spriteHeight)); // make background fullscreen

    loadFigures ();

}


void ChessBoard::OnUpdate()
{
    this->clear(sf::Color(0, 0, 0));
    this->draw (s_Board);
    for (int i = 0; i < 32; i++)
        this->draw (s_Figures[i]);
}

void ChessBoard::loadFigures ()
{
    t_Figures.loadFromFile (szFigures);
    int figuresWidth = t_Figures.getSize().x;
    int figuresHeight = t_Figures.getSize().y;

    const int qFiguresPerWidth = 6;
    const int qFiguresPerHeight = 2;
    const int imageSequece[] = {King, Queen, Bishop, Knight, Rook, Pawn};

    int figureWidth = figuresWidth / qFiguresPerWidth;
    int figureHeight = figuresHeight / qFiguresPerHeight;


    int figurePos = 0;
    int currentSprite = 0;
    int qFigures = 32;

    int boardWidth = s_Board.getLocalBounds().width * s_Board.getScale().x;
    int boardHeight = s_Board.getLocalBounds().height * s_Board.getScale().y;

    int boardFieldWidth = boardWidth/8;
    int boardFieldHeight = boardHeight/8;

    int boardMarginLeft = 0;
    int boardMarginTop = 0;

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
                                              (float)(boardFieldWidth) / figureWidth,
                                              (float)(boardFieldHeight) / figureHeight ));

                if ( imageSequece[figurePos % qFiguresPerWidth] == King )
                {
                    if (isBlack)
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + 4*boardFieldWidth,
                                                                         boardMarginTop) );
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + 4*boardFieldWidth,
                                                                         boardMarginTop + boardHeight - boardFieldHeight) );
                    }
                }
                else if ( imageSequece[figurePos % qFiguresPerWidth] == Queen )
                {
                    if (isBlack)
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + 3*boardFieldWidth,
                                                                         boardMarginTop) );
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + 3*boardFieldWidth,
                                                                         boardMarginTop + boardHeight - boardFieldHeight) );
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
                                                  (float)(boardFieldWidth) / figureWidth,
                                                  (float)(boardFieldHeight) / figureHeight ));

                    if (isBlack)
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + i*boardFieldWidth,
                                                                         boardMarginTop + boardFieldHeight) );
                    }
                    else
                    {
                        s_Figures[currentSprite].setPosition ( Vector2f (
                                                                         boardMarginLeft + i*boardFieldWidth,
                                                                         boardMarginTop + boardHeight - 2*boardFieldHeight) );
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
                                                  (float)(boardFieldWidth) / figureWidth,
                                                  (float)(boardFieldHeight) / figureHeight ));

                    if ( imageSequece[figurePos % qFiguresPerWidth] == Rook )
                    {
                        if (isBlack)
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + i*(boardWidth - boardFieldWidth),
                                                                             boardMarginTop) );
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + i*(boardWidth - boardFieldWidth),
                                                                             boardMarginTop + boardHeight - boardFieldHeight) );
                        }
                    }
                    else if ( imageSequece[figurePos % qFiguresPerWidth] == Knight )
                    {
                        if (isBlack)
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + 1*boardFieldWidth + 5*i*boardFieldWidth,
                                                                             boardMarginTop) );
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + 1*boardFieldWidth + 5*i*boardFieldWidth,
                                                                             boardMarginTop + boardHeight - boardFieldHeight) );
                        }
                    }
                    else
                    {
                        if (isBlack)
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + 2*boardFieldWidth + 3*i*boardFieldWidth,
                                                                             boardMarginTop) );
                        }
                        else
                        {
                            s_Figures[currentSprite].setPosition ( Vector2f (
                                                                             boardMarginLeft + 2*boardFieldWidth + 3*i*boardFieldWidth,
                                                                             boardMarginTop + boardHeight - boardFieldHeight) );
                        }
                    }

                    currentSprite++;
                }
            }
            figurePos++;
        }
}
