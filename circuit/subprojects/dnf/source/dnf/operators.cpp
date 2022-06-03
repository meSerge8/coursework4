#include "dnf.h"

dnf dnf::NEG()
{
    dnf res(varNum, true);

    for (conj c : cs)
    {
        auto negs = c.Negate();
        dnf neg(varNum, negs);
        dnf res2 = res.AND(neg);
        res = res2;
    }
   
    return res;
}

dnf dnf::AND(const dnf &d)
{
    dnf res(varNum);

    for (conj cx : cs)
    {
        for (conj cy : d.cs)
        {
            auto mul = cx * cy;
            res.AddConjunction(mul);
        }
    }

    return res;
}

dnf dnf::OR(const dnf &x)
{
    dnf res(*this);

    for (auto &c : x.cs)
        res.AddConjunction(c);

    return res;
}

dnf dnf::NAND(const dnf &x)
{
    dnf a = AND(x);
    dnf b = a.NEG();
    return b;
}

dnf dnf::NOR(const dnf &x)
{
    return OR(x).NEG();
}

dnf dnf::XOR(const dnf &x)
{
    return AND(x).NEG().AND(OR(x));
}

dnf dnf::NXOR(const dnf &x)
{
    return AND(x).OR(OR(x).NEG());
}
