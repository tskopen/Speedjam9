#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <thread>
#include <chrono>

void jumpAnimation()
{
  sf::Texture slime("slimes.png", false, sf::IntRect({0, 0}, {256, 75}));
  sf::Sprite character(slime);
  character.setTextureRect(sf::IntRect({96, 50}, {32, 25}));
}



int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds


    // Create window with Vector2u for VideoMode
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(600, 600)), "SFML Window");

    //Sprite
    sf::Texture slime("slimes.png", false, sf::IntRect({0, 0}, {256, 75}));
    sf::Sprite character(slime);

    window.draw(character);

    // testing loop
    while (window.isOpen())
    {
        //reset animation
        character.setTextureRect(sf::IntRect({0, 0}, {32, 25}));

        //Game movement speed
        std::optional<sf::Event> event = window.pollEvent();

        window.clear(sf::Color::Black);
        window.setTitle("Animations");    

        if (event)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                character.setTextureRect(sf::IntRect({96, 50}, {32, 25}));

                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
              jumpAnimation();
            }

        //Update position
        window.draw(character);
        window.display();
          }
    }
    return 0;
}

