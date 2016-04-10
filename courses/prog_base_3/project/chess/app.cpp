#include "app.h"

App::App ()
{
    pWindow = new RenderWindow (sf::VideoMode(screenWidth, screenHeight),
                                szAppName,
                                (fullscreenMode == true) ? Style::Fullscreen : Style::Default);
    pBoard = new ChessBoard (pWindow);
    pBoard->setPosition(Vector2f (
                                     screenWidth/2 - pBoard->getLocalBounds().width/2,
                                     screenHeight/2 - pBoard->getLocalBounds().height/2));

    pLayout = new Layout (pWindow, pBoard);
}

App::~App ()
{
    delete pWindow;
    delete pBoard;
    delete pLayout;
}

int App::exec ()
{
    while (pWindow->isOpen())
    {
        Event event;
        while (pWindow->pollEvent(event))
        {
            if (event.type == Event::Closed)
                pWindow->close();
        }

        pWindow->clear();

        pLayout->display();

        pWindow->display();
    }
    return 0;
}
