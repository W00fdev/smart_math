#include "Integral.h"

/*
    ���������� ������� ������ Natural.
    �������������� ������: ...
*/

/* [Z - 1]
    ������ ������
    ������ �������������� �� ������ �� ������ �����
*/

Natural Integral::ABS_Z_N() const {
    return Natural(odds, deg);
}

/*  [Z - 2]
    �������� ����
    ����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
*/

int Integral::POZ_Z_D() const {
    int flag = ABS_Z_N().NZER_N_B();
    if (minus && flag)  // minus && !0
        return 1; // < 0

    return 2 * flag;  // >0 || 0
}

/*  [Z - 3]
    �������� ����
    �������� ��������, ���������� �� ��������������� �����
*/

Integral& Integral::MUL_ZM_Z() {
    if (ABS_Z_N().NZER_N_B())
        minus = !minus;

    return *this;
}

/*  [Z - 4]
    ������ ����
    �������������� �� ������������ � ����� �����
*/

Integral Integral::TRANS_N_Z(const Natural& n) const {
    return Integral(n.getRawOdds(), n.getRawDeg(), false);
}

/*  [Z - 5]
    ������ ����
    �������������� �� ������ � �����������
*/

Natural Integral::TRANS_Z_N() const {
    return Natural(odds, deg);
}

/*  [Z - 6]
    ������ �������
    �������� ���� ����� �����
*/

Integral& Integral::ADD_ZZ_Z(const Integral& b) {
    int switcher = b.POZ_Z_D();
    Natural temp_n(odds, deg);  // ����� ������ �������
    int greater = temp_n.COMM_NN_D(b.ABS_Z_N());

    if ((switcher == 2 && !minus) || (switcher == 1 && minus)) {  // ����� ������ �����
        temp_n.ADD_NN_N(b.ABS_Z_N());
        *this = Integral(temp_n);   // �������� ������� �������� ����� �� ������
        if (switcher == 1)
            minus = true;
    }
    else {  // ����� ����������
        // ����� ������� �� ������ ��������,
        // �������� ����� ��������� ������
        bool final_minus = minus;

        if (greater == 2) {                   // this > b
            temp_n.SUB_NN_N(b.ABS_Z_N());
            *this = Integral(temp_n);
        }
        else if (greater == 1) {              // b > this
            final_minus = b.getMinus();
            Natural b_copy(b.ABS_Z_N());
            b_copy.SUB_NN_N(temp_n);
            *this = Integral(b_copy);
        }
        else {                                // b == this | ���������� ����, ����� ������ => 0
            final_minus = false;
            *this = Integral{};
        }
        // ������������� �������������� ����
        minus = final_minus;
    }

    return *this;
}

/*  [Z - 7]
    ��������� ���������
    �������� ��������� ���� ����� �����, ��������� �� � ���������� �� ���������������/���������������.
*/

Integral& Integral::SUB_ZZ_Z(const Integral& i) {
    bool inverted_minus = !i.getMinus();
    Integral i_copy(i.getRawOdds(), i.getRawDeg(), inverted_minus);
    return ADD_ZZ_Z(i_copy);
}

/*  [Z - 8]
    ������ �������
    ������������ ����� �����
    ������ �� ������������, �������������� ��� ����������.
*/

Integral& Integral::MUL_ZZ_Z(const Integral& rhs) {
    int flag = rhs.POZ_Z_D(); //������ ����� ���� � �����
    if (deg == 0u) {
        MakeNull();
        return *this;
    }

    Natural lhs(ABS_Z_N()); // ������������� *this � ������� � ��������� � lhs(left hand side),
                            // ��� ������ ������ � trans_z_n �������� �� �������� � *this.
    lhs.MUL_NN_N(rhs.TRANS_Z_N()); // ����������� ��� ��������
    bool final_minus = false;

    if ((flag == 1 && !minus) || (flag == 2 && minus))   // ��������� �� �������� ������
        final_minus = true;

    *this = lhs;
    minus = final_minus;    // ������������� �������������� ����
    return *this;
}

/*  [Z - 9]
    ������ �������
    ������� ����� ����� ������
*/

Integral& Integral::DIV_ZZ_Z(const Integral& rhs) {
    int flag = POZ_Z_D();
    int flag_for_rhs = rhs.POZ_Z_D();

    if (flag == 0 || flag_for_rhs == 0)
        return *this;

    bool final_minus = minus;

    if (flag_for_rhs == 1)      // ������ ��������� < 0
        final_minus = !final_minus; // ��������� ���� ����������

    const Natural natural_one("1");    

    Natural rhs_n = rhs.ABS_Z_N();
    int switcher = ABS_Z_N().COMM_NN_D(rhs_n);
    if (switcher == 0) {
        *this = Integral(natural_one);
    }
    else if (switcher == 1) {
        final_minus = false;
        MakeNull();
    }
    else if (switcher == 2) {
        *this = ABS_Z_N().DIV_NN_N(rhs.ABS_Z_N());
    }

    minus = final_minus;
    //std::cout << "integral:" << *this << std::endl;
    return *this;
}

/*  [Z - 10]
    ������ ������
    ������ ������� �� ������� ����� �����
*/

Integral& Integral::MOD_ZZ_Z(const Integral& i) {
    if (ABS_Z_N().COMM_NN_D(i.ABS_Z_N()) != 2) {  // |this| <= |i|
        MakeNull();
        return *this;
    }

    bool final_minus = minus;

    if (i.POZ_Z_D() == 1)   // i < 0 -> ������ ����
        final_minus = !final_minus;

    Natural modular_other(i.ABS_Z_N());
    Natural modular_this(ABS_Z_N());
    modular_this.DIV_NN_N(modular_other);
    *this = ABS_Z_N().SUB_NN_N(modular_this.MUL_NN_N(modular_other));
    minus = final_minus;
    return *this;
}



// <! ---------- Friend ���������� ---------- !> //


Natural ABS_Z_N(const Integral& i) {
    return i.ABS_Z_N();
}

Integral TRANS_N_Z(const Natural& n) {
    return Integral{ n };
}

Natural TRANS_Z_N(const Integral& i) {
    return i.TRANS_Z_N();
}

Integral ADD_ZZ_Z(const Integral& i1, const Integral& n2) {
    Integral const_disqualification(i1);
    return const_disqualification.ADD_ZZ_Z(n2);
}

Integral SUB_ZZ_Z(const Integral& i1, const Integral& i2) {
    Integral const_disqualification(i1);
    return const_disqualification.SUB_ZZ_Z(i2);
}

Integral MUL_ZZ_Z(const Integral& i1, const Integral& i2) {
    Integral const_disqualification(i1);
    return const_disqualification.MUL_ZZ_Z(i2);
}

Integral DIV_ZZ_Z(const Integral& i1, const Integral& i2) {
    Integral const_disqualification(i1);
    return const_disqualification.DIV_ZZ_Z(i2);
}

Integral MOD_ZZ_Z(const Integral& i1, const Integral& i2) {
    Integral const_disqualification(i1);
    return const_disqualification.MOD_ZZ_Z(i2);
}
