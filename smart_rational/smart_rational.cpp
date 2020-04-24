#include "smart_rational.h"

/*
    Реализация методов класса Rational.
    Дополнительные методы: ...
*/

/*  [XQ - 1]
    Куликов Дмитрий
    Дополнительный метод, переворачивающий дробь.
*/

Rational& Rational::INVERT_Q() {
    bool final_minus = numerator.getMinus();

    *this = Rational(
            Integral(denominator.getRawOdds(), denominator.getRawDeg(), final_minus),
            numerator.ABS_Z_N()
            );

    return *this;
}

/*  [XQ - 2]
    Куликов Дмитрий
    Дополнительный метод, переворачивающий дробь.
*/

Rational& Rational::MUL_ZM_Q() {
    numerator.MUL_ZM_Z();
    return *this;
}


/*  [Q - 1]
    Ковтун Александр
    Сокращаем дробь. Поделим обе части дроби на НОД.
*/

Rational& Rational::RED_Q_Q() {
    // НОД через натуральные.
    if (numerator == Integral{0}) {
        MakeNull();
        return *this;
    }

    Integral NOD = Integral(Natural(denominator).GCF_NN_N(numerator.ABS_Z_N()));

    numerator.DIV_ZZ_Z(NOD);
    denominator.DIV_NN_N(NOD.ABS_Z_N());

    return *this;   // Изменили исходный объект
}

/*  [Q - 2]
    Ковтун Александр
    Проверка на целое. Число целое? Тогда true
    Ссылки на документацию, использованную при разработке.
*/
// опять же, оператор= к рациональному.
bool Rational::INT_Q_B() const {
    Rational reduced_copy(*this);
    reduced_copy.RED_Q_Q();

    return reduced_copy.getDenominator() == Natural{"1"} != 0;
}

/*  [Q - 3]
    Бабкин Иван
    Преобразование целого в рациональное.
    Значение сохраняем в числителе, а знаменатель = 1
*/

Rational Rational::TRANS_Z_Q(const Integral& i) const {
    return Rational(i, Natural{1});
}

/*  [Q - 4]
    Бабкин Иван
    Преобразование Рационального в целое с округлением деления
*/

Integral Rational::TRANS_Q_Z(const Rational& n) const {
    Rational a(n.numerator, n.denominator);
    a.RED_Q_Q();
    if (a.INT_Q_B())
        return Integral(a.numerator.getRawOdds(), a.numerator.getRawDeg(), a.numerator.getMinus());

    Integral i_numerator = a.getNumerator();
    Integral i_denominator = i_numerator.TRANS_N_Z(a.getDenominator());
    return i_numerator.DIV_ZZ_Z(i_denominator);
}

/*  [Q - 5]
    Ширнин Кирилл
    Сложение двух рациональных чисел
    Ссылки на документацию, использованную при разработке.
*/

Rational& Rational::ADD_QQ_Q(const Rational& r) {
    Integral copy_numerator = numerator;

    Natural lcm_denoms = LCM_NN_N(denominator, r.getDenominator()); // НОК дробей

    Integral left_koeff_num = Integral(DIV_NN_N(lcm_denoms, denominator)); // домножение левого числителя на коэффициент
    Integral right_koeff_num = Integral(DIV_NN_N(lcm_denoms, r.getDenominator())); // домножение правого числителя на коэффициент

    numerator = ADD_ZZ_Z(MUL_ZZ_Z(numerator, left_koeff_num), MUL_ZZ_Z(r.getNumerator(), right_koeff_num));
    denominator = lcm_denoms;
    RED_Q_Q();  // сократим результат

    return *this;
}

/*  [Q - 6]
    Ширнин Кирилл
    Вычитание дробей реализуем как сложение двух дробей, где у второй изменён знак
*/

Rational& Rational::SUB_QQ_Q(const Rational& r) {
    Rational r_copy_inversed = Rational(r.getNumerator().MUL_ZM_Z(), r.getDenominator());
    ADD_QQ_Q(r_copy_inversed);
    return *this;
}

/*  [Q - 7]
    Ширнин Кирилл
    Умножение дробей. Умножим числители, знаменатели, сократим.
*/

Rational& Rational::MUL_QQ_Q(const Rational& r) {
    // проверка на ноль
    numerator.MUL_ZZ_Z(r.getNumerator());
    denominator.MUL_NN_N(r.getDenominator());
    RED_Q_Q();
    return *this;
}

/*  [Q - 8]
    Ширнир Кирилл
    Деление дробей. Умножим, перевернув правую дробь.
    Для этого создана специальная функция Invert().
*/
Rational& Rational::DIV_QQ_Q(const Rational& r) {
    Rational inverted_r = r;
    inverted_r.INVERT_Q();
    MUL_QQ_Q(inverted_r);

    return *this;
}


// <! ---------- Friend функционал ---------- !> //

Rational INVERT_Q(const Rational& r) {
    Rational const_disqualification(r);
    return const_disqualification.INVERT_Q();
}

Rational RED_Q_Q(const Rational& r) {
    Rational const_disqualification(r);
    return const_disqualification.RED_Q_Q();
}

bool INT_Q_B(const Rational& r) {
    return r.INT_Q_B();
}

Rational TRANS_Z_Q(const Integral& i) {
    Rational r;
    return r.TRANS_Z_Q(i);
}

Integral TRANS_Q_Z(const Rational& n) {
    return n.TRANS_Q_Z(n);
}

Rational ADD_QQ_Q(const Rational& r1, const Rational& r2) {
    Rational const_disqualification(r1);
    return const_disqualification.ADD_QQ_Q(r2);
}

Rational SUB_QQ_Q(const Rational& r1, const Rational& r2) {
    Rational const_disqualification(r1);
    return const_disqualification.SUB_QQ_Q(r2);
}

Rational MUL_QQ_Q(const Rational& r1, const Rational& r2) {
    Rational const_disqualification(r1);
    return const_disqualification.MUL_QQ_Q(r2);
}

Rational DIV_QQ_Q(const Rational& r1, const Rational& r2) {
    Rational const_disqualification(r1);
    return const_disqualification.DIV_QQ_Q(r2);
}