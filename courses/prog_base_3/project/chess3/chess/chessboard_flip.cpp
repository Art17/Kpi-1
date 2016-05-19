#include "chessboard.h"
#include "resources.h"

#include <iostream>

void ChessBoard::flipView ()
{
    for (int i = 0; i < 32; i++)
    {
        Vector2f pos =  s_Figures[i].getPosition();
        s_Figures[i].setPosition( pos.x, boardHeight - pos.y - boardTileHeight );
    }
    cout << "Before" << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << indexTable[i][j] << " ";

        }
        cout << endl;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int temp = indexTable[i][j];
            indexTable[i][j] = indexTable[7-i][j];
            indexTable[7-i][j] = temp;

            temp = figuresTable[i][j];
            figuresTable[i][j] = figuresTable[7-i][j];
            figuresTable[7-i][j] = temp;

        }
    }
    cout << "After" << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << indexTable[i][j] << " ";

        }
        cout << endl;
    }
}
