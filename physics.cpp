#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <thread>
#include <chrono>

int main()
{
    // Create window with Vector2u for VideoMode
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Window");

    sf::CircleShape character(50.f);

    // set the shape color to green
    character.setFillColor(sf::Color::Green);   
    window.draw(character);

//Physics Declarations
sf::Vector2f gravity(0, 10);
sf::Vector2f velocity(0, 0);
    // Game loop
    while (window.isOpen())
    {
        //reset acceleration
        sf::Vector2f acceleration(0, 0);

        //Game movement speed
        std::optional<sf::Event> event = window.pollEvent();

        window.clear(sf::Color::Black);
        window.setTitle("I hate that faggot chatgpt");    
        //inputs
        if (event)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                acceleration.x += -.1;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                acceleration.x += .1;
            }
            
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                acceleration.y += -.1;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                acceleration.y += .1;
            }

        }
        //calculate velocity
        velocity.x += acceleration.x;
        velocity.y += acceleration.y;
        //Update position
        character.move(velocity);
        window.draw(character);
        window.display();
    }
    return 0;
}





/*

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <thread>
#include <optional>

int main()
{
    // Window setup
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Window");
    sf::CircleShape character(50.f);
    character.setFillColor(sf::Color::Green);   

//Physics Declarations
    sf::Vector2f gravity(0, 10);
    sf::Vector2f velocity(0, 0);



//movement loop
    while (window.isOpen())
    {   
        window.clear(sf::Color::Black);
        window.setTitle("I hate that Censored chatgpt");
        window.draw(character);
        window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                velocity.x += -1;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                velocity.x += 1;
            }
            
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                velocity.y += -1;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                velocity.y += 1;
            }
            //Update window
            character.move(velocity);
            window.display();
            std::this_thread::sleep_for(std::chrono::seconds(1));


    }
    return 0;
}


*/