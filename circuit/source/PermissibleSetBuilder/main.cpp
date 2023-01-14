#include "PermissibleSetBuilder.h"

PermissibleSetBuilder::PermissibleSetBuilder(Circuit *c) {
    this->c = c;
}

vector<string> PermissibleSetBuilder::DoMagic(string gateName) {
    findPole(gateName);
    isolateSv();

    tuple<dnf, dnf> D1_D0 = build_D1_D0();

    dnf D1 = get<0>(D1_D0),
        D0 = get<1>(D1_D0);

    return buildPermissibleSet(D1, D0);
}

void PermissibleSetBuilder::findPole(string gateName) {
    this->pole = FindByName(c->GetGates(), gateName);
    if (this->pole == nullptr) {
        throw logic_error("pole not found");
    }
}

void PermissibleSetBuilder::isolateSv() {
    vector<Gate *> thisOuts = this->c->GetOutputs();
    isolateOutGates(this->pole, &thisOuts);

    for (Gate *outGate : this->outGates) {
        isolateGates(outGate);
    }

    this->gates = Gate::sortTopological(this->gates);

    for (Gate *g : this->gates) {
        if (g->GetType() == INPUT) {
            this->inGates.push_back(g);
        }
    }
}

void PermissibleSetBuilder::isolateGates(Gate *g) {
    if (contains(&this->gates, g)) {
        return;
    }

    this->gates.push_back(g);

    for (Gate *predGate : g->GetPredecessors()) {
        isolateGates(predGate);
    }
}

void PermissibleSetBuilder::isolateOutGates(Gate *g, vector<Gate *> *outGates) {
    if (contains(outGates, g)) {
        if (contains(&this->outGates, g)) {
            return;
        }
        this->outGates.push_back(g);
    }

    for (Gate *succGate : g->GetSuccessors()) {
        isolateOutGates(succGate, outGates);
    }
}
