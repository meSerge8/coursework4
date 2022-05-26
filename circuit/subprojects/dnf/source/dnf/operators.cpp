#include "dnf.h"

dnf dnf::NEG()
{
    dnf res(varNum, true);

    for (conj &c : cs)
    {
        res = res.AND({varNum, c.Negate()});
    }

    return res;
}

dnf dnf::AND(const dnf &d)
{
    if (varNum != d.varNum)
        throw invalid_argument("dnfs must be the same size");

    dnf res(varNum);

    for (conj cx : cs)
        for (conj cy : d.cs)
            res.AddConjunction(cx * cy);

    return res;
}

// dnf dnf::NAND(const dnf &y)
// {
//     // auto negX = x.negative;
//     // auto negY = this->negative;

//     // return negY->OR(*negX);
//     return y;
// }

// // not tested
// dnf dnf::OR(const dnf &x)
// {
//     vector<conj> resCS(cs);
//     resCS.insert(resCS.end(), x.cs.begin(), x.cs.end());

//     dnf res(varNum, resCS);
//     res.Reduce();

//     return res;
// }

// dnf dnf::NOR(const dnf &x)
// {
//     // auto negX = x.negative;
//     // auto negY = this->negative;
//     // auto res = negY->AND(*negX);
//     // return res;
//     return x;
// }

// dnf dnf::XOR(const dnf &x)
// {
//     // dnf x(2);
//     return x;
// }

// dnf dnf::NXOR(const dnf &x)
// {
//     // dnf x(2);
//     return x;
// }
