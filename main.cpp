#include <SFML/Graphics.hpp>
#include "Users/tskopen/Game/Speedjam9-2.0/physics"
#include <optional>
int main()
{
    // Create window with Vector2u for VideoMode
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Window");

    sf::CircleShape shape(50.f);

    // set the shape color to green
    shape.setFillColor(sf::Color::Green);   

    
    // Game loop
    while (window.isOpen())
    {
        std::optional<sf::Event> event = window.pollEvent();

        window.clear(sf::Color::Black);
        window.setTitle("I hate that faggot chatgpt");
        window.draw(shape);
    
        window.display();

        if (event)
        {
            // Use SFML 3.0's new event type check syntax
            if (event->is<sf::Event::Closed>())
                {
                    
                }
        }

    }
    return 0;
}