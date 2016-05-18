#include "chessboard.h"
#include "resources.h"

#include <chessboard_movethread.h>
#include <selectfiguredialog.h>

#include <iostream>

using namespace std;

void ChessBoard::resetVariables()
{
    unselect ();
    bWhiteCheck = false;
    bBlackCheck = false;

    bAgainstComputer = false;
    bFlipped = false;
    bLocked = false;
}

void ChessBoard::fillTable ()
{
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
}

void ChessBoard::setSpritesPositionAndRects()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            indexTable[i][j] = -1;
    int currentSprite = 0;
    for (int c = 0; c < 2; c++)
        for (int i = 0; i < 8; i++)
        {
            setSpriteRect( &s_Figures[currentSprite], Pawn | ((c==0) ? colorWhite : 0) );
            s_Figures[currentSprite].setPosition(Vector2f(i*boardTileWidth, ((c==0)?6:1)*boardTileHeight));
            indexTable[ ((c==0)?6:1) ][i] = currentSprite++;
        }
    int figuresArray[] = {Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook};
    for (int c = 0; c < 2; c++)
    {
        for (int i = 0; i < 8; i++)
        {
            setSpriteRect( &s_Figures[currentSprite], figuresArray[i] | ((c==0) ? colorWhite : 0) );
            s_Figures[currentSprite].setPosition(Vector2f(boardTileWidth*i, ((c==0)?7:0)*boardTileHeight));
            indexTable[ ((c==0)?7:0) ][i] = currentSprite++;
        }
    }
    /*for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << indexTable[i][j] << " ";
        cout << endl;
    }*/
}


void ChessBoard::setSpriteRect(Sprite* pSprite, int figure)
{
    const int imageSequece[] = {King, Queen, Bishop, Knight, Rook, Pawn};
    int index = -1;
    for (int i = 0; i < 6; i++)
        if (figure & imageSequece[i])
        {
            index = i;
            break;
        }
    pSprite->setTextureRect(figureRects[index][!isWhite(figure)]);

}

void ChessBoard::clearJournal()
{
    journal.clear();
}

void ChessBoard::unselect()
{
    iSelectedTileX = -1;
    iSelectedTileY = -1;
    iSelectedFigure = -1;

    memset (bValid, 0, sizeof (bool)*8*8);
}
