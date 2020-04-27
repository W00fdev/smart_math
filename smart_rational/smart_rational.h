/*
 *
*/

#ifndef PROJECT_SMART_RATIONAL_H
#define PROJECT_SMART_RATIONAL_H

#include <algorithm>

#include "Integral.h"

class Rational{
private:
    Integral numerator;
    //       ----------
    Natural denominator;

    bool parser_foundation(const std::string &string_rational) {

        // Парсим строку и создаём натуральное число.
        // ParseString(string) гарантирует корректность выходной строки
        size_t filler = 0u;
        std::string parsed = ParseStringForFraction(string_rational, filler);

        if (parsed.empty()) {
            return false;   // неудача
        }

        bool minus = false;
        if (parsed[0] == '-') {
            parsed = parsed.substr(1u, parsed.size() - 1);
            // Избавляемся от лишнего минуса
            minus = true;
        }
        bool after_slash = false;

        std::deque<uint8_t> num_odds;
        std::deque<uint8_t> denom_odds;

        for (const char num : parsed) {
            if (!after_slash && num != '/') {
                num_odds.emplace_back(num - '0');     // atoi(reinterpret_cast<const char *>(num))
            } else  if (num != '/'){
                denom_odds.emplace_back(num - '0');
            }

            if (num == '/')
                after_slash = true;
        }

        numerator = Integral(num_odds, num_odds.size(), minus);
        denominator = Natural(denom_odds, denom_odds.size());

        return true;
    }

    void MakeNull() {
        denominator = Natural{"1"};
        numerator = Integral{};
    }

public:

    Rational() {
        numerator = Integral{};
        denominator = Natural{"1"};
    }

    // Конструктор с прямыми параметрами слишком объёмный, удалим его для класса рац. чисел
    Rational(const std::deque<uint8_t>&, const uint64_t&, const bool&,
            const std::deque<uint8_t>&, const uint64_t&) = delete;

    // Конструктор копирования
    Rational(const Rational& r) {
        denominator = r.getDenominator();
        numerator = r.getNumerator();
    }
    Rational(const Integral& i, const Natural& n) : numerator(i), denominator(n) {}

    Rational(const Integral& i) {
        numerator = i;
        denominator = Natural{"1"};
    }

    explicit Rational(const std::string& string_rational) {
        parser_foundation(string_rational);
    }

    // Конструктор через прямое значение
    // Через список инициализации сс C++11 можем вызывать другие конструкторы
    explicit Rational(const int64_t& num, const uint64_t& num2) {
        numerator = Integral(num);
        denominator = Natural(num2);
    }

    ~Rational() = default;

    // <! ---------- Основные публичные методы ---------- !> //

    Rational& INVERT_Q(); // переворачивает дробь
    Rational& MUL_ZM_Q(); // Домножает дробь на -1

    Rational& RED_Q_Q();
    [[nodiscard]] bool INT_Q_B() const;
    [[nodiscard]] Rational TRANS_Z_Q(const Integral&) const;
    [[nodiscard]] Integral TRANS_Q_Z() ;
    Rational& ADD_QQ_Q(const Rational&);
    Rational& SUB_QQ_Q(const Rational&);
    Rational& MUL_QQ_Q(const Rational&);
    Rational& DIV_QQ_Q(const Rational&);

    // <! ---------- Friend функционал ---------- !> //

    friend Rational INVERT_Q(const Rational&); // переворачивает дробь
    friend Rational RED_Q_Q(const Rational&);
    friend bool INT_Q_B(const Rational&);
    friend Rational TRANS_Z_Q(const Integral&);
    friend Integral TRANS_Q_Z(const Rational&);
    friend Rational ADD_QQ_Q(const Rational&, const Rational&);
    friend Rational SUB_QQ_Q(const Rational&, const Rational&);
    friend Rational MUL_QQ_Q(const Rational&, const Rational&);
    friend Rational DIV_QQ_Q(const Rational&, const Rational&);

    // <! ---------- Переопределённые операторы ---------- !> //

    [[nodiscard]] Natural getDenominator() const { return denominator; }
    [[nodiscard]] Integral getNumerator() const { return numerator; }

    //Rational& operator=(const std::string& string_num);

    Rational& operator=(const Rational & num) {
        numerator = num.getNumerator();
        denominator = num.getDenominator();
        return *this;
    }

    int operator==(const Rational& other) const {
        Rational copy_other = other;
        copy_other.RED_Q_Q();

        Rational copy_this = *this;
        copy_this.RED_Q_Q();

        return copy_this.getDenominator() == copy_other.getDenominator()
                &&  copy_this.getNumerator() == copy_other.getNumerator();
    }

    int operator!=(const Rational& other) const {
        return !(*this == other);
    }

    Rational& operator*(const int&);         // Для работы со скаляром
    Rational& operator*(const Natural&);   // Для работы со степенями
    Rational& operator*(const Rational&);   // Для работы с рац. числами

    Rational& operator/(const Rational& other) ;

    Rational& operator%(const Rational& other);
};

#endif //PROJECT_SMART_RATIONAL_H
