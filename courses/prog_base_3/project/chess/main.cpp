#include <SFML/Graphics.hpp>

#include <stdio.h> // for debug

#include "settings.h"
#include "resources.h"

#include "chessboard.h"

using namespace sf;

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

    /*  Loading and creating textures   */
    Texture t_Background;
    t_Background.loadFromFile(szBackground);
    /*                  */

    /*  Loading and creating sprites    */
    Sprite s_Background;
    s_Background.setTexture(t_Background);
    /*                  */

    /*  sprites data(width, height etc)  */
    int backgroundWidth = s_Background.getLocalBounds().width;
    int backgroundHeight = s_Background.getLocalBounds().height;
    /*                                   */

    /*  positioning, scaling sprites    */
    s_Background.setScale (Vector2f (
                                     (float)screenWidth / backgroundWidth,
                                     (float)screenHeight / backgroundHeight));     //  make background fullscreen

    /*                                  */

    while (mainWindow.isOpen())
    {
        Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
                mainWindow.close();
        }

        mainWindow.clear();
        mainWindow.draw (s_Background);
        chessBoard.show ();
        mainWindow.display();
    }

    return 0;
}
