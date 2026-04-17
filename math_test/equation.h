#pragma once
#include <cmath>
//все методы внутри класса
class Equation {
private:
    static constexpr double EPS = 1e-6;

public:
    static int solve(double a, double b, double c, double& x1, double& x2);

    static bool check(double a, double b, double c,
        double r1, double r2, int type);
};
