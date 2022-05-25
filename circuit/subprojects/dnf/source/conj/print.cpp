#include "conj.h"

ostream &operator<<(ostream &os, conj &c)
{
    if (c.IsConstant())
    {
        os << *c.GetConstant() ? "1" : "0";
    }

    for (size_t i = 0; i < c.vs.size(); i++)
    {
        if (c.vs[i] == non)
        {
            continue;
        }
        string sign = c.vs[i] == pos ? "" : "-";
        os << sign + "x" + to_string(i) + " ";
    }

    return os;
}