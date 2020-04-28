// Весь код должен быть хорошо закомментирован:

/*
    Автор модуля.
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/

#ifndef PROJECT_SMART_INTEGRAL_H
#define PROJECT_SMART_INTEGRAL_H

// Подключаемые стандартные библиотеки #include <...>

#include <deque>
#include <string>
#include <cstdint>  // uint64/8_t; numeric_limits<...>::max();
#include <utility>

// Подключаемые наши файлы #include "smart_module.h"

#include "../smart_functional/smart_functional.h"
#include "../smart_naturals/smart_naturals.h"

// Здесь помещаем весь код модуля заголовка (*.h файла)

// осторожно, в std есть различные функции, такие как: std::is_integral и пр.
// Поэтому не стоит целиком открывать using namespace std;

class Integral{
private:
    std::deque<uint8_t> odds;
    uint64_t deg = 0u;
    bool minus;

    // Одних конструкторов по значению прямого int'a / string'a недостаточно
    // Для удобства реализуем операторы присваивания через инкапсуляцию общей функции
    bool parser_foundation(const std::string &string_natural) {

        // Парсим строку и создаём целое число.
        // ParseString(string) гарантирует корректность выходной строки
        size_t filler;
        std::string parsed = ParseStringForNums(string_natural, filler);

        if (parsed.empty()) {
            return false;   // неудача
        }

        if (parsed[0] == '-') {
            parsed = parsed.substr(1u, parsed.size() - 1);
            minus = true;
            // Избавляемся от лишнего минуса
        }

        for (const char &num : parsed) {
            odds.emplace_back(num - '0');
        }
        deg = odds.size();
        return true;
    }

    void MakeNull() {
        odds.resize(1);
        odds[0] = 0u;
        deg = 1u;
        minus = false;
    }

public:
    Integral() {
        deg = 1u;
        odds.push_back(0u);
        minus = false;
    }

    // Конструктор с прямыми параметрами
    Integral(std::deque<uint8_t>  _odds, const uint64_t& _deg, const bool& _minus) : odds(std::move(_odds)), deg(_deg), minus(_minus) {};

    // Конструктор копирования
    Integral(const Integral& i) {
        deg = i.getRawDeg();
        odds = i.getRawOdds();
        minus = i.getMinus();
    }

    // Конструктор копирования
    explicit Integral(const Natural& i) {
        deg = i.getRawDeg();
        odds = i.getRawOdds();
        minus = false;
    }

    explicit Integral(const Natural& i, const bool _minus) {
        deg = i.getRawDeg();
        odds = i.getRawOdds();
        minus = _minus;
    }

    explicit Integral(const std::string& string_integral) {
        parser_foundation(string_integral);
    }

    // Конструктор через прямое значение
    // Через список инициализации сс C++11 можем вызывать другие конструкторы
    explicit Integral(const int64_t& num) : Integral(std::to_string(num)) {}

    ~Integral() = default;

    // <! ---------- Основные публичные методы ---------- !> //

    [[nodiscard]] Natural ABS_Z_N() const;
    [[nodiscard]] int POZ_Z_D() const;
    Integral& MUL_ZM_Z();
    [[nodiscard]] Integral TRANS_N_Z(const Natural&) const;
    [[nodiscard]] Natural TRANS_Z_N() const;
    Integral& ADD_ZZ_Z(const Integral&);
    Integral& SUB_ZZ_Z(const Integral&);
    Integral& MUL_ZZ_Z(const Integral&);
    Integral& DIV_ZZ_Z(const Integral&);
    Integral& MOD_ZZ_Z(const Integral&);

    // <! ---------- Friend функционал ---------- !> //

    friend Integral TRANS_N_Z(const Natural&);
    friend Natural TRANS_Z_N(const Integral&);
    friend Integral ADD_ZZ_Z(const Integral&, const Integral&);
    friend Integral SUB_ZZ_Z(const Integral&, const Integral&);
    friend Integral MUL_ZZ_Z(const Integral&, const Integral&);
    friend Integral DIV_ZZ_Z(const Integral&, const Integral&);
    friend Integral MOD_ZZ_Z(const Integral&, const Integral&);

    // <! ---------- Переопределённые операторы ---------- !> //

    [[nodiscard]] uint64_t getRawDeg() const { return deg; }
    [[nodiscard]] std::deque<uint8_t> getRawOdds() const { return odds; }
    [[nodiscard]] bool getMinus() const { return minus; };

    Integral& operator=(const std::string& string_num) {
        parser_foundation(string_num);
        return *this;
    }

    Integral& operator=(const Integral & num) {
        //parser_foundation(std::to_string(num), minus);
        odds = num.getRawOdds();
        deg = num.getRawDeg();
        minus = false;

        if (num.POZ_Z_D() == 1)
            minus = true;

        return *this;
    }

    Integral& operator=(const Natural & num) {
        //parser_foundation(std::to_string(num), minus);
        odds = num.getRawOdds();
        deg = num.getRawDeg();
        minus = false;
        return *this;
    }

    bool operator==(const Integral& other) const { return odds == other.getRawOdds() && minus == other.getMinus(); }
    bool operator!=(const Integral& other) const { return !(*this == other); }

    Integral& operator*(const int& d) {         // Для работы со скаляром
        Natural n = Natural(odds, deg) * d;
        odds = n.getRawOdds();
        deg = n.getRawDeg();
        return *this;
    }

    // Для работы с интегралом
    Integral& operator*(const Integral& i) {
        return MUL_ZZ_Z(i);
    }

    Integral& operator+(const Integral& i) {
        return ADD_ZZ_Z(i);
    }

    Integral& operator-(const Integral& i) {
        return SUB_ZZ_Z(i);
    }

    Integral& operator/(const Integral& other) {     // Обычное деление
        return this->DIV_ZZ_Z(other);
    }

    Integral& operator%(const Integral& other) {
        return this->MOD_ZZ_Z(other);
    }
};

#endif //PROJECT_SMART_INTEGRAL_H
