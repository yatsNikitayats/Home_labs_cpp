#pragma once
#include <vector>
#include "Block.h"

class Level {
public:
    Level();

    void generate();

    void draw(sf::RenderWindow& window);

    std::vector<Block> blocks;
};