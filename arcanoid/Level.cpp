#include "Level.h"

Level::Level() {

    generate();
}

void Level::generate() {

    blocks.clear();

    const int rows = 6;
    const int cols = 12;

    const float blockWidth = 72.f;
    const float blockHeight = 28.f;

    const float startX = 50.f;
    const float startY = 60.f;

    const float gap = 1.f;

    for (int y = 0; y < rows; y++) {

        for (int x = 0; x < cols; x++) {

            float bx =
                startX +
                x * (blockWidth + gap);

            float by =
                startY +
                y * (blockHeight + gap);

            BlockType type =
                BlockType::NORMAL;

            int hp = 1;

            if ((x + y) % 11 == 0) {

                type =
                    BlockType::UNBREAKABLE;
            }
            else if ((x + y) % 7 == 0) {

                type =
                    BlockType::SPEED;
            }
            else if ((x + y) % 5 == 0) {

                type =
                    BlockType::BONUS;
            }
            else if ((x + y) % 3 == 0) {

                hp = 2;
            }

            blocks.emplace_back(
                bx,
                by,
                type,
                hp
            );
        }
    }
}

void Level::draw(
    sf::RenderWindow& window
) {

    for (auto& block : blocks) {

        block.draw(window);
    }
}