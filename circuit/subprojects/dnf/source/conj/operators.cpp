#include "conj.h"

conj conj::operator*(const conj &c)
{
    if (vs.size() != c.vs.size())
    {
        throw invalid_argument("conjunctions must be the same size");
    }

    if (constanta != nullptr)
        return *constanta ? c : *this;

    if (c.constanta != nullptr)
        return *c.constanta ? *this : c;

    conj res(vs.size());

    for (int i = 0; i < vs.size(); i++)
    {
        int z = vs[i] | c.vs[i];

        if (z == 0b11)
            return {(int)vs.size(), 0};

        res.Set(i, var(z));
    }

    return res;
}

vector<conj> conj::Negate()
{
    if (IsConstant())
    {
        return {{vs.size(), not *GetConstant()}};
    }

    vector<conj> res;

    for (int i = 0; i < vs.size(); i++)
    {
        int v = vs[i] xor 0b11;

        if (v == 0b11)
            continue;

        conj cj(vs.size());
        cj.Set(i, var(v));
        res.push_back(cj);
    }

    return res;
}

bool conj::operator==(const conj &c)
{
    if ((constanta == nullptr) != (c.constanta == nullptr))
        return false;

    if (IsConstant())
        return *constanta == *c.constanta;

    return vs == c.vs;
}

void conj::Set(int idx, var v)
{
    vs[idx] = v;

    if (v != non)
    {
        if (constanta != nullptr)
        {
            delete constanta;
            constanta = nullptr;
        }
        return;
    }

    for (var vr : vs)
        if (vr != non)
            return;

    constanta = new bool(false);
}

var conj::Get(int idx)
{
    return vs[idx];
}

// conj conj::Reduce(const conj &conj)
// {
//     return conj;
// }