#include <SFML/Graphics.hpp>

#include <stdio.h> // for debug

#include "settings.h"
#include "resources.h"

#include "chessboard.h"
#include "layout.h"

using namespace sf;

void mainLoop (RenderWindow*, Layout*);     // app cycle

int main()
{
    /* Creating window  */
    RenderWindow mainWindow(sf::VideoMode(screenWidth, screenHeight),
                        szAppName,
                        (fullscreenMode == true) ? Style::Fullscreen : Style::Default);
    /*                  */
    /*  Initializing chess board class  */
    ChessBoard chessBoard (&mainWindow);
    chessBoard.setPosition(Vector2f (
                                     screenWidth/2 - chessBoard.getLocalBounds().width/2,
                                     screenHeight/2 - chessBoard.getLocalBounds().height/2));
    /*                                  */

    /*  Initializing main layout    */
    Layout mainLayout (&mainWindow, &chessBoard);
    /*                              */

    mainLoop (&mainWindow, &mainLayout);    // app cycle

    return 0;
}

void mainLoop (RenderWindow* windowPtr, Layout* layoutPtr)
{
    while (windowPtr->isOpen())
    {
        Event event;
        while (windowPtr->pollEvent(event))
        {
            if (event.type == Event::Closed)
                windowPtr->close();
        }

        windowPtr->clear();

        layoutPtr->display();

        windowPtr->display();
    }
}
