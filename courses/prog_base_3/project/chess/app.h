#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "settings.h"
#include "resources.h"

#include "chessboard.h"
#include "layout.h"

using namespace sf;

class App
{
    public:
        App ();
        ~App ();

        int exec ();

    private:
        RenderWindow* pWindow;
        ChessBoard* pBoard;
        Layout* pLayout;
};

#endif // APP_H_INCLUDED
