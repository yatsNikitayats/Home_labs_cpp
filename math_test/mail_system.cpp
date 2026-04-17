#include "mail_system.h"
#include <iostream>
#include <fstream>

int MailSystem::loadEquations(const std::string& filename,
    double eq[][3],
    int maxCount) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        return -1;
    }

    int count = 0;

    while (count < maxCount &&
        file >> eq[count][0] >> eq[count][1] >> eq[count][2]) {
        count++;
    }

    return count;
}

void MailQueue::push(double a, double b, double c,
    double root1, double root2,
    int solutionType, const std::string& name) {

    Mail m;
    m.a = a;
    m.b = b;
    m.c = c;
    m.root1 = root1;
    m.root2 = root2;
    m.solutionType = solutionType;
    m.studentName = name;

    q.push(m);
}

Mail MailQueue::pop() {
    Mail m = q.front();
    q.pop();
    return m;
}

bool MailQueue::empty() const {
    return q.empty();
}



ResultsTable::~ResultsTable() {
    while (head) {
        Result* t = head;
        head = head->next;
        delete t;
    }
}

void ResultsTable::add(const std::string& name, bool correct) {
    if (!correct) return;

    Result* cur = head;

    while (cur) {
        if (cur->name == name) {
            cur->solved++;
            return;
        }
        cur = cur->next;
    }

    head = new Result{ name, 1, head };
}

void ResultsTable::print() const {
    std::cout << "\n=== Итоги зачетной недели ===\n";

    Result* cur = head;
    while (cur) {
        std::cout << cur->name;

        for (size_t i = cur->name.length(); i < 20; i++)
            std::cout << " ";

        std::cout << "| " << cur->solved << "\n";
        cur = cur->next;
    }
}