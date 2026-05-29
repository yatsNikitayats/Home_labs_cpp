#pragma once
#include <vector>

#include "Bonus.h"

class Paddle;
class Ball;

class BonusManager {
public:

    void spawn(float x,
        float y);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    void handlePaddleCollision(
        Paddle& paddle,
        Ball& ball,
        bool& stickyEnabled,
        bool& bottomWall
    );

    std::vector<Bonus> bonuses;
};