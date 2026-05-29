#include "BonusManager.h"

#include "Paddle.h"
#include "Ball.h"

#include <random>
#include <cmath>
#include <algorithm>

void BonusManager::spawn(float x,
    float y) {

    int t = rand() % 7;

    BonusType type =
        static_cast<BonusType>(t);

    bonuses.emplace_back(x, y, type);
}

void BonusManager::update(float dt) {

    for (auto& b : bonuses) {

        if (!b.active)
            continue;

        b.update(dt);

        if (b.position.y > 800.f) {
            b.active = false;
        }
    }

    bonuses.erase(
        std::remove_if(
            bonuses.begin(),
            bonuses.end(),
            [](const Bonus& b) {
                return !b.active;
            }),
        bonuses.end()
    );
}

void BonusManager::draw(sf::RenderWindow& window) {

    for (auto& b : bonuses) {
        b.draw(window);
    }
}

void BonusManager::handlePaddleCollision(
    Paddle& paddle,
    Ball& ball,
    bool& stickyEnabled,
    bool& bottomWall
) {

    for (auto& b : bonuses) {

        if (!b.active)
            continue;

        float left =
            paddle.position.x -
            paddle.width / 2.f;

        float right =
            paddle.position.x +
            paddle.width / 2.f;

        float top =
            paddle.position.y -
            paddle.height / 2.f;

        float bottom =
            paddle.position.y +
            paddle.height / 2.f;

        bool overlapX =
            b.position.x >= left &&
            b.position.x <= right;

        bool overlapY =
            b.position.y >= top &&
            b.position.y <= bottom;

        if (!overlapX || !overlapY)
            continue;

        b.active = false;

        switch (b.type) {

        case BonusType::BIG_PADDLE:

            paddle.width += 40.f;

            paddle.shape.setSize({
                paddle.width,
                paddle.height
                });

            paddle.shape.setOrigin({
                paddle.width / 2.f,
                paddle.height / 2.f
                });

            break;

        case BonusType::SMALL_PADDLE:

            paddle.width -= 30.f;

            if (paddle.width < 60.f)
                paddle.width = 60.f;

            paddle.shape.setSize({
                paddle.width,
                paddle.height
                });

            paddle.shape.setOrigin({
                paddle.width / 2.f,
                paddle.height / 2.f
                });

            break;

        case BonusType::FAST_BALL:

            ball.velocity *= 1.3f;

            break;

        case BonusType::SLOW_BALL:

            ball.velocity *= 0.8f;

            break;

        case BonusType::STICKY:

            stickyEnabled = true;

            break;

        case BonusType::BOTTOM_WALL:

            bottomWall = true;

            break;

        case BonusType::RANDOM_TRAJECTORY:

        {
            float speed =
                std::sqrt(
                    ball.velocity.x *
                    ball.velocity.x +

                    ball.velocity.y *
                    ball.velocity.y
                );

            float angle =
                (rand() % 120 - 60)
                * 3.14159f / 180.f;

            ball.velocity.x =
                std::cos(angle) * speed;

            ball.velocity.y =
                -std::abs(
                    std::sin(angle) * speed
                );
        }

        break;
        }

        float maxSpeed = 900.f;

        if (std::abs(ball.velocity.x) > maxSpeed) {

            ball.velocity.x =
                (ball.velocity.x > 0.f ? 1.f : -1.f)
                * maxSpeed;
        }

        if (std::abs(ball.velocity.y) > maxSpeed) {

            ball.velocity.y =
                (ball.velocity.y > 0.f ? 1.f : -1.f)
                * maxSpeed;
        }
    }
}