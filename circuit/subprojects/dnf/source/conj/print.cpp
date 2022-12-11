#include "conj.h"

ostream &operator<<(ostream &os, conj &c) {
    if (c.IsConstant()) {
        os << "Constanta ";
        if (c.GetConstant())
            os << "1";
        else
            os << "0";

        return os;
    }

    for (size_t i = 0; i < c.vs.size(); i++) {
        if (c.vs[i] == non)
            continue;

        string sign = c.vs[i] == pos ? "" : "-";
        os << sign + "x" + to_string(i) + " ";
    }

    return os;
}