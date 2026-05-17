#include "Board.h"
#include "Utils.h"

Board::Board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = -1;
            bonus[i][j].type = BonusType::NONE;
            bonus[i][j].originColor = -1;
        }
    }
}

int Board::getCell(int x, int y) const {
    return field[y][x];
}

void Board::setCell(int x, int y, int value) {
    field[y][x] = value;
}

Bonus Board::getBonus(int x, int y) const {
    return bonus[y][x];
}

void Board::setBonus(int x, int y, const Bonus& b) {
    bonus[y][x] = b;
}

void Board::swapCells(int x1, int y1, int x2, int y2) {
    std::swap(field[y1][x1], field[y2][x2]);
    std::swap(bonus[y1][x1], bonus[y2][x2]);
}

void Board::clearBonus(int x, int y) {
    bonus[y][x].type = BonusType::NONE;
    bonus[y][x].originColor = -1;
}

bool Board::isEmpty(int x, int y) const {
    return field[y][x] == -1;
}

bool Board::hasBonusAt(int x, int y) const {
    return bonus[y][x].type != BonusType::NONE;
}

int Board::getSize() const {
    return SIZE;
}

