#pragma once

class Ball;
class Paddle;

class Physics {
public:

    static void handleWallCollision(
        Ball& ball
    );

    static void handlePaddleCollision(
        Ball& ball,
        const Paddle& paddle,
        bool& stickyEnabled,
        bool& ballAttached
    );
};