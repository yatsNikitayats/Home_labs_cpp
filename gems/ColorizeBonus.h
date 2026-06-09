#pragma once
#include "Cell.h"
#include "Bonus.h"

class ColorizeBonus : public Cell {
    int originColor;
public:
    ColorizeBonus(int originColor);
    int getColorValue() const override;
    bool isBonus() const override;
    sf::Color getRenderColor() const override;
    void activate(Board& board, int x, int y,
        std::vector<DropEffect>& dropEffects) override;
};



