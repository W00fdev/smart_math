// Весь код должен быть хорошо закомментирован:

/*
    Куликов Д.А гр. 9302 (архитектор)
    Определение класса натуральных чисел Natural.

    friend-функции используются для удобного получения нового объекта, не изменяя
    вызывающий объект, как это зачастую используется: object.todo(params); использование
    методов таким способом скорее всего повлечёт за собой изменение object (смотрите идентификатор
    const у методов справа). friend же функции не привязаны к объектам и не изменяют их данных:
    sum(N1, N2) == N1 + N2; Это сделано для удобства программиста, использующего класс Natural.

    Некоторые функции имеют переопределённые операторы, что делает код ещё более читаемым. Например:
    N1 / N2 == DIV_NN_N(N1, N2);

    // friend
    // [nodiscard]
 */

#ifndef PROJECT_SMART_NATURALS_H
#define PROJECT_SMART_NATURALS_H

#include <deque>
#include <string>
#include <cstdint>  // uint64/8_t; numeric_limits<...>::max();
#include <utility>

#include "../smart_functional/smart_functional.h"


class Natural {
private:
    std::deque<uint8_t> odds;

    // Цифры разрядов. Т.к 0..9, то храним 1 байтом.
    // Стоит сразу упомянуть о проблемах, возникающих с использованием этого типа данных
    // Во-первых: никаких отрицательных чисел! У нас натуральные числа, тип unsigned.
    // Во-вторых: тип: unsigned char, соответственно не удивляемся, что cout << odds[i] даст нам не цифру, а мусор-символ
    // В-третьих: используем касты при трансформации и любом использовании. В интерфейсе предоставим Get типа int!

    uint64_t deg = 0u;

    // Старший разряд числа. Опять же, unsigned. Арифметика длинная, но тип имеет ограничения: std::numeric_limits<uint64_t>::max();
    // Вполне разумные, необходимо проверять строку и параметры, а также результат операций на допустимость,
    // Чтобы ушлые юзеры не перемножали триллионные степени и программа не падала.

    bool parser_foundation(const std::string &string_natural) {

        // Парсим строку и создаём натуральное число.
        // ParseString(string) гарантирует корректность выходной строки
        size_t filler;
        std::string parsed = ParseStringForNums(string_natural, filler);

        if (parsed.empty()) {
            return false;   // неудача
        }

        if (parsed[0] == '-') {
            parsed = parsed.substr(1u, parsed.size() - 1);
            // Избавляемся от лишнего минуса
        }

        for (const char num : parsed) {
            odds.emplace_back(num - '0');     // atoi(reinterpret_cast<const char *>(num))
        }
        deg = odds.size();
        return true;
    }

    void MakeNull() {
        odds.resize(1);
        odds[0] = 0u;   // 0 - это тоже символ, поэтому deg = 1
        deg = 1u;
    }

public:
    Natural() {
        deg = 1u;
        odds.push_back(0u);
    }

    // Конструктор с прямыми параметрами
    Natural(std::deque<uint8_t> _odds, const uint64_t &_deg) : odds(std::move(_odds)), deg(_deg) {};

    // Конструктор копирования
    Natural(const Natural &n) {
        deg = n.getRawDeg();
        odds = n.getRawOdds();
    }

    explicit Natural(const std::string &string_natural) {
        parser_foundation(string_natural);
    }

    // Конструктор через прямое значение
    // Через список инициализации сс C++11 можем вызывать другие конструкторы
    // explicit не допустит подачи int64_t и приведения его к типу uint64_t
    explicit Natural(const uint64_t &num) : Natural(std::to_string(num)) {}

    // Деструктор по умолчанию.
    ~Natural() = default;

    // <! ---------- Основные публичные методы ---------- !> //

    [[nodiscard]] int COMM_NN_D(const Natural&) const;
    bool NZER_N_B();  // Изменит степень, если вдруг ноль не обнаружен
    Natural &ADD_1N_N();
    Natural &ADD_NN_N(const Natural &);
    Natural &SUB_NN_N(const Natural &);
    Natural &MUL_ND_N(const int &);
    Natural &MUL_Nk_N(const uint64_t &);
    Natural &MUL_NN_N(const Natural &);
    Natural &SUB_NDN_N(const Natural &, const int &);
    uint64_t DIV_NN_Dk(const Natural &, const uint64_t &);
    Natural &DIV_NN_N(const Natural &);
    Natural &MOD_NN_N(const Natural &);
    Natural &GCF_NN_N(const Natural &);
    Natural &LCM_NN_N(const Natural &);

    // <! ---------- Friend функционал ---------- !> //

    friend int COMM_NN_D(const Natural &, const Natural &);
    friend Natural ADD_NN_N(const Natural &, const Natural &);
    friend Natural SUB_NN_N(const Natural &, const Natural &);
    friend Natural MUL_NN_N(const Natural &, const Natural &);
    friend Natural DIV_NN_N(const Natural &, const Natural &);
    friend Natural MOD_NN_N(const Natural &, const Natural &);
    friend Natural GCF_NN_N(const Natural &, const Natural &);
    friend Natural LCM_NN_N(const Natural &, const Natural &);

    // <! ---------- Переопределённые операторы ---------- !> //

    bool operator==(const Natural &other) const {
        return deg == other.getRawDeg() && odds == other.getRawOdds();
    }

    bool operator!=(const Natural &other) const {
        return !(*this == other);
    }

    Natural &operator=(const std::string &string_num) {
        parser_foundation(string_num);
        return *this;
    }

    Natural &operator=(const int64_t &num) {
        parser_foundation(std::to_string(num));
        return *this;
    }

    Natural& operator*(const int &d) {         // Для работы со скаляром
        return this->MUL_ND_N(d);
    }

    Natural& operator*(const Natural& n) {   // Для работы с натуралом.
        return this->MUL_NN_N(n);
    }

    Natural& operator/(const Natural& other) {     // Обычное деление
        return this->DIV_NN_N(other);
    }

    Natural& operator%(const Natural& other) {
        return this->MOD_NN_N(other);
    }

    // Передаём КОПИИ разряда числа и очереди всех его цифр.
    [[nodiscard]] uint64_t getRawDeg() const { return deg; }
    [[nodiscard]] std::deque<uint8_t> getRawOdds() const { return odds; }
};

#endif // PROJECT_SMART_NATURALS_H
