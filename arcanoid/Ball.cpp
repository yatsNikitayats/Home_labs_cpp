#include "Ball.h"
#include "Utils.h"

Ball::Ball() {

    radius = 10.f;

    shape.setRadius(radius);
    shape.setOrigin({ radius, radius });

    shape.setFillColor(sf::Color::White);

    reset();
}

void Ball::reset() {

    position = {
        WINDOW_WIDTH / 2.f,
        WINDOW_HEIGHT / 2.f
    };

    velocity = {
        BALL_SPEED,
        -BALL_SPEED
    };
}

void Ball::update(float dt) {

    

    float stepDt =
        dt / static_cast<float>(BALL_SUBSTEPS);

    for (int i = 0; i < BALL_SUBSTEPS; i++) {

        position += velocity * stepDt;
    }

    shape.setPosition(position);
}

void Ball::draw(sf::RenderWindow& window) {

    shape.setPosition(position);

    window.draw(shape);
}