#include "Block.h"

Block::Block(float x,
    float y,
    BlockType t,
    int health)
    : type(t),
    hp(health) {

    position = { x, y };

    width = 72.f;
    height = 28.f;

    shape.setSize({ width, height });
    shape.setOrigin({ width / 2.f, height / 2.f });

    switch (type) {

    case BlockType::NORMAL:
        shape.setFillColor(sf::Color::Red);
        break;

    case BlockType::UNBREAKABLE:
        shape.setFillColor(sf::Color(120, 120, 120));
        break;

    case BlockType::SPEED:
        shape.setFillColor(sf::Color::Yellow);
        break;

    case BlockType::BONUS:
        shape.setFillColor(sf::Color::Cyan);
        break;
    }
}

void Block::draw(sf::RenderWindow& window) {

    if (isDestroyed())
        return;

    shape.setPosition(position);

    window.draw(shape);
}

bool Block::isDestroyed() const {

    if (type == BlockType::UNBREAKABLE)
        return false;

    return hp <= 0;
}