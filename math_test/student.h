#pragma once
#include <string>
//используется enum
enum StudentType {
    GOOD,
    MID,
    BAD
};

class Student {
private:
    std::string name;
    StudentType type;

public:
    Student(const std::string& n, StudentType t);

    const std::string& getName() const;

    void solve(double a, double b, double c,
        double& root1, double& root2,
        int& solutionType) const;
};