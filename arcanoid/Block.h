#pragma once
#include <SFML/Graphics.hpp>
#include "BlockType.h"

class Block {
public:
    Block(float x,
        float y,
        BlockType type,
        int hp);

    void draw(sf::RenderWindow& window);

    bool isDestroyed() const;

    sf::Vector2f position;

    float width;
    float height;

    int hp;

    BlockType type;

    sf::RectangleShape shape;
};