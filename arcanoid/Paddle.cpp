#include "Paddle.h"

#include "Utils.h"

Paddle::Paddle() {

    reset();
}

void Paddle::reset() {

    width = 140.f;

    height = 20.f;

    position = {
        WINDOW_WIDTH / 2.f,
        WINDOW_HEIGHT - 40.f
    };

    shape.setSize({
        width,
        height
        });

    shape.setOrigin({
        width / 2.f,
        height / 2.f
        });

    shape.setFillColor(sf::Color::White);

    shape.setPosition(position);
}

void Paddle::update(float dt) {

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::A)) {

        position.x -=
            PADDLE_SPEED * dt;
    }

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::D)) {

        position.x +=
            PADDLE_SPEED * dt;
    }

    float half =
        width / 2.f;

    if (position.x < half)
        position.x = half;

    if (position.x >
        WINDOW_WIDTH - half) {

        position.x =
            WINDOW_WIDTH - half;
    }

    shape.setPosition(position);
}

void Paddle::draw(
    sf::RenderWindow& window
) {

    window.draw(shape);
}