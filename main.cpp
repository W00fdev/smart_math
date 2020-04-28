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
int main() {

    // Ускоряем ввод-вывод. За справкой в "smart_functional.cpp"
    ActivateFastStreams();

    int n;
    cout << "Выберите тип данных с которыми будете работать.\n";
    cout << "1. Натуральные.\n2. Целые.\n3. Рациональные.\n4. Полиномы.\n";
    do {
        cin >> n;
    } while ((n < 1) && (n > 4));
    if (n == 1) {
        cout << "Введите желаемую команду:\n";
        cout << "1. Сравнение натуральных чисел. Вывод: 2 - если первое больше второго, 0, если равно, 1 иначе.\n";
        cout << "2. Проверка на ноль: если число не равно нулю, то «true» иначе «false».\n";
        cout << "3. Добавление 1 к натуральному числу.\n";
        cout << "4. Сложение натуральных чисел.\n";
        cout << "5. Вычитание из первого большего натурального числа второго меньшего или равного.\n";
        cout << "6. Умножение натурального числа на цифру.\n";
        cout << "7. Умножение натурального числа на 10^k.\n";
        cout << "8. Умножение натуральных чисел.\n";
        cout << "9. Вычитание из натурального другого натурального, умноженного на цифру для случая с неотрицательным результатом.\n";
        cout << "10. Вычисление первой цифры деления большего натурального на меньшее, домноженное на 10^k,где k - номер позиции этой цифры (номер считается с нуля).\n";
        cout << "11. Частное от деления большего натурального числа на меньшее или равное натуральное с остатком(делитель отличен от нуля).\n";
        cout << "12. Остаток от деления большего натурального числа на меньшее или равное натуральное с остатком(делитель отличен от нуля).\n";
        cout << "13. НОД.\n";
        cout << "14. НОК.\n";
        cin >> n;
        if (n == 1) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << COMM_NN_D(n1, n2);
        }
        if (n == 2) {
            cout << "Введите натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << n1.NZER_N_B();
        }
        if (n == 3) {
            cout << "Введите натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << n1.ADD_1N_N();
        }
        if (n == 4) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << ADD_NN_N(n1, n2);
        }
        if (n == 5) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << SUB_NN_N(n1, n2);
        }
        if (n == 6) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите цифру.\n";
            int d;
            cin >> d;
            cout << n1.MUL_ND_N(d);
        }
        if (n == 7) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите степень k.\n";
            uint64_t k;
            cin >> k;
            cout << n1.MUL_Nk_N(k);
        }
        if (n == 8) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << MUL_NN_N(n1, n2);
        }
        if (n == 9) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << "Введите цифру.\n";
            int d;
            cin >> d;
            cout << n1.SUB_NDN_N(n2, d);
        }
        if (n == 10) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << "Введите степень k.\n";
            uint64_t k;
            cin >> k;
            cout << n1.DIV_NN_Dk(n2, k);
        }
        if (n == 11) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << DIV_NN_N(n1,n2);
        }
        if (n == 12) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << MOD_NN_N(n1, n2);
        }
        if (n == 13) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << GCF_NN_N(n1, n2);
        }
        if (n == 14) {
            cout << "Введите 1-ое натуральное число.\n";
            Natural n1;
            cin >> n1;
            cout << "Введите 2-ое натуральное число.\n";
            Natural n2;
            cin >> n2;
            cout << LCM_NN_N(n1, n2);
        }
    }
    if (n == 2) {
        cout << "Введите желаемую команду:\n";
        cout << "1. Абсолютная величина числа, результат - натуральное.\n";
        cout << "2. Определение положительности числа, вывод: 2 - положительное, 0 — равное нулю, 1 - отрицательное.\n";
        cout << "3. Умножение целого на (-1).\n";
        cout << "4. Преобразование натурального в целое.\n";
        cout << "5. Преобразование целого неотрицательного в натуральное.\n";
        cout << "6. Сложение целых чисел.\n";
        cout << "7. Вычитание целых чисел.\n";
        cout << "8. Умножение целых чисел.\n";
        cout << "9. Частное от деления большего целого числа на меньшее или равное натуральное с остатком(делитель отличен от нуля).\n";
        cout << "10. Остаток от деления большего целого числа на меньшее или равное натуральное с остатком(делитель отличен от нуля).\n";
        cin >> n;
        if (n == 1) {
            Integral z;
            cout << "Введите целое число.\n";
            cin >> z;
            cout << ABS_Z_N(z);
        }
        if (n == 2) {
            Integral z;
            cout << "Введите целое число.\n";
            cin >> z;
            cout << z.POZ_Z_D();
        }
        if (n == 3) {
            Integral z;
            cout << "Введите целое число.\n";
            cin >> z;
            cout << z.MUL_ZM_Z();
        }
        if (n == 4) {
            Natural z;
            cout << "Введите натуральное число.\n";
            cin >> z;
            cout << TRANS_N_Z(z);
        }
        if (n == 5) {
            Integral z;
            cout << "Введите целое число.\n";
            cin >> z;
            cout << TRANS_Z_N(z);
        }
        if (n == 6) {
            Integral z1;
            Integral z2;
            cout << "Введите 1-ое число.\n";
            cin >> z1;
            cout << "Введите 2-ое число.\n";
            cin >> z2;
            cout << ADD_ZZ_Z(z1, z2);
        }
        if (n == 7) {
            Integral z1;
            Integral z2;
            cout << "Введите 1-ое число.\n";
            cin >> z1;
            cout << "Введите 2-ое число.\n";
            cin >> z2;
            cout << SUB_ZZ_Z(z1, z2);
        }
        if (n == 8) {
            Integral z1;
            Integral z2;
            cout << "Введите 1-ое число.\n";
            cin >> z1;
            cout << "Введите 2-ое число.\n";
            cin >> z2;
            cout << MUL_ZZ_Z(z1, z2);
        }
        if (n == 9) {
            Integral z1;
            Integral z2;
            cout << "Введите 1-ое число.\n";
            cin >> z1;
            cout << "Введите 2-ое число.\n";
            cin >> z2;
            cout << DIV_ZZ_Z(z1, z2);
        }
        if (n == 10) {
            Integral z1;
            Integral z2;
            cout << "Введите 1-ое число.\n";
            cin >> z1;
            cout << "Введите 2-ое число.\n";
            cin >> z2;
            cout << MOD_ZZ_Z(z1, z2);
        }
    }
    if (n == 3) {
        cout << "Введите желаемую команду:\n";
        cout << "1. Сокращение дроби.\n";
        cout << "2. Проверка на целое, если рациональное число является целым, то «true», иначе «false».\n";
        cout << "3. Преобразование целого в дробное.\n";
        cout << "4. Преобразование рационального в целое с округлением деления.\n";
        cout << "5. Сложение дробей.\n";
        cout << "6. Вычитание дробей.\n";
        cout << "7. Умножение дробей.\n";
        cout << "8. Деление дробей (делитель отличен от нуля).\n";
        cout << "9. Дополнительный метод, переворачивающий дробь.\n";
        cout << "10. Дополнительный метод, переворачивающий дробь.\n";
        cin >> n;
        if (n == 1) {
            Rational q;
            cout << "Введите рациональное число.\n";
            cin >> q;
            cout << RED_Q_Q(q);
        }
        if (n == 2) {
            Rational q;
            cout << "Введите рациональное число.\n";
            cin >> q;
            cout << INT_Q_B(q);
        }
        if (n == 3) {
            Integral q;
            cout << "Введите целое число.\n";
            cin >> q;
            cout << TRANS_Z_Q(q);
        }
        if (n == 4) {
            Rational q;
            cout << "Введите рациональное число.\n";
            cin >> q;
            cout << TRANS_Q_Z(q);
        }
        if (n == 5) {
            Rational q;
            Rational q2;
            cout << "Введите 1-ое рациональное число.\n";
            cin >> q;
            cout << "Введите 2-ое рациональное число.\n";
            cin >> q2;
            cout << ADD_QQ_Q(q, q2);
        }
        if (n == 6) {
            Rational q;
            Rational q2;
            cout << "Введите 1-ое рациональное число.\n";
            cin >> q;
            cout << "Введите 2-ое рациональное число.\n";
            cin >> q2;
            cout << SUB_QQ_Q(q, q2);
        }
        if (n == 7) {
            Rational q;
            Rational q2;
            cout << "Введите 1-ое рациональное число.\n";
            cin >> q;
            cout << "Введите 2-ое рациональное число.\n";
            cin >> q2;
            cout << MUL_QQ_Q(q, q2);
        }
        if (n == 8) {
            Rational q;
            Rational q2;
            cout << "Введите 1-ое рациональное число.\n";
            cin >> q;
            cout << "Введите 2-ое рациональное число.\n";
            cin >> q2;
            cout << DIV_QQ_Q(q, q2);
        }
        if (n == 9) {
            Rational q;
            cout << "Введите рациональное число.\n";
            cin >> q;
            cout << INVERT_Q(q);
        }
    }
    if (n == 4) {
        cout << "Введите желаемую команду:\n";
        cout << "1. Домножение полинома на -1.\n";
        cout << "2. Проверка на ноль многочлена.\n";
        cout << "3. Сложение полиномов.\n";
        cout << "4. Вычитание полиномов.\n";
        cout << "5. Умножение многочлена на рациональное число.\n";
        cout << "6. Домножение многочлена на x^k.\n";
        cout << "7. Получение коэффициента старшего монома.\n";
        cout << "8. Получение степени многочлена.\n";
        cout << "9. Вынесение дроби НОД/НОК из многочлена.\n";
        cout << "10. Перемножение многочленов.\n";
        cout << "11. Частное от деления многочлена на многочлен при делении с остатком.\n";
        cout << "12. Остаток от деления многочлена на многочлен при делении с остатком.\n";
        cout << "13. Взятие НОД многочленов.\n";
        cout << "14. Производная многочлена.\n";
        cout << "15. Преобразование многочлена — кратные корни в простые.\n";
        cin >> n;
        if (n == 1) {
            Polynomial p;
            cout << "Введите полином.\n";
            cin >> p;
            cout << p.MUL_ZM_P();
        }
        if (n == 2) {
            Polynomial p;
            cout << "Введите полином.\n";
            cin >> p;
            cout << p.NZER_P_B();
        }
        if (n == 3) {
            Polynomial p, p2;
            cout << "Введите 1-ый полином.\n";
            cin >> p;
            cout << "Введите 2-ой полином.\n";
            cin >> p2;
            cout << ADD_PP_P(p, p2);
        }
        if (n == 4) {
            Polynomial p, p2;
            cout << "Введите 1-ый полином.\n";
            cin >> p;
            cout << "Введите 2-ой полином.\n";
            cin >> p2;
            cout << SUB_PP_P(p, p2);
        }
        if (n == 5) {
            Polynomial p;
            Rational q;
            cout << "Введите полином.\n";
            cin >> p;
            cout << "Введите рациональное число.\n";
            cin >> q;
            cout << MUL_PQ_P(p, q);
        }
        if (n == 6) {
            Polynomial p;
            uint64_t k;
            cout << "Введите полином.\n";
            cin >> p;
            cout << "Введите степень k.\n";
            cin >> k;
            cout << MUL_Pxk_P(p, k);
        }
        if (n == 7) {
            Polynomial p;
            cout << "Введите полином.\n";
            cin >> p;
            cout << p.LED_P_Q();
        }
        if (n == 8) {
            Polynomial p, p2;
            cout << "Введите полином.\n";
            cin >> p;
            cout << p.DEG_P_N();
        }
        if (n == 9) {
            Polynomial p, p2;
            cout << "Введите полином.\n";
            cin >> p;
            cout << p.FAC_P_Q();
        }
        if (n == 10) {
            Polynomial p, p2;
            cout << "Введите 1-ый полином.\n";
            cin >> p;
            cout << "Введите 2-ой полином.\n";
            cin >> p2;
            cout << p.MUL_PP_P(p2);
        }
        if (n == 11) {
            Polynomial p, p2;
            cout << "Введите 1-ый полином.\n";
            cin >> p;
            cout << "Введите 2-ой полином.\n";
            cin >> p2;
            cout << p.DIV_PP_P(p2);
        }
        if (n == 12) {
            Polynomial p, p2;
            cout << "Введите 1-ый полином.\n";
            cin >> p;
            cout << "Введите 2-ой полином.\n";
            cin >> p2;
            cout << p.MOD_PP_P(p2);
        }
        if (n == 13) {
            Polynomial p, p2;
            cout << "Введите 1-ый полином.\n";
            cin >> p;
            cout << "Введите 2-ой полином.\n";
            cin >> p2;
            cout << p.GCF_PP_P(p2);
        }
        if (n == 14) {
            Polynomial p, p2;
            cout << "Введите полином.\n";
            cin >> p;
            cout << p.DER_PP_P();
        }
        if (n == 15) {
            Polynomial p, p2;
            cout << "Введите полином.\n";
            cin >> p;
            cout << p.NMR_P_P();
        }
    }

    // Ввод производится через string в параметрах конструктора

    // Функции-методы объектов изменяют объект, т.е [n1.ADD_NN_N(n2);] == [n1 = ADD_NN_N(n1, n2);]
    // Когда глобальные функции не изменяют объектов.


    Natural n1 {"600"};
    Natural n2 {"550"};

    n1 = n1 * n2;
    cout << n1 << " + " << n2 << " = " << n1.ADD_NN_N(n2) << endl;
    cout << n1 << " - " << n2 << " = " << n1.SUB_NN_N(n2) << endl;
    cout << n1 << " * " << n2 << " = " << n1*n2 << endl;
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




    Polynomial p1 {"-10x^4 20x^10 5/10x^8 -1"};
    Polynomial p2 {"2x^3 -3x -3"};

    cout << "[" << p1 << "]" << " + " << "[" << p2 << "] = " << p1.ADD_PP_P(p2) << endl;
    cout << "[" << p1 << "]"  << " - " << "[" << p2 << "] = " << p1.SUB_PP_P(p2) << endl;
    cout << "[" << p1 << "]"  << " * " << "[" << p2 << "] = " << p1.MUL_PP_P(p2) << endl;
    cout << "[" << p1 << "]"  << " / " << "[" << p2 << "] = " << p1.DIV_PP_P(p2) << endl;
    cout << "[" << p1 << "]"  << "' = " << p1.DER_PP_P() << endl;




    return 0;
}