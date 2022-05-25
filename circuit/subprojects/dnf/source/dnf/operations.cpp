#include "dnf.h"

bool *dnf::GetConstant()
{
    return constanta;
}

void dnf::SetConstant(bool c)
{
    if (constanta != nullptr)
        delete constanta;

    constanta = new bool(c);

    cs.clear();
}

bool dnf::IsConstant()
{
    return constanta != nullptr;
}

void dnf::AddConjunction(conj c)
{
    if (c.Size() != varNum)
        throw logic_error("Wrong number of variables");

    if (c.IsConstant())
        if (not *c.GetConstant())
            return;

    cs.push_back(c);

    if (constanta != nullptr)
    {
        delete constanta;
        constanta = nullptr;
    }

    // Reduce();
}

vector<conj> dnf::GetConjunctions()
{
    return cs;
}

void dnf::SetNames(vector<string> l)
{
    if (l.size() != varNum)
        throw logic_error("Wrong number of variables");

    names = l;
}
