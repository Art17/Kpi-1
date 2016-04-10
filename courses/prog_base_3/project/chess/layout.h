#ifndef LAYOUT_H_INCLUDED
#define LAYOUT_H_INCLUDED

#include "chessboard.h"

class Layout
{
    public:
        Layout (RenderWindow*, ChessBoard*);
        ~Layout ();

        void display ();


    private:
        RenderWindow* windowPtr;
        ChessBoard* boardPtr;

        Texture t_Background;
        Sprite  s_Background;

        int backgroundWidth;
        int backgroundHeight;
};

#endif // LAYOUT_H_INCLUDED
