#include "CollisionManager.h"

#include "Ball.h"
#include "Level.h"
#include "BlockType.h"
#include "BonusManager.h"

#include <cmath>

int CollisionManager::handleBlockCollisions(
    Ball& ball,
    Level& level,
    BonusManager& bonuses
) {

    int score = 0;

    for (auto& block : level.blocks) {

        if (block.isDestroyed())
            continue;

        float left =
            block.position.x -
            block.width / 2.f;

        float right =
            block.position.x +
            block.width / 2.f;

        float top =
            block.position.y -
            block.height / 2.f;

        float bottom =
            block.position.y +
            block.height / 2.f;

        bool overlapX =
            ball.position.x + ball.radius >= left &&
            ball.position.x - ball.radius <= right;

        bool overlapY =
            ball.position.y + ball.radius >= top &&
            ball.position.y - ball.radius <= bottom;

        if (!overlapX || !overlapY)
            continue;

        float overlapLeft =
            (ball.position.x + ball.radius) - left;

        float overlapRight =
            right - (ball.position.x - ball.radius);

        float overlapTop =
            (ball.position.y + ball.radius) - top;

        float overlapBottom =
            bottom - (ball.position.y - ball.radius);

        float minOverlapX =
            std::min(overlapLeft, overlapRight);

        float minOverlapY =
            std::min(overlapTop, overlapBottom);

        if (minOverlapX < minOverlapY) {

            ball.velocity.x *= -1.f;

            if (overlapLeft < overlapRight) {

                ball.position.x =
                    left - ball.radius - 1.f;
            }
            else {

                ball.position.x =
                    right + ball.radius + 1.f;
            }
        }
        else {

            ball.velocity.y *= -1.f;

            if (overlapTop < overlapBottom) {

                ball.position.y =
                    top - ball.radius - 1.f;
            }
            else {

                ball.position.y =
                    bottom + ball.radius + 1.f;
            }
        }

        if (block.type !=
            BlockType::UNBREAKABLE) {

            block.hp--;

            if (block.type == BlockType::BONUS &&
                block.hp == 0) {

                bonuses.spawn(
                    block.position.x,
                    block.position.y
                );
            }

            score++;
        }

        if (block.type ==
            BlockType::SPEED) {

            ball.velocity *= 1.15f;

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

        break;
    }

    return score;
}