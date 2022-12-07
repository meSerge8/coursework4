#include "gate.h"

ostream &operator<<(ostream &os, gate &g) {
    os << "gate: " << g.name << endl
       << " type: " << printType(g.type) << endl
       << " sub-Gates: ";

    for (auto i : g.subGates)
        os << i->name << " ";

    os << endl;
    return os;
}

string printType(gateType t) {
    switch (t) {
        case NOT:
            return "NOT";
        case INPUT:
            return "INPUT";
        case DFF:
            return "DFF";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case NAND:
            return "NAND";
        case NOR:
            return "NOR";
        case XOR:
            return "XOR";
        case NXOR:
            return "NXOR";
        default:
            throw logic_error("Can't deduce what to do");
    }
}