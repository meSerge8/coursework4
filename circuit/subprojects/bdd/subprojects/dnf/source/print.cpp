#include "dnf_from_bdd.h"

ostream &operator<<(ostream &os, dnf_from_bdd &d)
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

string dnf_from_bdd::PrintConjunction(conjunction c)
{
    int counter = -1;
    string res, sample;

    for (auto var : c)
    {
        counter++;
        if (var == none)
            continue;

        sample = names.at(counter) + " ";
        if (var == negative)
            sample = "-" + sample;

        res += sample;
    }

    return res;
}

ostream &operator<<(ostream &os, list<dnf_from_bdd> &dnfs)
{
    os << "========== dnfs ==========" << endl
       << endl;

    for (auto d : dnfs)
        os << d << endl;

    os << endl
       << "========== dnfs end ==========" << endl;

    return os;
}