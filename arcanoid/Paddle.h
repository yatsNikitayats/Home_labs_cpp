#pragma once

#include <SFML/Graphics.hpp>

class Paddle {
public:

    Paddle();

    void update(float dt);

    void draw(sf::RenderWindow& window);

    void reset();

    sf::Vector2f position;

    float width;

    float height;

    sf::RectangleShape shape;
};