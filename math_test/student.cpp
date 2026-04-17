#include "student.h"
#include "equation.h"
#include <cstdlib>

Student::Student(const std::string& n, StudentType t)
    : name(n), type(t) {
}

const std::string& Student::getName() const {
    return name;
}

//нет отдельной функции makeWrongAnswer
void Student::solve(double a, double b, double c,
    double& root1, double& root2,
    int& solutionType) const {

    if (type == GOOD) {
        solutionType = Equation::solve(a, b, c, root1, root2);

        if (solutionType == -1)
            root1 = root2 = 0;
    }
    else if (type == MID) {
        if (rand() % 2 == 0) {
            solutionType = Equation::solve(a, b, c, root1, root2);

            if (solutionType == -1)
                root1 = root2 = 0;
        }
        else {
            solutionType = 1;
            root1 = root2 = 0;
        }
    }
    else {
        solutionType = 1;
        root1 = root2 = 0;
    }
}
