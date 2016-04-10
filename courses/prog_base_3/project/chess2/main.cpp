#include <stdio.h>
#include <memory.h>
#include <SFML/Graphics.hpp>
#include "resources.h"
#include "settings.h"


using namespace sf;

enum Figures {Pawn = 1, Knight, Bishop, Rook, Queen, King};

int main()
{
    RenderWindow* pWindow = new RenderWindow (sf::VideoMode(screenWidth, screenHeight),
                                                  szAppName,
                                                  (fullscreenMode == true) ? Style::Fullscreen : Style::Default);

    Texture t_Background;
    Sprite  s_Background;

    Texture t_Board;
    Sprite  s_Board;

    const int qFigures = 32;
    Texture t_Figures;
    Sprite s_Figures[qFigures];

    int backgroundWidth, backgroundHeight;
    int boardWidth, boardHeight;
    int boardMarginTop, boardMarginLeft;
    int boardFieldWidth, boardFieldHeight;
    int figuresWidth, figuresHeight;
    int figureWidth, figureHeight;

    const int qFiguresPerWidth = 6;
    const int qFiguresPerHeight = 2;
    const int imageSequece[] = {King, Queen, Bishop, Knight, Rook, Pawn};

    t_Figures.loadFromFile (szFigures);
    figuresWidth = t_Figures.getSize().x;
    figuresHeight = t_Figures.getSize().y;

    figureWidth = figuresWidth / qFiguresPerWidth;
    figureHeight = figuresHeight / qFiguresPerHeight;

    t_Background.loadFromFile (szBackground);
    s_Background.setTexture (t_Background);

    t_Board.loadFromFile (szField);
    s_Board.setTexture (t_Board);

    boardWidth = s_Board.getLocalBounds().width;
    boardHeight = s_Board.getLocalBounds().height;

    boardFieldWidth = boardWidth/8;
    boardFieldHeight = boardHeight/8;

    backgroundWidth = s_Background.getLocalBounds().width;
    backgroundHeight = s_Background.getLocalBounds().height;

    s_Background.setScale (Vector2f (
                                     (float)screenWidth / backgroundWidth,
                                     (float)screenHeight / backgroundHeight)); // make background fullscreen

    boardMarginLeft = screenWidth/2 - s_Board.getLocalBounds().width/2;
    boardMarginTop = screenHeight/2 - s_Board.getLocalBounds().height/2;
    s_Board.setPosition(Vector2f (
                                     boardMarginLeft,
                                     boardMarginTop ));

    int figurePos = 0;
    int currentSprite = 0;
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


    while (pWindow->isOpen())
    {
        Event event;
        while (pWindow->pollEvent(event))
        {
            if (event.type == Event::Closed)
                pWindow->close();
        }

        pWindow->clear();
        pWindow->draw (s_Background);
        pWindow->draw (s_Board);
        for (int i = 0; i < qFigures; i++)
            pWindow->draw (s_Figures[i]);
        pWindow->display();
    }

    delete pWindow;

    return 0;
}
