#include "conj.h"

bool *conj::GetConstant()
{
    return constanta;
}

void conj::SetConstant(bool c)
{
    if (constanta != nullptr)
        delete constanta;

    constanta = new bool(c);

    for (auto &v : vs)
        v = non;
}

bool conj::IsConstant()
{
    return constanta != nullptr;
}

size_t conj::Size()
{
    return vs.size();
}

vector<var> conj::GetVectorCopy()
{
    return vs;
}
