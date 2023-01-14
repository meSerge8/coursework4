#include "Circuit.h"

vector<Gate *> Circuit::GetGates() {
    return this->gates;
}
vector<Gate *> Circuit::GetInputs() {
    return this->inGates;
}

vector<Gate *> Circuit::GetOutputs() {
    return this->outGates;
}

int Circuit::CountGates() {
    return this->gates.size();
}

int Circuit::CountInputs() {
    return this->inGates.size();
}

int Circuit::CountOutputs() {
    return this->outGates.size();
}
