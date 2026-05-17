#pragma once
#include "Bonus.h"

class Board {
public:
    static constexpr int SIZE = 14;

    Board();

    int getCell(int x, int y) const;
    void setCell(int x, int y, int value);
    Bonus getBonus(int x, int y) const;
    void setBonus(int x, int y, const Bonus& b);
    void swapCells(int x1, int y1, int x2, int y2);
    void clearBonus(int x, int y);

    bool isEmpty(int x, int y) const;
    bool hasBonusAt(int x, int y) const;
    int getSize() const;

    int getFieldAt(int x, int y) const { return field[y][x]; }
    int& getFieldAt(int x, int y) { return field[y][x]; }
    Bonus getBonusAt(int x, int y) const { return bonus[y][x]; }
    Bonus& getBonusAt(int x, int y) { return bonus[y][x]; }

private:
    int field[SIZE][SIZE];
    Bonus bonus[SIZE][SIZE];
};

