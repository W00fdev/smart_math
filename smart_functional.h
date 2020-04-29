// Общий функционал, классонезависимый.

#ifndef PROJECT_SMART_FUNCTIONAL_H
#define PROJECT_SMART_FUNCTIONAL_H

#include <string>

// Stream optimisations block

void ActivateFastStreams();
void DeactivateFastStreams();

// String parse block

// Возвращает строку с минусом, если есть.
std::string ParseStringForNums(std::string src, size_t&);
std::string ParseStringForFraction(std::string src, size_t&);
std::string ParseStringForPolynomial(std::string src, size_t&);


#endif //PROJECT_SMART_FUNCTIONAL_H
