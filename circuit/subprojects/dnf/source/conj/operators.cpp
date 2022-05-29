#include "conj.h"

conj conj::operator*(const conj &c)
{
    if (vs.size() != c.vs.size())
        throw invalid_argument("conjunctions must be the same size:" + to_string(vs.size()) + "|" + to_string(c.vs.size()));

    if (isConstanta)
        return constanta != 0 ? c : *this;

    if (c.isConstanta)
        return c.constanta != 0 ? *this : c;

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
        vector<conj> res;
        conj r(vs.size(), not GetConstant());
        res.push_back(r);
        return res;
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
    if (isConstanta != c.isConstanta)
        return false;

    if (IsConstant())
        return constanta == c.constanta;

    return vs == c.vs;
}

void conj::Set(int idx, var v)
{
    vs[idx] = v;

    if (v != non)
    {
        isConstanta = false;
        return;
    }

    for (var vr : vs)
        if (vr != non)
            return;

    constanta = false;
}

var conj::Get(int idx)
{
    return vs[idx];
}