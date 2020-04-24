#include "smart_naturals.h"

/*
    Реализация методов класса Natural.
    Дополнительные методы: ...
    MakeNull()... -> обнуляет число

*/

/*  [N - 1]
    Олег Баязитов. 9302
    Сравниваем степени, при тождестве сравниваем посимвольно.
*/
int Natural::COMM_NN_D(const Natural& n) const {
    // n1 > n2 : return 2;
    // n1 < n2 : return 1;
    // n1 == n2 return 0;

    if (deg > n.getRawDeg())
        return 2;
    else if (deg < n.getRawDeg())
        return 1;
    else {
        if (deg == 0u) return 0;
        std::deque<uint8_t> temp_odds = n.getRawOdds();         // Скопируем, для избежания многочисл. копий в цикле
        for (unsigned runner = 0u; runner < deg; runner++) { // Пройдёмся по разрядам, начиная слева.
            if (odds.at(runner) != temp_odds.at(runner)) {
                if (odds.at(runner) > temp_odds.at(runner))
                    return 2;
                else
                    return 1;
            }
        }
    }

    return 0;
}


/*
    Автор модуля.
    Проверка на ноль и обновление степени.
    Если == 0, то false
*/
// [N - 2]
bool Natural::NZER_N_B() {
    // Проверяем полноценно на ноль,
    // если у нас степень != 0, но все значения - нули
    // значит произошла ошибка, её нужно исправить
    unsigned word = 0u;
    if (deg == 1u && odds[0] == 0) return false;
    else {
        for (unsigned runner = 0; runner < deg; runner++) {
            if (odds.at(runner) == 0) {
                word++;
            } else if (odds.at(runner) != 0) {
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
    }

    return true;
}

/* [N - 3]
    Бабкин
    Поразрядно пройдёмся по числу, прибавляя единицу к каждому,
    пока у нас Ni == 9.
*/
Natural& Natural::ADD_1N_N() {
    bool flag = false;
    for (int i = 1; i <= deg; i++) {
        if (odds[deg - i] != 9) {
            odds[deg - i]++;
            flag = true;
            break;
        }
        else {
            odds[deg - i] = 0;
        }
    }

    if (!flag) {
        odds.emplace_front(1);
        deg++;
    }
    return *this;
}

/*  [N - 4]
    Архипов
    Сложение двух натуральных чисел
*/
Natural& Natural::ADD_NN_N(const Natural& n) {
    if (n.getRawDeg() == 0u) {
        return *this;
    }
    else if (deg == 0u) {
        *this = n;
        return *this;
    }
    std::deque<uint8_t> tmp = n.getRawOdds();    // дек для элементов n
    uint64_t old_deg = deg;

    deg = std::max(odds.size(), tmp.size()) + 1;    // берём deg+1 == size с запасом для большего чиса
    // на случай, если 99999 + 2, то мы заранее поднимем разряд левого числа на 1.

    // приводим к одному размеру

    uint64_t k = deg - old_deg;
    odds.insert(odds.begin(), k, 0);

    k = deg - tmp.size();
    tmp.insert(tmp.begin(), k, 0);

    int debt = 0;
    for (int64_t i = deg-1; i >= 0; i--) {
        odds[i] += debt; debt = 0;
        odds[i] += tmp[i] ; // суммируем последние разряды чисел

        if (odds[i] > 9) {
            debt = 1;
            odds[i] -= 10;
        }
    }

    NZER_N_B(); // обновим степень, если odds[0] == 0

    return *this;
}

/*  [N - 5]
    Дима Квитко
    Поразрядное вычитание с использованием debt (долга)
*/
Natural& Natural::SUB_NN_N(const Natural& n) {
    int switcher = COMM_NN_D(n);

    if (switcher == 2) {
        // Сам алгоритм вычитания. Наш объект > n
        std::deque<uint8_t > n_odds = n.getRawOdds();
        uint64_t n_deg = n.getRawDeg();
        bool debt = false;
        unsigned smallest_deg = deg - n_deg;
        unsigned nrunner = 0u;
        for (int runner = (int)deg - 1; runner >= 0; runner--) {
            if (runner >= smallest_deg)
                nrunner = runner - smallest_deg;                    // всегда инициализируется

            if (debt) { // сначала вычтем долг
                if (odds[runner] == 0) {
                    odds[runner] = 9;
                    // 0 - 1 = 9, долг остаётся
                } else {
                    odds[runner]--; // Иначе забираем и прощаем долг
                    debt = false;
                }
            }

            if (!debt && runner < smallest_deg) break;

            if (runner >= smallest_deg) {
                if (odds.at(runner) >= n_odds.at(nrunner)) {              // Ni >= N2i
                    odds[runner] = odds[runner] - n_odds[nrunner];
                } else {                                                  // Ni < N2i
                    odds[runner] += 10;
                    odds[runner] -= n_odds[nrunner];
                    debt = true;
                }
            }
        }
    } else {
        if (switcher == 1) {
            // throw func
        }

        MakeNull(); // обнуление
    }

    // Установит новую степень, если получили не ноль
    NZER_N_B(); // Проверка на ноль.

    return *this;
}

/*
    Автор модуля.
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/

// [N - 6]
Natural& Natural::MUL_ND_N(const int& d) {
    if (d == 0) {
        MakeNull();
        return *this;
    } else if (d == 1 || deg == 0) return *this;
    else if (d == 10) {
        odds.emplace_back(0);
        deg++;
        return *this;
    }

    int debt = 0;
    for (int64_t i = deg - 1; i >= 0; i--) {
        odds[i] *= d;   // 9 * 9 = 81, мы не выходим за размеры <char>
        odds[i] += debt; debt = 0;
        if (odds[i] > 9) {
            debt = odds[i] / 10;
            odds[i] %= 10;
        }
    }
    if (debt > 0) {
        odds.emplace_front(debt);
        deg++;
    }

    return *this;
}

/*  [N - 7]
    Ковтун Александр
    Домножить на 10^k == добавить k нулей в конец и увеличить разряд на k
*/

Natural& Natural::MUL_Nk_N(const uint64_t& k) {
    // здесь будут функции проверки

    odds.insert(odds.end(), k, 0);
    deg += k;

    return *this;
}


/*  [N - 8]
    Тарабурин Александр
    Перемножение двух натуральных чисел столбиком
*/

Natural& Natural::MUL_NN_N(const Natural& n) {

    Natural mul{};  // mul{} == Natural(0).
    std::deque<uint8_t> n_odds = n.getRawOdds();

    for (uint64_t i = 0; i < n.getRawDeg(); i++) {
        // мы не должны изменять оригинальный объект до конца умножения столбиком
        // потому что MUL_ND_N и MUL_NK_N изменяют объект, мы создаём временные
        Natural this_copy = *this;
        Natural temp = this_copy.MUL_ND_N(n_odds.at(n.getRawDeg() - i - 1));
        temp.MUL_Nk_N(i);
        mul.ADD_NN_N(temp);
    }
    *this = mul;
    return *this;
}

/*  [N - 9]
    Ковтун Александр
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/

Natural& Natural::SUB_NDN_N(const Natural& n, const int& d) {
    if (d >= 0 && d<10) {
        Natural temporary_nd = Natural(n).MUL_ND_N(d);  // создали копию n
        int comparer = COMM_NN_D(temporary_nd);
        if (comparer == 2) {
            SUB_NN_N(temporary_nd);
        } else if (comparer == 1 || comparer == 0) {
            *this = Natural{}; // return 0
        }
    }

    return *this;
}

/* [N - 10]
    Тарабурин Александр
    Получение первой цифры от деления *this на n*10^k
*/

uint64_t Natural::DIV_NN_Dk(const Natural& n, const uint64_t& k) {
    Natural temp(n); //Èñïîëüçóþùèéñÿ íàòóðàë äëÿ ïîèñêà çíà÷åíèÿ
    temp.MUL_Nk_N(k);
    if (COMM_NN_D(temp) == 1) return 0; // Åñëè âòîðîå ÷èñëî áîëüøå ïåðâîãî öèôðà ðàâíà 0
    Natural mem(temp); //Íàòóðàë õðàíÿùèé n*10^k
    for (int i = 2; i <= 10; i++) {
        if (COMM_NN_D(temp.MUL_ND_N(i)) == 1) return i - 1; //Åñëè íàòóðàë óìíîæåííûé íà öèôðó áîëüøå, òî âåðíåòñÿ ïðåäûäóùåå çíà÷åíèå
        temp = mem;
    }//Åñëè ïîñëå ýòîãî ïðîõîäà íå íàøëàñü öèôðà, íàäî åùå ðàç óìíîæèòü íà 10^k
    temp.MUL_Nk_N(getRawDeg() - temp.getRawDeg() - 1);
    mem = temp;
    for (int i = 2; i <= 10; i++) {
        if (COMM_NN_D(temp.MUL_ND_N(i)) == 1) return i - 1;
        temp = mem;
    }
    temp.MUL_Nk_N(1);
    mem = temp;
    for (int i = 2; i < 10; i++) {
        if (COMM_NN_D(temp.MUL_ND_N(i)) == 1) return i - 1;
        temp = mem;
    }
    return 9;
}

/*  [N - 11]
    Тарабурин Александр
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/

Natural& Natural::DIV_NN_N(const Natural& n) {
    Natural first(*this), second(n), res("0"), znach("1");
    uint64_t numb, step;
    while (first.COMM_NN_D(second) != 1) { //Исполняется пока this >= n
        numb = Natural(first).DIV_NN_Dk(second, 0); //Находиться первая цифра от деления this на n
        znach = Natural(second).MUL_ND_N(numb); //Значение для поиска положения текущей цифры
        step = 0;
        while (first.COMM_NN_D(znach.MUL_Nk_N(1)) == 2) step++;
        res.ADD_NN_N(Natural("1").MUL_Nk_N(step).MUL_ND_N(numb));
        Natural a(Natural("1").MUL_Nk_N(step).MUL_NN_N(second));
        first.SUB_NDN_N(a, numb);
        first.NZER_N_B();
    }
    *this = res;
    return *this;
}

/*
    Автор модуля.
    Краткое описание модуля...
    Ссылки на документацию, использованную при разработке.
*/
// [N - 12]
Natural& Natural::MOD_NN_N(const Natural& n) {
    // èñïîëüçîâàòü [N - 9][N - 11]
    Natural a(n), b(*this);
    Natural Diver = DIV_NN_N(a);
    *this = b.SUB_NN_N(a.MUL_NN_N(Diver));
    return *this;
}

/*  [N - 13]
    Тарабурин Александр
    НОД двух натуральных чисел
*/

Natural& Natural::GCF_NN_N(const Natural& n) {
    Natural a(*this);
    Natural b(n);
    while (b.NZER_N_B()) {
        a.MOD_NN_N(b);
        std::swap(a, b);
    }
    *this = a;
    return *this;
}

/*  [N - 14]
    Тарабурин Александр
    НОК двух натуральных чисел
*/

Natural& Natural::LCM_NN_N(const Natural& n) {
    Natural gcd = Natural(*this).GCF_NN_N(n);
    (MUL_NN_N(n)).DIV_NN_N(gcd);

    return *this;
}



// <! ---------- Friend функционал ---------- !> //



int COMM_NN_D(const Natural& n1, const Natural& n2) {
    // сравнение чисел как публичный метод класса - глупо.
    return n1.COMM_NN_D(n2);
}
Natural ADD_NN_N(const Natural& n1, const Natural& n2) {
    Natural const_disqualification(n1);
    return const_disqualification.ADD_NN_N(n2);
}

Natural SUB_NN_N(const Natural& n1, const Natural& n2) {
    Natural const_disqualification(n1);
    return const_disqualification.SUB_NN_N(n2);
}

Natural MUL_NN_N(const Natural& n1, const Natural& n2){
    Natural const_disqualification(n1);
    return const_disqualification.MUL_NN_N(n2);
}
Natural DIV_NN_N(const Natural& n1, const Natural& n2) {
    Natural const_disqualification(n1);
    return const_disqualification.DIV_NN_N(n2);
}

Natural MOD_NN_N(const Natural& n1, const Natural& n2) {
    Natural const_disqualification(n1);
    return const_disqualification.MOD_NN_N(n2);
}

Natural GCF_NN_N(const Natural& n1, const Natural& n2) {
    Natural const_disqualification(n1);
    return const_disqualification.GCF_NN_N(n2);
}

Natural LCM_NN_N(const Natural& n1, const Natural& n2) {
    Natural const_disqualification(n1);
    return const_disqualification.LCM_NN_N(n2);
}
