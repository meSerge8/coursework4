#include "TestabilityFooBuilder.h"

void TestabilityFooBuilder::isolateSv() {
    vector<Gate *> circuitOutGates = this->c->GetOutputs();
    isolateOutGates(this->pole, &circuitOutGates);

    for (Gate *outGate : this->outGates) {
        isolateGates(outGate);
    }

    this->gates = sortTopological(this->gates);

    for (Gate *g : this->gates) {
        if (g->GetType() == INPUT) {
            this->inGates.push_back(g);
        }
    }
}

void TestabilityFooBuilder::isolateOutGates(Gate *g, vector<Gate *> *circuitOutGates) {
    if (contains(circuitOutGates, g)) {
        if (contains(&this->outGates, g)) {
            return;
        }
        this->outGates.push_back(g);
    }

    for (Gate *succGate : g->GetSuccessors()) {
        isolateOutGates(succGate, circuitOutGates);
    }
}

void TestabilityFooBuilder::isolateGates(Gate *g) {
    if (contains(&this->gates, g)) {
        return;
    }

    this->gates.push_back(g);

    for (Gate *predGate : g->GetPredecessors()) {
        isolateGates(predGate);
    }
}

vector<Gate *> TestabilityFooBuilder::GetInputs() {
    return this->inGates;
}

int TestabilityFooBuilder::CountInputs() {
    return this->inGates.size();
}