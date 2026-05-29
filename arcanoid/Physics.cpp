#include "Physics.h"

#include "Ball.h"
#include "Paddle.h"
#include "Utils.h"

void Physics::handleWallCollision(
    Ball& ball
) {

    if (ball.position.x - ball.radius <= 0.f) {

        ball.position.x =
            ball.radius;

        ball.velocity.x *= -1.f;
    }

    if (ball.position.x + ball.radius >= WINDOW_WIDTH) {

        ball.position.x =
            WINDOW_WIDTH - ball.radius;

        ball.velocity.x *= -1.f;
    }

    if (ball.position.y - ball.radius <= 0.f) {

        ball.position.y =
            ball.radius;

        ball.velocity.y *= -1.f;
    }
}

void Physics::handlePaddleCollision(
    Ball& ball,
    const Paddle& paddle,
    bool& stickyEnabled,
    bool& ballAttached
) {

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
        ball.position.x + ball.radius >= left &&
        ball.position.x - ball.radius <= right;

    bool overlapY =
        ball.position.y + ball.radius >= top &&
        ball.position.y - ball.radius <= bottom;

    if (overlapX &&
        overlapY &&
        ball.velocity.y > 0.f) {

        ball.position.y =
            top - ball.radius;

        float hitPos =
            (ball.position.x -
                paddle.position.x)
            / (paddle.width / 2.f);

        ball.velocity.x =
            hitPos * 500.f;

        if (stickyEnabled) {

            ballAttached = true;

            stickyEnabled = false;

            return;
        }

        ball.velocity.y *= -1.f;
    }
}