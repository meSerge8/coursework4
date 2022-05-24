#include "gate.h"

ostream &operator<<(ostream &os, gate &g)
{
    os << "gate: " << g.name << endl
       << " type: " << g.type << endl
       << " sub-Gates: ";
       
    for (auto i : g.subGates)
        os << i->name << " ";

    os << endl;
    return os;
}