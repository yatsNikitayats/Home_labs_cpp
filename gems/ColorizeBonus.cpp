#include "ColorizeBonus.h"
#include "Board.h"
#include "Utils.h"
#include "CellFactory.h"
#include <algorithm>

ColorizeBonus::ColorizeBonus(int origin) : originColor(origin) {}

int ColorizeBonus::getColorValue() const {
    return originColor;
}

bool ColorizeBonus::isBonus() const {
    return true;
}

sf::Color ColorizeBonus::getRenderColor() const {
    return sf::Color(0, 200, 255);
}

void ColorizeBonus::activate(Board& board, int x, int y,
    std::vector<DropEffect>& dropEffects) {
    board.setCell(x, y, CellFactory::createNormalCell(originColor));

    std::vector<std::pair<int, int>> nonAdj;
    for (int dy = -3; dy <= 3; ++dy) {
        for (int dx = -3; dx <= 3; ++dx) {
            int nx = x + dx, ny = y + dy;
            if (!inBounds(nx, ny, Board::SIZE)) continue;
            if (manhattan(x, y, nx, ny) > 3) continue;
            if (manhattan(x, y, nx, ny) <= 1) continue;
            if (board.isEmpty(nx, ny)) continue;
            nonAdj.push_back({ nx, ny });
        }
    }

    std::shuffle(nonAdj.begin(), nonAdj.end(), gen);

    std::vector<std::pair<int, int>> selected;
    for (auto [tx, ty] : nonAdj) {
        bool ok = true;
        for (auto [sx, sy] : selected) {
            if (manhattan(tx, ty, sx, sy) <= 1) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;
        selected.push_back({ tx, ty });
        if (selected.size() >= 2) break;
    }

    for (auto [tx, ty] : selected) {
        board.setCell(tx, ty, CellFactory::createNormalCell(originColor));
    }
}



