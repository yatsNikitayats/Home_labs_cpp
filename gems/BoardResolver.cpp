#include "BoardResolver.h"

#include "BoardGravity.h"
#include "BoardMatchFinder.h"
#include "BonusManager.h"
#include "Utils.h"

#include <iostream>

bool BoardResolver::resolveBoard(
    Board& board,
    std::vector<DropEffect>& dropEffects,
    bool allowBonusSpawn) {
    auto matches = BoardMatchFinder::findAllMatches(board);

    int spawnedBonuses = 0;
    const int MAX_BONUSES_PER_RESOLVE = 2;

    if (matches.empty()) return false;

    bool toDelete[Board::SIZE][Board::SIZE] = {};

    for (auto& match : matches) {
        for (auto [x, y] : match.cells) {
            toDelete[y][x] = true;
        }
    }

    if (allowBonusSpawn) {
        for (auto& match : matches) {

            if (spawnedBonuses >= MAX_BONUSES_PER_RESOLVE)
                break;

            if (rnd(1, 100) <= 8) {
                auto [cx, cy] = match.cells[rnd(0, match.cells.size() - 1)];
                if (BonusManager::trySpawnBonus(
                    board,
                    cx,
                    cy,
                    match.color,
                    toDelete,
                    dropEffects))
                {
                    spawnedBonuses++;
                }
            }
        }
    }

    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            if (board.hasBonusAt(j, i)) {
                BonusManager::activateBonus(board, j, i, dropEffects);
            }
        }
    }


    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            if (toDelete[i][j]) {
                board.setCell(j, i, -1);
                board.clearBonus(j, i);
            }
        }
    }

    BoardGravity::applyGravity(board);
    return true;
}

void BoardResolver::stabilize(Board& board, std::vector<DropEffect>& dropEffects) {
    const int MAX_ITERATIONS = 100;
    int iterations = 0;

    while (resolveBoard(
        board,
        dropEffects,
        false)) {
        if (++iterations >= MAX_ITERATIONS) {
            std::cerr << "Warning: stabilize reached max iterations\n";
            break;
        }
    }
}

