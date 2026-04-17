#include "equation.h"

int Equation::solve(double a, double b, double c, double& x1, double& x2) {
    if (fabs(a) < EPS) return -1;//защита от вырожденного случая линейного уравнения

    double D = b * b - 4 * a * c;

    if (D < -EPS) return 0;

    double denom = 2 * a;

    if (fabs(D) < EPS) {
        x1 = -b / denom;
        x2 = x1;
        return 1;
    }

    x1 = (-b + sqrt(D)) / denom;
    x2 = (-b - sqrt(D)) / denom;

    return 2;
}

bool Equation::check(double a, double b, double c,
    double r1, double r2, int type) {

    double x1 = 0, x2 = 0;
    int correct = solve(a, b, c, x1, x2);

    if (correct != type)
        return false;

    if (correct == 1)
        return fabs(r1 - x1) < 1e-6;

    if (correct == 2)
        return (fabs(r1 - x1) < 1e-6 && fabs(r2 - x2) < 1e-6) ||
        (fabs(r1 - x2) < 1e-6 && fabs(r2 - x1) < 1e-6);

    return (correct == -1 && type == -1);
}



