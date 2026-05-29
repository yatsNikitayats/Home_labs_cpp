#pragma once

class Ball;
class Level;
class BonusManager;

class CollisionManager {
public:

    static int handleBlockCollisions(
        Ball& ball,
        Level& level,
        BonusManager& bonuses
    );
};