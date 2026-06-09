#pragma once
#include <memory>
#include "Bonus.h"

class Cell;

class CellFactory {
public:
    static std::unique_ptr<Cell> createNormalCell(int color);
    static std::unique_ptr<Cell> createBonus(BonusType type, int originColor);
};



