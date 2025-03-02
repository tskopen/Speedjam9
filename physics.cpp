#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <thread>
#include <chrono>

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds


    // Create window with Vector2u for VideoMode
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(600, 1200)), "SFML Window");

    //Sprite
    sf::Texture slime("slimes.png", false, sf::IntRect({0, 0}, {32, 25}));
    sf::Sprite character(slime);

    window.draw(character);

//Physics Declarations
sf::Vector2f gravity(0, 10);
sf::Vector2f velocity(0, 0);
    // Game loop
    while (window.isOpen())
    {
        //reset animation

        //reset acceleration
        sf::Vector2f acceleration(0, 0);
        //Gravity
        //acceleration.y += .0002;
        //Drag
        velocity.y = velocity.y / 1.002;
        velocity.x = velocity.x / 1.002;

        std::optional<sf::Event> event = window.pollEvent();

        window.clear(sf::Color::Black);
        window.setTitle("Testing");    
        //inputs

        if (event)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }
//Special Moves
            //Big jump
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                acceleration.y += -.5;
                
            }
//WASD Movement
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                acceleration.x += -.15;
                //Slide
                sleep_for(nanoseconds(10));
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
                {
                    velocity.x = velocity.x * 2.5;
                }
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                acceleration.x += .15;
                //Slide
                sleep_for(nanoseconds(10));
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
                {
                    velocity.x = velocity.x * 2.5;
                }
            }
            
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                acceleration.y += -.25;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                acceleration.y += .15;
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