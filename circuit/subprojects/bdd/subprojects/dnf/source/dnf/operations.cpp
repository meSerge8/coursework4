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

    conjuctions.clear();
}

bool dnf::IsConstant()
{
    return (constanta != nullptr) ? true : false;
}

void dnf::AddConjunction(conjunction c)
{
    if (c.size() != varNum)
        throw logic_error("Wrong number of variables");

    conjuctions.push_back(c);
}

list<conjunction> dnf::GetConjunctions()
{
    return conjuctions;
}

void dnf::SetNames(vector<string> l)
{
    if (l.size() != varNum)
        throw logic_error("Wrong number of variables");

    names = l;
}

