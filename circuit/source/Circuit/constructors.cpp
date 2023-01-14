#include "Circuit.h"

Circuit::Circuit(
    vector<Gate *> gates,
    vector<Gate *> inGates,
    vector<Gate *> outGates) {
    this->gates = gates;
    this->inGates = inGates;
    this->outGates = outGates;
}

Circuit::~Circuit() {
    for (Gate *g : gates)
        delete g;
}
