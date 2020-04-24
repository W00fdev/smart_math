// Классозависимый функционал.

#ifndef PROJECT_SMART_FUNCTIONAL_ADDITIONAL_H
#define PROJECT_SMART_FUNCTIONAL_ADDITIONAL_H

#include <iostream>

#include "../smart_polynomial/smart_polynomial.h"

// Natural block:

std::ostream& operator<<(std::ostream&, const Natural&);
std::istream& operator>>(std::istream&, const Natural&);

// Позволяет вводить и выводить в удобном, корректном формате.

// Integral block:

std::ostream& operator<<(std::ostream&, const Integral&);
std::istream& operator>>(std::istream&, const Integral&);


// Rational block:

std::ostream& operator<<(std::ostream&, const Rational&);
std::istream& operator>>(std::istream&, const Rational&);

// Polynomial block:

std::ostream& operator<<(std::ostream&, const Polynomial&);
std::istream& operator>>(std::istream&, const Polynomial&);

#endif //PROJECT_SMART_FUNCTIONAL_ADDITIONAL_H
