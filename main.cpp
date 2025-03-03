#include <SFML/Graphics.hpp>
#include "animation.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Animations");
    JumpAnimation animation(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        physics.CharacterMovement();
        window.clear(sf::Color::Black);
        
        animation.update();
        animation.draw();
        
        window.display();
    }

    return 0;
}