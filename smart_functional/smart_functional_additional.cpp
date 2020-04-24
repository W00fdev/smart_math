#include "smart_functional_additional.h"

std::ostream& operator<<(std::ostream& os, const Natural& n) {
    const auto data = n.getRawOdds();
    if (n.getRawDeg() > 0 && !data.empty()) {
        const unsigned offset = data.size() - n.getRawDeg();
        for (unsigned i = offset; i < n.getRawDeg() + offset; i++) {
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
        const unsigned offset = data.size() - i.getRawDeg();
        for (unsigned ii = offset; ii < i.getRawDeg() + offset; ii++) {
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
        for (const auto& odd: p.getRawOdds()) {
            os  << odd;      // Rational
            if (deg != 0) {
                os << "x^" + std::to_string(deg);
                os << " + ";      // если не последний элемент
            }

            deg--;
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, const Polynomial& p) {
    return is;
}