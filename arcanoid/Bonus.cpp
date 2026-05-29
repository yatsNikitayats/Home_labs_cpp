#include "Bonus.h"

Bonus::Bonus(float x,
    float y,
    BonusType t)
    : type(t),
    active(true),
    speed(240.f)
{
    position = { x, y };

    shape.setSize({ 24.f, 24.f });

    shape.setOrigin({ 12.f, 12.f });

    switch (type) {

    case BonusType::BIG_PADDLE:
        shape.setFillColor(sf::Color::Green);
        break;

    case BonusType::SMALL_PADDLE:
        shape.setFillColor(sf::Color::Red);
        break;

    case BonusType::FAST_BALL:
        shape.setFillColor(sf::Color::Yellow);
        break;

    case BonusType::SLOW_BALL:
        shape.setFillColor(sf::Color::Blue);
        break;

    case BonusType::STICKY:
        shape.setFillColor(sf::Color::Magenta);
        break;

    case BonusType::BOTTOM_WALL:
        shape.setFillColor(sf::Color::Cyan);
        break;

    case BonusType::RANDOM_TRAJECTORY:
        shape.setFillColor(sf::Color::White);
        break;
    }
}

void Bonus::update(float dt) {

    position.y += speed * dt;
}

void Bonus::draw(sf::RenderWindow& window) {

    if (!active)
        return;

    shape.setPosition(position);

    window.draw(shape);
}