#pragma once
#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball();

    void update(float dt);

    void draw(sf::RenderWindow& window);

    void reset();

    sf::Vector2f position;
    sf::Vector2f velocity;

    float radius;

    sf::CircleShape shape;
};