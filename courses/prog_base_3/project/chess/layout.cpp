#include "layout.h"
#include "resources.h"

Layout::Layout (RenderWindow* pWindow, ChessBoard* pBoard)
{
    t_Background.loadFromFile (szBackground);
    s_Background.setTexture (t_Background);

    backgroundWidth = s_Background.getLocalBounds().width;
    backgroundHeight = s_Background.getLocalBounds().height;

    s_Background.setScale (Vector2f (
                                     (float)screenWidth / backgroundWidth,
                                     (float)screenHeight / backgroundHeight)); // make background fullscreen

    this->pWindow = pWindow;
    this->pBoard = pBoard;
}

Layout::~Layout ()
{

}

void Layout::display ()
{
    pWindow->draw (s_Background);
    pBoard->draw();
}
