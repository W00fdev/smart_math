#include "smart_functional.h"

#include <iostream>
#include <sstream>
#include <cctype> // isdigit

using namespace std;

void ActivateFastStreams() {
    // Отключаем синхронизацию с C-потоками и их буфферами.
    ios_base::sync_with_stdio(false);
    // Отрубаем связанные потоки.
    cout.tie(nullptr);
    cin.tie(nullptr);
    cerr.tie(nullptr);

    // Вместо endl; используем "\n". Потому что endl очищает буффер.
    // Использовать endl только там, где указано.
}


// Возвращает подстроку с ЧИСЛОМ, а значит, с минусом! Оставим минус на совесть внутриклассовых парсеров.
std::string ParseStringForNums(std::string src, size_t& end_pos) {

    size_t start_pos = 0; // Будем двигать, пока не найдём начало числа
    end_pos = 0; // Будем двигать, пока не найдём конец числа

    /// C-style parser

    // находим начало цифры : если нашлась цифра / - и это не конец строки и после него цифра
    while (start_pos < src.size()) {
        if (isdigit(src[start_pos])) break;
        else if (src[start_pos] == '-' && start_pos < src.size() - 1 && isdigit(src[start_pos + 1])) break;

        start_pos++;
    }

    end_pos = start_pos + 1;

    while (end_pos < src.size() && isdigit(src[end_pos])) {
        end_pos++;  // двигаем, пока не встретим НЕ цифру.
    }

    return src.substr(start_pos, end_pos - start_pos);
}

// Возвращает подстроку с корректной ДРОБЬЮ
std::string ParseStringForFraction(std::string src, size_t& _pos) {
    size_t pos_ending = 0u;

    string numleft = ParseStringForNums(src, _pos);
    if (numleft.empty()) {
        _pos = pos_ending;
        return "";
    }

    pos_ending += _pos;

    if (src[_pos] != '/') {
        _pos = pos_ending;
        return numleft + "/1";
    }

    _pos++;
    size_t start_pos_right = _pos;
    while (_pos < src.size() && isdigit(src[_pos]))
        _pos++;

    if (start_pos_right == _pos) {
        _pos = pos_ending;
        return numleft + "/1";
    }

    return numleft + '/' + src.substr(start_pos_right, _pos - start_pos_right);

}

std::string ParseStringForPolynomial(std::string src, size_t& pos) {
    std::string res;
    size_t temp_pos = 0u;

    while (pos != string::npos && pos < src.size()) {
        res += ParseStringForFraction(src.substr(pos), temp_pos);
        pos += temp_pos;
        if (src[pos] == 'x') {
            std::string additional;
            if (pos < src.size() - 2 && src[pos + 1] == '^') {
                if (isdigit(src[pos + 2])) {
                    additional = string("^") + ParseStringForNums(src.substr(pos + 2), temp_pos);
                    pos += additional.size();
                }
            }
            res += string("x") + additional;
            pos++;
        }

        while (pos < src.size() && pos != string::npos && src.at(pos) != ' ')
            pos++; // может быть всякое: 13x^3 !pos на пробеле!

        if (pos < src.size())
            res += " ";
    }

    // для свободного коэффициента без х
    if (pos < src.size())
        res += ParseStringForNums(src.substr(pos), pos);


    return res;
}