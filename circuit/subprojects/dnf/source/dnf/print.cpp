#include "dnf.h"

ostream &operator<<(ostream &os, dnf &d) {
    auto conjs = d.cs;
    os << "----- dnf -----" << endl
       << "amount of conjuctions: " << to_string(conjs.size()) << endl
       << endl;

    if (d.IsConstant())
        cout << d.GetConstant() << endl;
    else
        for (auto conj : conjs)
            os << d.PrintConjunction(conj) << endl;

    os << "----- dnf end -----" << endl;

    return os;
}

string dnf::PrintConjunction(conj c) {
    if (c.IsConstant())
        return c.GetConstant() ? "1" : "0";

    string res;
    for (int i = 0; i < c.Size(); i++) {
        if (c.Get(i) == non)
            continue;

        string name = names.size() ? names[i] : "x" + to_string(i);

        string sign = c.Get(i) == pos ? "" : "-";
        res += sign + name + " ";
    }

    return res;
}

ostream &operator<<(ostream &os, list<dnf> &dnfs) {
    os << "========== dnfs ==========" << endl
       << endl;

    for (auto d : dnfs)
        os << d << endl;

    os << endl
       << "========== dnfs end ==========" << endl;

    return os;
}