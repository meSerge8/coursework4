#include "conjunction.h"

bool *conjunction::GetConstant()
{
    return constanta;
}

void conjunction::SetConstant(bool c)
{
    if (constanta != nullptr)
        delete constanta;

    constanta = new bool(c);

    for (auto &v : varVect)
        v = non;
}

bool conjunction::IsConstant()
{
    return (constanta != nullptr) ? true : false;
}

size_t conjunction::size()
{
    return varVect.size();
}

vector<var> conjunction::GetVectorCopy()
{
    return varVect;
}
