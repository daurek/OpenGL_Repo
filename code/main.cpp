
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Scene.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;
using namespace openglScene;

int main ()
{
    // SFML Window
	sf::Vector2i screenDimension(800, 600);
    Window window(VideoMode(screenDimension.x, screenDimension.y), "OpenGL_Scene", Style::Default, ContextSettings(32));
    window.setVerticalSyncEnabled (true);

    // Initialize Glew
    GLenum glew_initialization =  glewInit ();
    assert(glew_initialization == GLEW_OK);

    Scene scene(screenDimension.x, screenDimension.y);

    bool running = true;

    do
    {
        Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
                case Event::Closed:
                {
                    running = false;
                    break;
                }

                case Event::Resized:
                {
                    Vector2u window_size = window.getSize ();
                    scene.Resize (window_size.x, window_size.y);
                    break;
                }
            }
        }

        glClear (GL_COLOR_BUFFER_BIT);
        scene.Update ();
        scene.Render ();
        window.display ();
    }
    while (running);

    return (EXIT_SUCCESS);
}
