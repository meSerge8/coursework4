#include "dnf.h"

ostream &operator<<(ostream &os, dnf &d)
{
    auto conjs = d.conjuctions;
    os << "----- dnf -----" << endl
       << "amount of conjuctions: " << to_string(conjs.size()) << endl
       << endl;

    for (auto conj : conjs)
        os << d.PrintConjunction(conj) << endl;

    os << "----- dnf end -----" << endl;

    return os;
}

string dnf::PrintConjunction(conjunction c)
{
    if (names.empty())
        for (u_int i = 0; i < varNum; i++)
            names.push_back("x" + to_string(i));

    int counter = -1;
    string res, sample;

    for (var var : c.GetVectorCopy())
    {
        counter++;
        if (var == non)
            continue;

        sample = names.at(counter) + " ";
        if (var == neg)
            sample = "-" + sample;

        res += sample;
    }

    return res;
}

ostream &operator<<(ostream &os, list<dnf> &dnfs)
{
    os << "========== dnfs ==========" << endl
       << endl;

    for (auto d : dnfs)
        os << d << endl;

    os << endl
       << "========== dnfs end ==========" << endl;

    return os;
}