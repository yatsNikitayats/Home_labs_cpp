#pragma once
#include <SFML/Graphics.hpp>
#include "BonusType.h"

class Bonus {
public:

    Bonus(float x,
        float y,
        BonusType type);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    bool active;

    BonusType type;

    sf::Vector2f position;

    float speed;

    sf::RectangleShape shape;
};