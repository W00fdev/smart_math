#include <iostream>
#include <string>

#include "smart_polynomial/smart_polynomial.h"
#include "smart_functional/smart_functional.h"
#include "smart_functional/smart_functional_additional.h"

using std::cout;
using std::cin;
using std::endl;

// int argc - количество аргументов, поданых в командной строке при запуске программы
// char *argv[] - массив строк этих самых аргументов
// Например, при вводе: "program_name.exe second_arg -thirdArg 3"

// argv[i]:
// 0: program_name.exe
// 1: second_arg
// 2: -thirdArg
// 3: 3

// Точка входа в программу
int main(int argc, char *argv[]) {

    // Ускоряем ввод-вывод. За справкой в "smart_functional.cpp"
    ActivateFastStreams();

    if (argc > 1) {
        // Обработка параметров

        for (int command = 1; command < argc; command++) {
            if (argv[command] == "break") {
                exit(1);
            } else {    // if (argv[command] == "..."

            }

        }
        // Обработка закончена
    }

    // Ввод производится через string в параметрах конструктора

    // Функции-методы объектов изменяют объект, т.е [n1.ADD_NN_N(n2);] == [n1 = ADD_NN_N(n1, n2);]
    // Когда глобальные функции не изменяют объектов.

    cout << "TEST FUNCTIONAL:\n\nNaturals:\n\n";

    Natural n1 {"100"};
    Natural n2 {"55"};
    cout << n1 << " + " << n2 << " = " << n1.ADD_NN_N(n2) << endl;
    cout << n1 << " - " << n2 << " = " << n1.SUB_NN_N(n2) << endl;
    cout << n1 << " * " << n2 << " = " << n1.MUL_NN_N(n2) << endl;
    cout << n1 << " / " << n2 << " = " << n1.DIV_NN_N(n2) << endl;
    cout << n1 << " % " << n2 << " = " << n1.MOD_NN_N(n2) << endl;
    cout << n1 << " gcd " << n2 << " = " << n1.GCF_NN_N(n2) << endl;
    cout << n1 << " lcm " << n2 << " = " << n1.LCM_NN_N(n2) << endl;

    cout << "\n\nIntegral:\n\n";

    Integral i1 {"100"};
    Integral i2 {"-55"};
    cout << i1 << " + " << i2 << " = " << i1.ADD_ZZ_Z(i2) << endl;
    cout << i1 << " - " << i2 << " = " << i1.SUB_ZZ_Z(i2) << endl;
    cout << i1 << " * " << i2 << " = " << i1.MUL_ZZ_Z(i2) << endl;
    cout << i1 << " / " << i2 << " = " << i1.DIV_ZZ_Z(i2) << endl;
    cout << i1 << " % " << i2 << " = " << i1.MOD_ZZ_Z(i2) << endl;

    cout << "\n\nRational:\n\n";


    Rational r1 {"100/3"};
    Rational r2 {"55/2"};
    cout << r1 << " + " << r2 << " = " << r1.ADD_QQ_Q(r2) << endl;
    cout << r1 << " - " << r2 << " = " << r1.SUB_QQ_Q(r2) << endl;
    cout << r1 << " * " << r2 << " = " << r1.MUL_QQ_Q(r2) << endl;
    cout << r1 << " / " << r2 << " = " << r1.DIV_QQ_Q(r2) << endl;

    cout << "\n\nPolynomial:\n\n";


    Polynomial p1 {"100 -10 0 -1"};
    Polynomial p2 {"2 -3"};
    cout << "[" << p1 << "]" << " + " << "[" << p2 << "] = " << p1.ADD_PP_P(p2) << endl;
    cout << "[" << p1 << "]"  << " - " << "[" << p2 << "] = " << p1.SUB_PP_P(p2) << endl;
    cout << "[" << p1 << "]"  << " * " << "[" << p2 << "] = " << p1.MUL_PP_P(p2) << endl;
    cout << "[" << p1 << "]"  << " / " << "[" << p2 << "] = " << p1.DIV_PP_P(p2) << endl;



    return 0;
}