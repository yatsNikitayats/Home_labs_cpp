#include "BombBonus.h"
#include "Board.h"
#include "Utils.h"
#include <algorithm>

BombBonus::BombBonus(int origin) : originColor(origin) {}

int BombBonus::getColorValue() const {
    return -1;
}

bool BombBonus::isBonus() const {
    return true;
}

sf::Color BombBonus::getRenderColor() const {
    return sf::Color(50, 50, 50);
}

void BombBonus::activate(Board& board, int x, int y,
    std::vector<DropEffect>& dropEffects) {

    board.clearCell(x, y);

    std::vector<std::pair<int, int>> all;
    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            if (!board.isEmpty(j, i)) {
                all.push_back({ j, i });
            }
        }
    }

    std::shuffle(all.begin(), all.end(), gen);

    int destroyed = 0;
    for (auto [tx, ty] : all) {
        if (destroyed >= 4) break;
        board.clearCell(tx, ty);
        destroyed++;
    }
}



