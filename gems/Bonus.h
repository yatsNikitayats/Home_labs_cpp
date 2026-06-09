#pragma once
#include <SFML/Graphics.hpp>

enum class BonusType {
    NONE = 0,
    COLORIZE = 1,
    BOMB = 2
};


struct DropEffect {
    float x, y;
    float life;
    BonusType type;
};







