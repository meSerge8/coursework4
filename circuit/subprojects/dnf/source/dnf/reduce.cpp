#include "dnf.h"

dnf dnf::Reduce()
{
    vector<conj> vs = shrinkConstants();
    if (vs.size() == 1)
        return {varNum, vs};

    while (true)
    {
        if (absorb(&vs))
            continue;

        if (glue(&vs))
            continue;

        break;
    }

    return {varNum, vs};
}

vector<conj> dnf::shrinkConstants()
{
    if (cs.size() == 1)
        return cs;

    vector<conj> vs;
    for (auto itr = cs.begin(); itr != cs.end(); itr++)
    {
        if (not itr->IsConstant())
        {
            vs.push_back((*itr));
            continue;
        }

        if (not *itr->GetConstant())
            continue;

        return {{varNum, true}};
    }

    return vs;
}

bool dnf::absorb(vector<conj> *vs)
{
    for (auto itr = vs->begin(); itr != vs->end(); itr++)
    {
        for (auto jtr = next(itr, 1); jtr != vs->end(); jtr++)
        {

        }
    }
}

bool dnf::glue(vector<conj> *)
{
    return true;
}
