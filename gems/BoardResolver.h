#pragma once
#include "Board.h"
#include "Bonus.h"
#include <vector>

class BoardResolver {
public:
    static bool resolveBoard(
        Board& board,
        std::vector<DropEffect>& dropEffects,
        bool allowBonusSpawn
    );

    static void stabilize(Board& board,
        std::vector<DropEffect>& dropEffects);
};





