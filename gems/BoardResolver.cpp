#include "BoardResolver.h"
#include "BoardGravity.h"
#include "BoardMatchFinder.h"
#include "CellFactory.h"
#include "Utils.h"
#include <iostream>

namespace {
    constexpr int MAX_BONUSES_PER_RESOLVE = 2;
    constexpr int BONUS_SPAWN_CHANCE_PERCENT = 8;
    constexpr int MAX_STABILIZE_ITERATIONS = 100;
}

bool BoardResolver::resolveBoard(Board& board,
    std::vector<DropEffect>& dropEffects,
    bool allowBonusSpawn) {
    auto matches = BoardMatchFinder::findAllMatches(board);
    if (matches.empty()) return false;

    bool toDelete[Board::SIZE][Board::SIZE] = {};
    for (auto& match : matches) {
        for (auto [x, y] : match.cells) {
            toDelete[y][x] = true;
        }
    }

    int spawnedBonuses = 0;

    if (allowBonusSpawn) {
        for (auto& match : matches) {
            if (spawnedBonuses >= MAX_BONUSES_PER_RESOLVE) break;
            if (rnd(1, 100) <= BONUS_SPAWN_CHANCE_PERCENT) {
                auto [cx, cy] = match.cells[rnd(0, match.cells.size() - 1)];

                std::vector<std::pair<int, int>> spawnPoints;
                for (int dy = -3; dy <= 3; dy++) {
                    for (int dx = -3; dx <= 3; dx++) {
                        int nx = cx + dx, ny = cy + dy;
                        if (!inBounds(nx, ny, Board::SIZE)) continue;
                        if (manhattan(cx, cy, nx, ny) > 3) continue;
                        if (toDelete[ny][nx]) continue;
                        if (board.isEmpty(nx, ny)) continue;
                        if (board.hasBonusAt(nx, ny)) continue;
                        spawnPoints.push_back({ nx, ny });
                    }
                }

                if (!spawnPoints.empty()) {
                    auto [bx, by] = spawnPoints[rnd(0, spawnPoints.size() - 1)];
                    BonusType newType = (rnd(0, 1) == 0) ? BonusType::COLORIZE : BonusType::BOMB;
                    auto bonusCell = CellFactory::createBonus(newType, match.color);
                    board.setCell(bx, by, std::move(bonusCell));
                    dropEffects.push_back({
                        bx * 64.0f + 32.0f,
                        by * 64.0f + 32.0f,
                        1.2f,
                        newType
                        });
                    spawnedBonuses++;
                }
            }
        }
    }

    
    std::vector<std::tuple<int, int, std::unique_ptr<Cell>>> bonusesToActivate;

    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            Cell* cell = board.getCell(j, i);
            if (cell && cell->isBonus()) {
                auto bonusPtr = board.releaseCell(j, i);
                bonusesToActivate.emplace_back(j, i, std::move(bonusPtr));
            }
        }
    }

    for (auto& [x, y, bonusPtr] : bonusesToActivate) {
        if (bonusPtr) {
            bonusPtr->activate(board, x, y, dropEffects);
        }
    }

    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            if (toDelete[i][j]) {
                board.clearCell(j, i);
            }
        }
    }

    BoardGravity::applyGravity(board);
    return true;
}

void BoardResolver::stabilize(Board& board, std::vector<DropEffect>& dropEffects) {
    int iterations = 0;
    while (resolveBoard(board, dropEffects, false)) {
        if (++iterations >= MAX_STABILIZE_ITERATIONS) {
            std::cerr << "Warning: stabilize reached max iterations\n";
            break;
        }
    }
}





