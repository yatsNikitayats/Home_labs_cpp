#include "CellFactory.h"
#include "NormalCell.h"
#include "ColorizeBonus.h"
#include "BombBonus.h"

std::unique_ptr<Cell> CellFactory::createNormalCell(int color) {
    return std::make_unique<NormalCell>(color);
}

std::unique_ptr<Cell> CellFactory::createBonus(BonusType type, int originColor) {
    switch (type) {
    case BonusType::COLORIZE:
        return std::make_unique<ColorizeBonus>(originColor);
    case BonusType::BOMB:
        return std::make_unique<BombBonus>(originColor);
    default:
        return nullptr;
    }
}





