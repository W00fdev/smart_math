/*
 *
*/


#ifndef PROJECT_SMART_POLYNOMIAL_H
#define PROJECT_SMART_POLYNOMIAL_H

#include "../smart_rational/smart_rational.h"
#include "../smart_functional/smart_functional.h"


class Polynomial {
private:
    std::deque<Rational> odds;
    uint64_t deg;

    // Одних конструкторов по значению прямого int'a / string'a недостаточно
    // Для удобства реализуем операторы присваивания через инкапсуляцию общей функции
    void parser_foundation(const std::string& string_polynomial) {
        size_t filler = 0u;
        std::string parsed = ParseStringForPolynomial(string_polynomial, filler);
        // приведено к виду: "x/y x/y x/y"

        size_t pos = 0u;
        uint64_t deg_pos = 0u;
        uint64_t stable_deg = 0u;

        uint64_t max_deg = 0u;

        while (pos < parsed.size()) {
            deg_pos++;
            std::string parsed_rational = ParseStringForFraction(parsed.substr(pos), filler);
            pos += filler;
            filler = 0u;
            if (parsed[pos] == 'x') {
                filler = 1;
                if (pos < parsed.size() - 2 && parsed[pos + 1] == '^') {
                    if (isdigit(parsed[pos + 2])) {
                        uint64_t tmp_deg_pos = std::stoi(ParseStringForNums(parsed.substr(pos + 2), filler));

                        if (tmp_deg_pos > max_deg)
                            max_deg = tmp_deg_pos + 1;

                        //if (deg_pos == tmp_deg_pos) deg_pos--;

                        filler += std::to_string(tmp_deg_pos).size();
                    }
                }
            }

            pos += filler + 1; // + " "
            if (max_deg < deg_pos)
                max_deg = deg_pos;
        }

        odds.resize(max_deg, Rational("0/1"));  // устанавливаем массив нужной величины
        pos = 0u;

        while (pos != std::string::npos && pos < parsed.size()) {
            deg_pos = 0u;
            std::string parsed_rational = ParseStringForFraction(parsed.substr(pos), filler);
            pos += filler;
            filler = 0u;
            if (parsed[pos] == 'x') {
                deg_pos = 1u;
                filler = 1;
                if (pos < parsed.size() - 2 && parsed[pos + 1] == '^') {
                    if (isdigit(parsed[pos + 2])) {
                        deg_pos = std::stoi(ParseStringForNums(parsed.substr(pos + 2), filler));
                        filler += std::to_string(deg_pos).size();
                    }
                }
            }

            pos += filler + 1; // + " "

            if (deg_pos == 0) {
                odds[odds.size() - stable_deg - 1] = Rational(parsed_rational);
                stable_deg++;
            }
            else
                odds[odds.size()  - deg_pos - 1] = Rational(parsed_rational);
        }

        deg = odds.size();
    }

    void MakeNull() {
        deg = 1u;
        odds.clear();
        odds.emplace_back(Rational{"0"});
    }

public:
    Polynomial() {
        deg = 1u;
        odds.emplace_back(Rational{"0"});
    }

    // Конструктор с прямыми параметрами
    Polynomial(std::deque<Rational>  _odds, const uint64_t & _deg) : odds(std::move(_odds)), deg(_deg) {};

    // Конструктор копирования
    Polynomial(const Polynomial& p) {
        deg = p.getRawDeg();
        odds = p.getRawOdds();
    }

    explicit Polynomial(const std::string& string_integral) {
        parser_foundation(string_integral);
        deg = odds.size();
    }

    // Конструктор через прямое значение
    // Через список инициализации сс C++11 можем вызывать другие конструкторы
    explicit Polynomial(const int64_t& num) : Polynomial(std::to_string(num)) {}

    ~Polynomial() = default;

    // <! ---------- Основные публичные методы ---------- !> //

    // дополнительный метод * -1
    Polynomial& MUL_ZM_P();
    // дополнительный метод обновления степени, проверки на ноль
    bool NZER_P_B();

    Polynomial& ADD_PP_P(const Polynomial&);
    Polynomial& SUB_PP_P(const Polynomial&);
    Polynomial& MUL_PQ_P(const Rational&);
    Polynomial& MUL_Pxk_P(const uint64_t& k);
    [[nodiscard]] Rational LED_P_Q() const;
    [[nodiscard]] Natural DEG_P_N() const;
    [[nodiscard]] Rational FAC_P_Q() const;
    Polynomial& MUL_PP_P(const Polynomial&);
    Polynomial& DIV_PP_P(const Polynomial&);
    Polynomial& MOD_PP_P(const Polynomial&);
    Polynomial GCF_PP_P(const Polynomial&);
    Polynomial& DER_PP_P();
    Polynomial& NMR_P_P();

    // <! ---------- Friend функционал ---------- !> //

    friend Polynomial ADD_PP_P(const Polynomial&, const Polynomial&);
    friend Polynomial SUB_PP_P(const Polynomial&, const Polynomial&);
    friend Polynomial MUL_PQ_P(const Polynomial&, const Rational&);
    friend Polynomial MUL_Pxk_P(const Polynomial&, const uint64_t& k);
    friend Polynomial MUL_PP_P(const Polynomial&, const Polynomial&);
    friend Polynomial DIV_PP_P(const Polynomial&, const Polynomial&);
    friend Polynomial MOD_PP_P(const Polynomial&, const Polynomial&);
    friend Polynomial GCF_PP_P(const Polynomial&, const Polynomial&);
    friend Rational FAC_P_Q(const Polynomial&);

    // <! ---------- Переопределённые операторы ---------- !> //

    // у нас есть DEG_P_N и LED_P_Q, но они не константны
    [[nodiscard]] uint64_t getRawDeg() const { return deg; }
    [[nodiscard]] std::deque<Rational> getRawOdds() const { return odds; }
    [[nodiscard]] std::deque<Rational>& getRawOdds_nc() { return odds; } // nc - not const

    Polynomial& operator=(const Polynomial& num) {
        odds = num.getRawOdds();
        deg = num.getRawDeg();
    }

    Polynomial& operator=(const std::string& string_num) {
        parser_foundation(string_num);
    }


    bool operator==(const Polynomial& other) const {
        return deg == other.getRawDeg() && odds == other.getRawOdds();
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    Polynomial& operator*(const int& d) {
        return MUL_PQ_P(Rational("1/1") * d);
    }

    Polynomial& operator*(const Rational& r) {
        return MUL_PQ_P(r);
    }

    Polynomial& operator*(const Polynomial& p) {
        return MUL_PP_P(p);
    }

    Polynomial& operator+(const Polynomial& p) {
        return ADD_PP_P(p);
    }

    Polynomial& operator-(const Polynomial& p) {
        return SUB_PP_P(p);
    }

    Polynomial& operator/(const Polynomial& p) {
        return DIV_PP_P(p);
    }

    Polynomial& operator/(const Rational& r) {
        return MUL_PQ_P(INVERT_Q(r));
    }

    Polynomial& operator%(const Polynomial& p) {
        return MOD_PP_P(p);
    }

};

#endif //PROJECT_SMART_POLYNOMIAL_H
