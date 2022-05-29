#include "conj.h"

bool conj::GetConstant()
{
    return constanta;
}

void conj::SetConstant(bool c)
{
    isConstanta = true;
    constanta = c;

    for (auto &v : vs)
        v = non;
}

bool conj::IsConstant()
{
    return isConstanta;
}

size_t conj::Size()
{
    return vs.size();
}

vector<var> conj::GetVectorCopy()
{
    return vs;
}
