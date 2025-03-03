#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Platform.hpp"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Player player;
    Platform platform;
    sf::Clock clock;

    void handleEvents();
    void update(float deltaTime);
    void render();
};
