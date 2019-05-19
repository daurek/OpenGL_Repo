// Libraries
#include <SFML/Window.hpp>
// Project
#include "Scene.hpp"

int main ()
{
    // SFML Window
	sf::Vector2u screenDimension(1280, 720);
    sf::Window window(sf::VideoMode(screenDimension.x, screenDimension.y), "OpenGL_Scene", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled (true);

    // Initialize Glew
    GLenum glew_initialization =  glewInit ();
    assert(glew_initialization == GLEW_OK);

	// Clear and display loading screen
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	window.display();

	// Create Scene
    openglScene::Scene scene(screenDimension.x, screenDimension.y);

	// Start loop
    bool running = true;

    do
    {
		// Check for window events
        sf::Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
			case sf::Event::Closed:
                {
                    running = false;
                    break;
                }

			case sf::Event::Resized:
                {
					// Resize window when changed 
                    sf::Vector2u window_size = window.getSize ();
                    scene.Resize (window_size.x, window_size.y);
                    break;
                }
            }
        }

		// Update Scene
        scene.Update ();
		// Render Scene
        scene.Render ();
		// Display window
        window.display ();
    }
    while (running);

    return (EXIT_SUCCESS);
}
