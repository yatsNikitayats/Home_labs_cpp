#include "BoardGravity.h"
#include "BoardMatchFinder.h"
#include "BonusManager.h"
#include "Utils.h"
#include <iostream>

void BoardGravity::applyGravity(Board& board) {
    const int N = board.getSize();

    for (int j = 0; j < N; j++) {
        int write = N - 1;

        for (int i = N - 1; i >= 0; i--) {
            if (!board.isEmpty(j, i)) {
                board.setCell(j, write, board.getCell(j, i));
                board.setBonus(j, write, board.getBonus(j, i));
                write--;
            }
        }

        while (write >= 0) {
            board.setCell(j, write, rnd(0, 4));
            board.clearBonus(j, write);
            write--;
        }
    }
}



