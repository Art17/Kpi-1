#include "layout.h"
#include "resources.h"

Layout::Layout (RenderWindow* windowPtr, ChessBoard* boardPtr)
{
    t_Background.loadFromFile (szBackground);
    s_Background.setTexture (t_Background);

    backgroundWidth = s_Background.getLocalBounds().width;
    backgroundHeight = s_Background.getLocalBounds().height;

    s_Background.setScale (Vector2f (
                                     (float)screenWidth / backgroundWidth,
                                     (float)screenHeight / backgroundHeight)); // make background fullscreen

    this->windowPtr = windowPtr;
    this->boardPtr = boardPtr;
}

Layout::~Layout ()
{

}

void Layout::display ()
{
    windowPtr->draw (s_Background);
    boardPtr->show();
}
