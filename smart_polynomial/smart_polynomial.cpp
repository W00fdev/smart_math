#include "smart_polynomial.h"


/*
    Реализация методов класса Polynomial.
    Дополнительные методы: ...
*/


/*  [XP - 1]
    Куликов Дмитрий
    Домножение полинома на -1
*/

Polynomial& Polynomial::MUL_ZM_P() {
    for (auto& odd : odds) {
        odd.MUL_ZM_Q(); // домножаем на минус один каждую дробь
    }

    return *this;
}


/*  [XP - 2]
    Куликов Дмитрий
    Проверка на ноль многочлена / обновление степени
*/

bool Polynomial::NZER_P_B() {
    unsigned word = 0u;
    Rational nuller{ "0" };
    if (deg == 1u && odds[0] == nuller) return false;

    for (unsigned runner = 0; runner < deg; runner++) {
        if (odds.at(runner) == nuller) {
            word++;
        }
        else if (odds.at(runner) != nuller) {
            break;
        }
    }

    if (word != 0) {
        if (word == deg) {
            MakeNull();
            return false;
        }
        else {
            odds.erase(odds.begin(), odds.begin() + word); // очистим лишнее
            deg = odds.size();
        }
    }

    return true;
}



/*  [P - 1]
    Ковтун Александр
    Сложение полиномов. Сложим соответственные коэффициенты.
*/

Polynomial& Polynomial::ADD_PP_P(const Polynomial& p) {
    // если прибавляем ноль
    if (p == Polynomial("0")) return *this;

    uint64_t offset;
    std::deque<Rational> operating_odds;
    if (deg > p.getRawDeg()) {
        offset = deg - p.getRawDeg();
        operating_odds = p.getRawOdds();
    }
    else {
        offset = p.getRawDeg() - deg;
        operating_odds = odds;
        *this = p;
    }

    for (int64_t i = operating_odds.size() - 1; i >= 0; i--) {
        odds[i + offset].ADD_QQ_Q(operating_odds[i]);
    }

    // Это ведь дроби! могут быть обратные
    NZER_P_B(); // обновим верную степень

    return *this;
}

/*  [P - 2]
    Квитко Дмитрий
    Вычитание полиномов. Используем сложение с отрицательным p.
*/

Polynomial& Polynomial::SUB_PP_P(const Polynomial& p) {
    return ADD_PP_P(Polynomial(p).MUL_ZM_P());   // Проверка происходит внутри
}

/*  [P - 3]
    Квитко Дмитрий
    Умножение многочлена на рациональное число.
    Упростим параметр, проверим на ноль. Умножим.
*/

Polynomial& Polynomial::MUL_PQ_P(const Rational& q) {
    Rational copy_q = Rational(q).RED_Q_Q();

    if (copy_q == Rational{ "0" }) {
        MakeNull();
        return *this;
    }

    for (auto& odd : odds)
        odd.MUL_QQ_Q(copy_q);

    return *this;
}

/*  [P - 4]
    Баязитов Олег
    Домножение многочлена на x^k. Повысим степень каждого монома на k
*/

Polynomial& Polynomial::MUL_Pxk_P(const uint64_t& k) {
    odds.resize(deg + k);   // новые нули добавятся вправо -> степени сместятся влево
    deg = odds.size();

    return *this;
}

/*  [P - 5]
    Баязитов Олег.
    Получение коэффициента старшего монома.
*/

Rational Polynomial::LED_P_Q() const {
    // добавить проверок и пр.
    return odds.front();
}

/*  [P - 6]
    Баязитов Олег
    Получаем степень многочлена
*/

Natural Polynomial::DEG_P_N() const {
    return Natural(deg);
}

/*  [P - 7]
    Архипов Михаил
    Вынесение дроби НОД/НОК из многочлена.
*/

Rational Polynomial::FAC_P_Q() const {
    Natural den(odds[0].getDenominator()); // Знаменатель самого левого эд-та
    Natural num(odds[0].getNumerator().TRANS_Z_N()); // Числитель самого левого эл-та
    for (uint64_t i = 1; i < deg; i++) {
        den.LCM_NN_N(odds[i].getDenominator());
        num.GCF_NN_N(odds[i].getNumerator().ABS_Z_N());
    }

    return Rational(Integral(num), den);
}

/*  [P - 8]
    Архипов Михаил
    Перемножение многочленов
    Ссылки на документацию, использованную при разработке.
*/

Polynomial& Polynomial::MUL_PP_P(const Polynomial& p) {
    const uint64_t N = p.getRawDeg();

    if (N == 0 || deg == 0) {
        MakeNull();
        return *this;
    }

    Polynomial result;
    if (deg <= p.getRawDeg()) {
        // (x - 1) * (x^3 - x + 1)
        // если степень левого < степени правого

        for (uint64_t i = 0; i < deg; i++) {
            // теперь умножим это на каждый член "p"
            Polynomial copy_other = p;
            // домножаем на коэффициент и степень
            copy_other.MUL_PQ_P(odds[i]);
            copy_other.MUL_Pxk_P(deg - 1 - i);
            result.ADD_PP_P(copy_other);
        }

    }
    else {
        auto copy_p_odds = p.getRawOdds();
        auto copy_p_degs = p.getRawDeg();
        for (uint64_t i = 0; i < p.getRawDeg(); i++) {
            // теперь умножим это на каждый член "p"
            Polynomial copy_this = *this;
            // домножаем на коэффициент и степень
            copy_this.MUL_PQ_P(copy_p_odds[i]);
            copy_this.MUL_Pxk_P(copy_p_degs - 1 - i);
            result.ADD_PP_P(copy_this);
        }
    }

    *this = result;
    return *this;
}

/*
   Куликов Дмитрий
*/
// [P - 9]
Polynomial& Polynomial::DIV_PP_P(const Polynomial& p) {
    // использовать [Q - 8][P - 1][P - 2][P - 4][P - 6]

    if (*this == Polynomial("0")) return *this;
    else if (p == Polynomial("1")) return *this;

    //Integral result;
    if (deg < p.getRawDeg()) {
        // если степень левого < степени правого
        // то деление = 0
        MakeNull();
    }
    else {
        uint64_t offset = deg - p.getRawDeg();
        uint64_t stable_deg = deg;
        Polynomial res;
        for (uint64_t i = 0; i < stable_deg; i++) {
            // делим каждый наш член
            // (10x^2 + 5x - 3) / (x - 1)

            Polynomial temp_p = p;
            temp_p.MUL_Pxk_P(offset);
            Rational divided = DIV_QQ_Q(odds[0], temp_p.LED_P_Q());    // делим i-ый левый на первый правый
            // т.к мы точно домножаем до нуля, то степень *this уменьшается и актуальный odd всегда нулевой
            temp_p.MUL_PQ_P(divided);
            SUB_PP_P(temp_p);

            std::deque<Rational> res_deq;
            res_deq.push_back(divided);
            res.ADD_PP_P(Polynomial(res_deq, res_deq.size()).MUL_Pxk_P(offset));

            if (offset == 0) {
                break;
            }
            offset--;

            // Домножить на 10^offset
            // offset--
            // Поделить Дробь a на b = с
            // домножить временный полином на с
            // вычесть из a c
            // -> следующий круг
        }
        *this = res;
    }

    return *this;
}

/*   [P - 10]
    Архипов Михаил
    Остаток от деления многочленов по алгоритму евклида
*/

Polynomial& Polynomial::MOD_PP_P(const Polynomial& p) {
    if (*this == Polynomial("0")) return *this;
    else if (p == Polynomial("1")) return *this;

    //Integral result;
    if (deg >= p.getRawDeg()) {
        Polynomial priv(*this);
        priv.DIV_PP_P(p); // Частное от деления левого на правое
        priv.MUL_PP_P(p); // Правое умножаем на частное
        this->SUB_PP_P(priv); // вычитаем
    }

    return *this;
}

/*  [P - 11]
    Архипов Михаил
    Взятие НОД многочленов
*/

Polynomial Polynomial::GCF_PP_P(const Polynomial& p) {
    // Проверки

    if (p == Polynomial("1")) { //  Если Р = 0, то возвращаем *this
        return Polynomial{ "1" };
    }
    else if (*this == Polynomial("0")) { //Если первый полином равен нулю,то возвращаем P
        if (p == Polynomial("0"))
            return Polynomial("0");

        return Polynomial{ p };
    }
    else if (p == Polynomial("0")) {
        return *this;
    }
    else { // Обычный алгоритм НОД
        Polynomial copy_p(p);
        while (copy_p != Polynomial{ 0 }) {
            if (deg >= copy_p.getRawDeg()) {
                Polynomial priv(*this);
                this->DIV_PP_P(copy_p);
                for (auto& odd : odds) {
                    odd = odd.TRANS_Z_Q(odd.TRANS_Q_Z());
                }
                this->MUL_PP_P(copy_p);
                priv.SUB_PP_P(*this);

                Polynomial tmp(copy_p);
                copy_p = priv;
                *this = tmp;        // меняем местами a и b
            }
            else {
                return Polynomial{ 1 };
            }
        }
    }

    return *this;
}

/*  [P - 12]
    Архипов Михаил
    Производная многочлена
*/

Polynomial& Polynomial::DER_PP_P() {
    std::deque<Rational> Derivative;
    if (deg == 1) {
        MakeNull();
        return *this;
    }

    for (int64_t i = 0; i < deg - 1; i++) {
        Derivative.emplace_back(odds[i].MUL_QQ_Q(Rational{ Integral{(int64_t)deg - 1 - i},Natural{1} }));
    }

    odds = Derivative;
    deg = odds.size();
    return *this;
}

/*  [P - 13]
    Архипов Михаил
*/

Polynomial& Polynomial::NMR_P_P() {
    if (*this != Polynomial{ 0 } && deg > 1) {
        Polynomial tmp_this(*this);
        tmp_this.DER_PP_P();
        tmp_this.GCF_PP_P(*this);
        this->DIV_PP_P(tmp_this);
        Rational NOD_NOK = FAC_P_Q();
        for (auto& odd : odds) {
            odd.DIV_QQ_Q(NOD_NOK);
        }
    }
    else {
        MakeNull();
    }
    return *this;
}



// <! ---------- Friend функционал ---------- !> //



Polynomial ADD_PP_P(const Polynomial& p1, const Polynomial& p2) {
    Polynomial const_disqualification(p1);
    return const_disqualification.ADD_PP_P(p2);
}

Polynomial SUB_PP_P(const Polynomial& p1, const Polynomial& p2) {
    Polynomial const_disqualification(p1);
    return const_disqualification.SUB_PP_P(p2);
}

Polynomial MUL_PQ_P(const Polynomial& p1, const Rational& r1) {
    Polynomial const_disqualification(p1);
    return const_disqualification.MUL_PQ_P(r1);
}

Polynomial MUL_Pxk_P(const Polynomial& p1, const uint64_t& k) {
    Polynomial const_disqualification(p1);
    return const_disqualification.MUL_Pxk_P(k);
}

Polynomial MUL_PP_P(const Polynomial& p1, const Polynomial& p2) {
    Polynomial const_disqualification(p1);
    return const_disqualification.MUL_PP_P(p2);
}

Polynomial DIV_PP_P(const Polynomial& p1, const Polynomial& p2) {
    Polynomial const_disqualification(p1);
    return const_disqualification.DIV_PP_P(p2);
}

Polynomial MOD_PP_P(const Polynomial& p1, const Polynomial& p2) {
    Polynomial const_disqualification(p1);
    return const_disqualification.MOD_PP_P(p2);
}

Polynomial GCF_PP_P(const Polynomial& p1, const Polynomial& p2) {
    Polynomial const_disqualification(p1);
    return const_disqualification.GCF_PP_P(p2);
}


Rational FAC_P_Q(const Polynomial& p) {
    return p.FAC_P_Q();
}