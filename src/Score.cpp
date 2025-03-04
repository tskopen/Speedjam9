#include "Score.hpp"
#include "Platform.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <chrono>
using namespace Constants;


void Score::draw(sf::RenderWindow& window, const sf::Font& arcadeFont, 
     std::string& elapsedTimeStr, unsigned int charSize, 
    sf::Color color, sf::Text::Style style, sf::Vector2f position) 
{


sf::Text text(arcadeFont);
text.setFont(arcadeFont);
text.setString(elapsedTimeStr);       // Set the custom string
text.setCharacterSize(charSize); // Set the custom size
text.setFillColor(color);       // Set the custom color
text.setStyle(style);           // Set the custom style
text.setPosition(position);     // Set the custom position

window.draw(text);
}
