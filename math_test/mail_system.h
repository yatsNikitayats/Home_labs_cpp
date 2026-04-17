#pragma once
#include <string>
#include <queue>
//все методы внутри классов
struct Mail {
    double a, b, c;
    double root1, root2;
    int solutionType;
    std::string studentName;
};

struct Result {
    std::string name;
    int solved;
    Result* next;
};

class MailSystem {
public:
    static int loadEquations(const std::string& filename,
        double eq[][3],
        int maxCount);
};

class MailQueue {
private:
    std::queue<Mail> q; // используется std::queue

public:
    void push(double a, double b, double c,
        double root1, double root2,
        int solutionType, const std::string& name);

    Mail pop();
    bool empty() const;
};

class ResultsTable {
private:
    Result* head = nullptr;

public:
    ~ResultsTable();

    void add(const std::string& name, bool correct);
    void print() const;
};
