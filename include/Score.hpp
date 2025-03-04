#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
#include "Constants.hpp"

class Score {
public:
    void Timer();
    void draw(sf::RenderWindow& window, const sf::Font& arcadeFont, 
         std::string& elapsedTimeStr, unsigned int charSize, 
        sf::Color color, sf::Text::Style style, sf::Vector2f position);

private:
    sf::Clock clock;
};
