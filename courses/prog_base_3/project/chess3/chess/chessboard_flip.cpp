#include "chessboard.h"
#include "resources.h"

void ChessBoard::flipView ()
{
    bFlipped = !bFlipped;

    for (int i = 0; i < 32; i++)
    {
        Vector2f pos =  s_Figures[i].getPosition();
        s_Figures[i].setPosition( pos.x, boardHeight - pos.y - boardTileHeight );
    }
}
