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
    Rational nuller{"0"};
    if (deg == 1u && odds[0] == nuller) return false;

    for (unsigned runner = 0; runner < deg; runner++) {
        if (odds.at(runner) == nuller) {
            word++;
        } else if (odds.at(runner) != nuller) {
            break;
        }
    }

    if (word != 0) {
        if (word == deg) {
            MakeNull();
            return false;
        } else {
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
    if (p.getRawDeg() == 0) return *this;

    std::deque<Rational> operating_odds;
    if (deg > p.getRawDeg()) {
        operating_odds = p.getRawOdds();

    } else {
        operating_odds = odds;
        odds = p.getRawOdds();
    }

    for (int64_t i = operating_odds.size() - 1; i >= 0; i--) {
        odds[i].ADD_QQ_Q(operating_odds[i]);
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
    Polynomial copy_p = p;
    copy_p.MUL_ZM_P();
    ADD_PP_P(copy_p);   // Проверка происходит внутри

    return *this;
}

/*  [P - 3]
    Квитко Дмитрий
    Умножение многочлена на рациональное число.
    Упростим параметр, проверим на ноль. Умножим.
*/

Polynomial& Polynomial::MUL_PQ_P(const Rational& q) {
    Rational copy_q = q;
    copy_q.RED_Q_Q();
    if (copy_q == Rational{"0"}) {
        MakeNull();
        return *this;
    }

    for (auto& odd : odds) {
        odd.MUL_QQ_Q(copy_q);
    }

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

Rational Polynomial::FAC_P_Q() {
    Natural den(odds[0].getDenominator()); // Знаменатель самого левого эд-та
    Natural num(odds[0].getNumerator().getRawOdds(), odds[0].getNumerator().getRawDeg()); // Числитель самого левого эл-та
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
    Polynomial copy_this = *this;
    Polynomial copy_other = p;

    // для скорости, если степени сильно отличаются
    // Да, дублирование кода. Пусть останется так.
    if (deg <= p.getRawDeg()) {
        // (x - 1) * (x^3 - x + 1)
        // если степень левого < степени правого

        for (uint64_t i = 0; i < deg; i++) {
            // теперь умножим это на каждый член "p"
            copy_other.MUL_PQ_P(odds[i]);    // домножаем на коэффициент и степень
            copy_other.MUL_Pxk_P(i);
        }
    } else {
        for (uint64_t i = 0; i < p.getRawDeg(); i++) {
            // теперь умножим это на каждый член "p"
            copy_other.MUL_PQ_P(copy_other.getRawOdds()[i]);    // домножаем на коэффициент и степень
            copy_other.MUL_Pxk_P(i);
        }

    }

    deg = odds.size();

    return *this;
}

/*
    Автор модуля.
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/
// [P - 9]
Polynomial& Polynomial::DIV_PP_P(const Polynomial& p) {
    // использовать [Q - 8][P - 1][P - 2][P - 4][P - 6]

    if (deg == 0) return *this;
    else if (p.DEG_P_N() == Natural{0}) return *this;

    //Integral result;
    if (deg < p.getRawDeg()) {
        // если степень левого < степени правого
        // то деление = 0
        MakeNull();
    } else {
        uint64_t offset = deg - p.getRawDeg();
        for (uint64_t i = 0; i < deg; i++) {
            // делим каждый наш член

            // (10x^2 + 5x - 3) / (x - 1)

            Polynomial temp_p = p;
            temp_p.MUL_Pxk_P(offset);
            Integral divided = TRANS_Q_Z(DIV_QQ_Q(odds[i], temp_p.LED_P_Q()));    // делим i-ый левый на первый правый
            temp_p.MUL_PQ_P(Rational(divided));
            SUB_PP_P(temp_p);

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

    }

    return *this;
}

/*
    Автор модуля.
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/
// [P - 10]
Polynomial& Polynomial::MOD_PP_P(const Polynomial&) {
    // использовать [P - 2][P - 8][P - 9]
    return *this;
}

/*
    Автор модуля.
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/
// [P - 11]
Polynomial Polynomial::GCF_PP_P(const Polynomial&) const {
    // использовать [P - 6][P - 10]
    return Polynomial{};
}

/*
    Автор модуля.
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/
// [P - 12]
[[nodiscard]] Polynomial& Polynomial::DER_PP_P() {
    return *this;
}

/*
    Автор модуля.
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/
//[P - 13]
Polynomial& Polynomial::NMR_P_P() {
    // использовать [P - 9][P - 11][P - 12]
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

Polynomial MUL_PQ_P(const Polynomial& p1, const Rational& r1){
    Polynomial const_disqualification(p1);
    return const_disqualification.MUL_PQ_P(r1);
}

Polynomial MUL_Pxk_P(const Polynomial& p1, const uint64_t& k) {
    Polynomial const_disqualification(p1);
    return const_disqualification.MUL_Pxk_P(k);
}