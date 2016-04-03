#include <SFML/Graphics.hpp>

#include <stdio.h> // for debug

#include "settings.h"
#include "resources.h"

using namespace sf;

int main()
{
    /* Creating window  */
    RenderWindow mainWindow(sf::VideoMode(screenWidth, screenHeight),
                        szAppName,
                        (fullscreenMode == true) ? Style::Fullscreen : Style::Default);
    /*                  */

    /*  Loading and creating textures   */
    Texture t_Field;
    t_Field.loadFromFile (szField);

    Texture t_Background;
    t_Background.loadFromFile(szBackground);
    /*                  */

    /*  Loading and creating sprites    */
    Sprite s_Field;
    s_Field.setTexture (t_Field);

    Sprite s_Background;
    s_Background.setTexture(t_Background);
    /*                  */

    /*  sprites data(width, height etc)  */
    int boardWidth = s_Field.getLocalBounds().width;
    int boardHeight = s_Field.getLocalBounds().height;

    int backgroundWidth = s_Background.getLocalBounds().width;
    int backgroundHeight = s_Background.getLocalBounds().height;
    /*                                   */

    /*  positioning, scaling sprites    */
    s_Field.setPosition(Vector2f(screenWidth/2 - boardWidth/2,
                                 screenHeight/2 - boardHeight/2));

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
        mainWindow.draw (s_Field);
        mainWindow.display();
    }

    return 0;
}
