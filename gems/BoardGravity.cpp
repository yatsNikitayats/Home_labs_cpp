#include "BoardGravity.h"
#include "CellFactory.h"
#include "Utils.h"
#include <iostream>

void BoardGravity::applyGravity(Board& board) {
    const int N = board.getSize();

    for (int j = 0; j < N; j++) {
        int write = N - 1;

        for (int i = N - 1; i >= 0; i--) {
            if (!board.isEmpty(j, i)) {
                 
                if (write != i) {
                    
                    auto cell = board.releaseCell(j, i); 
                    board.setCell(j, write, std::move(cell)); 
                }
                write--;
            }
        }

        
        while (write >= 0) {
            int newColor = rnd(0, 4);
            board.setCell(j, write, CellFactory::createNormalCell(newColor));
            write--;
        }
    }
}



