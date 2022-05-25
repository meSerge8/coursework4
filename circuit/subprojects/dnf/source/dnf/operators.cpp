#include "dnf.h"

// (a v b) * 0
// (a v b) * 1

// 0va
// 1va

// 0v0
// 0v1
// 1v0
// 1v1

dnf dnf::AND(const dnf &d)
{
    if (varNum != d.varNum)
    {
        throw invalid_argument("dnfs must be the same size");
    }

    if (constanta != nullptr)
        return *constanta ? d : *this;

    if (d.constanta != nullptr)
        return *d.constanta ? *this : d;

    dnf res(varNum);

    for (auto cx : cs)
        for (auto cy : d.cs)
            res.AddConjunction(cx * cy);

    res.Reduce();
    return res;
}

dnf dnf::NAND(const dnf &y)
{
    // auto negX = x.negative;
    // auto negY = this->negative;

    // return negY->OR(*negX);
    return y;
}

// not tested
dnf dnf::OR(const dnf &x)
{
    vector<conj> resCS(cs);
    resCS.insert(resCS.end(), x.cs.begin(), x.cs.end());

    dnf res(varNum, resCS);
    res.Reduce();

    return res;
}

dnf dnf::NOR(const dnf &x)
{
    // auto negX = x.negative;
    // auto negY = this->negative;
    // auto res = negY->AND(*negX);
    // return res;
    return x;
}

dnf dnf::XOR(const dnf &x)
{
    // dnf x(2);
    return x;
}

dnf dnf::NXOR(const dnf &x)
{
    // dnf x(2);
    return x;
}

// not tested
dnf dnf::NEG()
{
    dnf res(varNum, 1);

    for (conj &c : cs)
    {
        int x = varNum;
        dnf d(x, c.Negate());
        res = res.AND(d);
    }

    return res;
}