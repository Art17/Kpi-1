#ifndef CHESSBOARD_H_INCLUDED
#define CHESSBOARD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "resources.h"

using namespace sf;

class ChessBoard
{
    public:
        ChessBoard (RenderWindow* );
        ~ChessBoard ();

        void draw ();
        void setPosition (Vector2f);

        FloatRect getLocalBounds ();


    private:
        RenderWindow* windowPtr;

        Texture t_Board;
        Sprite  s_Board;

        int boardWidth;
        int boardHeight;
};

#endif // CHESSBOARD_H_INCLUDED
