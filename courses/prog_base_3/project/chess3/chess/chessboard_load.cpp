#include "chessboard.h"
#include "resources.h"

#include <movethread.h>
#include <selectfiguredialog.h>

#include <iostream>

using namespace std;

void ChessBoard::loadRectangles()
{
    rs_Selected = RectangleShape ( Vector2f (boardTileWidth, boardTileHeight) );
    rs_Selected.setFillColor(Color (0, 255, 0, 96));

    rs_Moving = RectangleShape ( Vector2f (boardTileWidth, boardTileHeight) );
    rs_Moving.setFillColor(Color (0, 255, 0, 64));

    rs_Check = RectangleShape ( Vector2f (boardTileWidth, boardTileHeight) );
    rs_Check.setFillColor(Color (255, 0, 0, 160));

    memset (bValid, 0, sizeof (bool)*8*8);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            rs_ValidMoveHighlight[i][j] = RectangleShape ( Vector2f (boardTileWidth, boardTileHeight) );
            rs_ValidMoveHighlight[i][j].setFillColor (Color (0, 255, 0, 48));
            rs_ValidMoveHighlight[i][j].setPosition (j*boardTileWidth, i*boardTileHeight );
        }
}

void ChessBoard::loadChessEngine ()
{
    chessEng = new ChessEngine ();
    chessEng->newGame();
}

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

    figureWidth = figuresWidth / qFiguresPerWidth;
    figureHeight = figuresHeight / qFiguresPerHeight;

    for (int i = 0; i < 32; i++)
    {
        s_Figures[i].setTexture (t_Figures);
        s_Figures[i].setScale (Vector2f (
                                      (float)(boardTileWidth) / figureWidth,
                                      (float)(boardTileHeight) / figureHeight ));
    }
    figureOriginalWidth = figureWidth;
    figureOriginalHeight = figureHeight;
    figureWidth *= s_Figures[0].getScale().x;
    figureHeight *= s_Figures[0].getScale().y;

    initFigureRects ();
}

void ChessBoard::initFigureRects ()
{
    const int qFiguresPerWidth = 6;
    const int qFiguresPerHeight = 2;

    for (int j = 0; j < qFiguresPerHeight; j++)
        for (int i = 0; i < qFiguresPerWidth; i++)
        {
            figureRects[i][j].left = i*figureOriginalWidth;
            figureRects[i][j].top = j*figureOriginalHeight;
            figureRects[i][j].width = figureOriginalWidth;
            figureRects[i][j].height = figureOriginalHeight;
        }
}
