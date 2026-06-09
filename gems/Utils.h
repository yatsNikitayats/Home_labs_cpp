#pragma once
#include <SFML/Graphics.hpp>
#include <random>

extern std::mt19937 gen;

int rnd(int l, int r);
int manhattan(int x1, int y1, int x2, int y2);
bool inBounds(int x, int y, int N);
sf::Color getColor(int v, bool hasBonus = false, int bonusType = 0);



