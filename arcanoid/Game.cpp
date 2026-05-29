#include "Game.h"

#include "Physics.h"
#include "CollisionManager.h"
#include "Utils.h"

Game::Game()
    : window(
        sf::VideoMode({
            WINDOW_WIDTH,
            WINDOW_HEIGHT
            }),
        "Arkanoid"
    ),
    score(0),
    lives(3),
    stickyEnabled(false),
    ballAttached(false),
    bottomWall(false)
{
    window.setFramerateLimit(144);
}

void Game::resetRound() {

    ball.reset();

    paddle.reset();

    stickyEnabled = false;

    ballAttached = false;

    bottomWall = false;
}

void Game::update(float dt) {

    paddle.update(dt);

    if (!ballAttached) {

        ball.update(dt);
    }
    else {

        ball.position.x =
            paddle.position.x;

        ball.position.y =
            paddle.position.y - 30.f;

        if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::Space)) {

            ballAttached = false;

            ball.velocity = {
                BALL_SPEED,
                -BALL_SPEED
            };
        }
    }

    Physics::handleWallCollision(ball);

    Physics::handlePaddleCollision(
        ball,
        paddle,
        stickyEnabled,
        ballAttached
    );

    score +=
        CollisionManager::
        handleBlockCollisions(
            ball,
            level,
            bonusManager
        );

    bonusManager.update(dt);

    bonusManager.handlePaddleCollision(
        paddle,
        ball,
        stickyEnabled,
        bottomWall
    );

    if (ball.position.y - ball.radius >
        WINDOW_HEIGHT) {

        if (bottomWall) {

            bottomWall = false;

            ball.velocity.y =
                -std::abs(ball.velocity.y);

            ball.position.y =
                WINDOW_HEIGHT -
                ball.radius - 10.f;
        }
        else {

            lives--;

            resetRound();

            if (lives <= 0) {

                lives = 3;

                score = 0;

                level.generate();
            }
        }
    }
}

void Game::render() {

    window.clear(sf::Color::Black);

    level.draw(window);

    bonusManager.draw(window);

    paddle.draw(window);

    ball.draw(window);

    window.display();
}

void Game::run() {

    while (window.isOpen()) {

        float dt =
            clock.restart().asSeconds();

        while (const auto event =
            window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        update(dt);

        render();
    }
}