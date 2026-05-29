#pragma once

#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Paddle.h"
#include "Level.h"
#include "BonusManager.h"

class Game {
public:

    Game();

    void run();

private:

    void update(float dt);

    void render();

    void resetRound();

    sf::RenderWindow window;

    Ball ball;

    Paddle paddle;

    Level level;

    BonusManager bonusManager;

    int score;

    int lives;

    bool stickyEnabled;
    bool ballAttached;

    bool bottomWall;

    sf::Clock clock;
};