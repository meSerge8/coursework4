#include "dnf.h"

dnf::dnf(int variableNumber, bool constant)
{
    varNum = variableNumber;
    constanta = new bool(constant);
}

dnf::dnf(int variableNumber, vector<string> variableNames, bool constant)
    : dnf(variableNumber, constant)
{
    SetNames(variableNames);
}

dnf::dnf(const dnf &orig)
{
    varNum = orig.varNum;
    cs = orig.cs;
    names = orig.names;
    constanta = orig.constanta != nullptr
                    ? new bool(*orig.constanta)
                    : constanta = nullptr;
}

dnf::~dnf()
{
    if (constanta != nullptr)
        delete constanta;
}
