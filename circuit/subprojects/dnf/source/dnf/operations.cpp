#include "dnf.h"

int dnf::GetVarNum()
{
    return varNum;
}

bool dnf::IsConstant()
{
    if (cs.size() == 0)
        throw logic_error("bad dnf");

    if (cs.size() > 1)
        return false;

    return cs[0].IsConstant();
}

bool dnf::GetConstant()
{
    if (cs.size() != 1)
        throw logic_error("cs wrong size");

    auto c = cs[0];

    if (not c.IsConstant())
        throw logic_error("Cant get constant");

    return *c.GetConstant();
}

void dnf::SetConstant(bool c)
{
    cs.clear();
    cs.push_back({varNum, c});
}

void dnf::AddConjunction(conj c)
{
    if (varNum != c.Size())
        throw logic_error("Wrong number of variables");

    cs.push_back(c);

    Reduce();
}

vector<conj> dnf::GetConjunctions()
{
    return cs;
}

void dnf::SetNames(vector<string> l)
{
    if (varNum != l.size())
        throw logic_error("Wrong number of variables");

    names = l;
}
