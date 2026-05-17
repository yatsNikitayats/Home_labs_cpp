#include "Utils.h"
#include <random>

std::mt19937 gen(std::random_device{}());

int rnd(int l, int r) {
    std::uniform_int_distribution<int> dist(l, r);
    return dist(gen);
}

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool inBounds(int x, int y, int N) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

sf::Color getColor(int v, bool hasBonus, int bonusType) {
    if (v == -1) return sf::Color(30, 30, 30);

    sf::Color base;
    switch (v) {
    case 0: base = sf::Color::Red; break;
    case 1: base = sf::Color::Green; break;
    case 2: base = sf::Color::Blue; break;
    case 3: base = sf::Color::Yellow; break;
    case 4: base = sf::Color::Magenta; break;
    default: base = sf::Color::White;
    }

    if (hasBonus) {
        if (bonusType == 1) return sf::Color(0, 200, 255);
        if (bonusType == 2) return sf::Color(50, 50, 50);
    }
    return base;
}

