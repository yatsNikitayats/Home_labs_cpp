#include "NormalCell.h"
#include "Utils.h"

NormalCell::NormalCell(int col) : color(col) {}

int NormalCell::getColorValue() const {
    return color;
}

bool NormalCell::isBonus() const {
    return false;
}

sf::Color NormalCell::getRenderColor() const {
    return getColor(color, false, 0);
}



