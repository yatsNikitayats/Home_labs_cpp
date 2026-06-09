#pragma once
#include "Cell.h"

class NormalCell : public Cell {
    int color;
public:
    NormalCell(int col);
    int getColorValue() const override;
    bool isBonus() const override;
    sf::Color getRenderColor() const override;
};



