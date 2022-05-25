#include "conj.h"

conj::conj()
{
    constanta = new bool(0);
}

conj::conj(vector<var> initVs)
{
    vs = initVs;
}

conj::conj(int size) : vs(size)
{
    for (var &v : vs)
        v = non;
}

conj::conj(int size, bool constanta) : conj(size)
{
    this->constanta = new bool(constanta);
}

// conj::conj(initializer_list<var> l) : vs(l){};

conj::conj(const conj &copy) : vs(copy.vs)
{
    constanta = copy.constanta != nullptr
                    ? new bool(*copy.constanta)
                    : nullptr;
}

conj::~conj()
{
    if (constanta != nullptr)
        delete constanta;
}
