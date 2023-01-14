#include "Gate.h"

ostream &operator<<(ostream &os, Gate &g) {
    os << g.GetName() << " = " << printType(g.GetType()) << "(";

    for (Gate *g : g.GetPredecessors()) {
        os << g->GetName() << " ";
    }

    os << ") -- ";

    for (Gate *g : g.GetSuccessors()) {
        os << g->GetName() << " ";
    }

    os << endl;

    return os;
}

string printType(GateType t) {
    switch (t) {
        case NOT:
            return "NOT";
        case INPUT:
            return "INPUT";
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