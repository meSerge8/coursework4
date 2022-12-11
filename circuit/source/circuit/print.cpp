#include "circuit.h"

ostream &operator<<(ostream &os, circuit &circ) {
    os << "========== circuit ==========" << endl;
    for (auto gate : circ.gates) {
        // PrintGate(gate, os);
    }
    os << "========== circuit end ==========" << endl;
    return os;
}

list<string> circuit::GetOutNames() {
    list<string> res;
    for (auto gate : outputs)
        res.push_back(gate->name);
    return res;
}

void circuit::PrintMap(map<string, u_int> *nim) {
    for (auto it : *nim)
        cout << it.first << "\t" << it.second << endl;
}
