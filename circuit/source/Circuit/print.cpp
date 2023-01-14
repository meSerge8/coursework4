#include "Circuit.h"

ostream &operator<<(ostream &os, Circuit &c) {
    os << "Input gates: " << c.CountInputs() << endl
       << "Output gates: " << c.CountOutputs() << endl
       << "Total gates: " << c.CountGates() << endl
       << "--------------------------------------" << endl;

    for (Gate *g : c.GetGates()) {
        os << *g;
    }

    return os;
}