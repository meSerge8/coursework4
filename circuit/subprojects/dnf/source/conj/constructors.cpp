#include "conj.h"

conj::conj()
{
    isConstanta = false;
    constanta = false;
}

conj::conj(vector<var> initVs)
{
    isConstanta = false;
    constanta = false;
    vs = initVs;
}

conj::conj(int size, bool cons) : vs(size)
{
    if (size == 0)
        throw logic_error("size must not be zero");
    for (var &v : vs)
        v = non;

    isConstanta = true;
    constanta = cons;
}

conj::conj(const conj &copy)
{
    vs = copy.vs;
    isConstanta = copy.isConstanta;
    constanta = copy.constanta;
}
