#pragma once
#include "Cell.h"
#include "Bonus.h"

class BombBonus : public Cell {
    int originColor; 
public:
    BombBonus(int originColor);
    int getColorValue() const override;
    bool isBonus() const override;
    sf::Color getRenderColor() const override;
    void activate(Board& board, int x, int y,
        std::vector<DropEffect>& dropEffects) override;
};



