#include "BddExporter.h"

bdd *BddExporterFromOutput::Export(Circuit *c) {
    bdd *result = new bdd();
    this->gateVertMap = new map<string, vertex *>();
    this->manager = result->GetManager();

    for (auto outGate : c->GetOutputs()) {
        auto root = makeVertex(outGate);
        result->AddRoot(root, outGate->GetName());
    }

    return result;
}

vertex *BddExporterFromOutput::makeVertex(Gate *gate) {
    auto it = this->gateVertMap->find(gate->GetName());
    if (it != this->gateVertMap->end()) {
        return it->second;
    }

    vector<vertex *> subVs;
    for (auto subGate : gate->GetPredecessors()) {
        auto sv = makeVertex(subGate);
        subVs.push_back(sv);
    }

    auto newVertex = performOperation(gate, subVs);
    this->gateVertMap->insert(make_pair(gate->GetName(), newVertex));

    return newVertex;
}

vertex *BddExporterFromOutput::performOperation(Gate *gate, vector<vertex *> subgs) {
    switch (gate->GetType()) {
        case NOT:
            if (subgs.size() != 1) throw logic_error("expected only one arg");
            return this->manager->Negate(subgs.front());

        case INPUT:
            return this->manager->CreateVertex(gate->GetName());
        case AND:
            return this->manager->AND(subgs);

        case OR:
            return this->manager->OR(subgs);

        case NAND:
            return this->manager->NAND(subgs);

        case NOR:
            return this->manager->NOR(subgs);

        case XOR:
            return this->manager->XOR(subgs);

        case NXOR:
            return this->manager->NXOR(subgs);

        default:
            throw logic_error("Can't deduce what to do");
    }
}
