#include <iostream>
#include <ctime>
#include <cstdlib>
#include <locale>
#include "mail_system.h"
#include "student.h"
#include "equation.h"

int main() {
    srand((unsigned)time(nullptr));//вызывается srand(time)

    setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));

    const int MAX_EQUATIONS = 100;
    double equations[MAX_EQUATIONS][3];

    int eqCount = MailSystem::loadEquations(
        "data/equations.txt",
        equations,
        MAX_EQUATIONS
    );

    if (eqCount <= 0) {
        std::cout << "Ошибка или пустой файл\n";
        return 1;
    }

    Student students[] = {
        {"Яцишин", GOOD},
        {"Куликова", MID},
        {"Хаймин", BAD},
        {"Славгородский", MID},
        {"Фролов", GOOD}
    };

    int studentCount = sizeof(students) / sizeof(students[0]);

    MailQueue queue;

    for (int i = 0; i < eqCount; i++) {

        double a = equations[i][0];
        double b = equations[i][1];
        double c = equations[i][2];

        for (int j = 0; j < studentCount; j++) {

            double r1 = 0, r2 = 0;
            int type = 0;

            students[j].solve(a, b, c, r1, r2, type);

            queue.push(
                a, b, c,
                r1, r2,
                type,
                students[j].getName()
            );
        }
    }

    ResultsTable results;

    while (!queue.empty()) {

        Mail m = queue.pop();

        bool correct = Equation::check(
            m.a, m.b, m.c,
            m.root1, m.root2,
            m.solutionType
        );

        results.add(m.studentName, correct);
    }

    results.print();

    return 0;
}