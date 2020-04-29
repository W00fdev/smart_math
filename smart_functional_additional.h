// Классозависимый функционал.

#ifndef PROJECT_SMART_FUNCTIONAL_ADDITIONAL_H
#define PROJECT_SMART_FUNCTIONAL_ADDITIONAL_H

#include <iostream>

#include "../smart_polynomial/smart_polynomial.h"

using std::noskipws;
using std::string;

// Natural block:

std::ostream& operator<<(std::ostream&, const Natural&);
std::istream& operator>>(std::istream&, Natural&);

// Позволяет вводить и выводить в удобном, корректном формате.

// Integral block:

std::ostream& operator<<(std::ostream&, const Integral&);
std::istream& operator>>(std::istream&, Integral&);


// Rational block:

std::ostream& operator<<(std::ostream&, const Rational&);
std::istream& operator>>(std::istream&, Rational&);

// Polynomial block:

std::ostream& operator<<(std::ostream&, const Polynomial&);
std::istream& operator>>(std::istream&, Polynomial&);

#endif //PROJECT_SMART_FUNCTIONAL_ADDITIONAL_H
