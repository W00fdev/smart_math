#include "smart_functional_additional.h"

std::ostream& operator<<(std::ostream& os, const Natural& n) {
    const auto data = n.getRawOdds();
    if (n.getRawDeg() > 0 && !data.empty()) {
        const uint64_t  offset = n.getRawDeg() % 3;
        int counter = 0; bool after_first = false;
        if (offset == 0u)  {
            after_first = true;
            counter = -1;
        }
        for (uint64_t i = 0u; i < n.getRawDeg(); i++) {
            if (i != 0 && n.getRawDeg() > 3 && i == offset) {
                os << "'";
                after_first = true;
            } else if (after_first) {
                counter++;
                if (counter == 3) {
                    counter = 0;
                    os << "'";
                }
            }
            os << (int)data.at(i);
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, const Natural&) {
    return is;
}

// Позволяет вводить и выводить в удобном, корректном формате.

// Integral block:

std::ostream& operator<<(std::ostream& os, const Integral& i) {
    if (i.POZ_Z_D() == 1)
        os << "-";

    const auto data = i.getRawOdds();
    if (i.getRawDeg() > 0 && !data.empty()) {
        const uint64_t offset = i.getRawDeg() % 3;
        bool after_first = false; int counter = 0;
        for (uint64_t ii = 0u; ii < i.getRawDeg(); ii++) {
            if (ii != 0 && i.getRawDeg() > 3 && ii == offset) {
                os << "'";
                after_first = true;
            } else if (after_first) {
                counter++;
                if (counter == 3) {
                    counter = 0;
                    os << "'";
                }
            }
            os << (int)data.at(ii);
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, const Integral&) {
    return is;
}

// Rational block:

std::ostream& operator<<(std::ostream& os, const Rational& r) {

    if (r.getDenominator() != Natural{"1"}) {
        os << "(";
        os << r.getNumerator();
        os << '/';
        os << r.getDenominator();
        os << ")";
    } else {
        os << r.getNumerator();
    }

    return os;
}

std::istream& operator>>(std::istream& is, const Rational&) {
    return is;
}

// Polynomial block:

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    if (p.getRawDeg() > 0) {
        int64_t deg = p.getRawDeg() - 1;
        bool first = true;
        for (const auto& odd: p.getRawOdds()) {
            if (odd != Rational("0")) {
                if (!first)
                    os << " + ";
                else
                    first = false;

                os << odd;      // Rational
                if (deg > 0) {
                    os << "x";
                    if (deg > 2)
                        os << "^" + std::to_string(deg);
                }
            }
            deg--;
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, const Polynomial& p) {
    return is;
}