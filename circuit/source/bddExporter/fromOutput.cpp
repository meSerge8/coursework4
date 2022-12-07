#include "bddExporter.h"

BddExporterFromOutput::BddExporterFromOutput(list<gate *> outGates) {
    this->outGates = outGates;
}

bdd BddExporterFromOutput::Export() {
    std::cout << *this->outGates.begin() << endl;
    bdd result;
    this->gateVertMap = new map<string, vertex *>();
    this->manager = result.GetManager();

    for (auto outGate : this->outGates) {
        auto root = makeVertex(outGate);
        result.AddRoot(root, outGate->name);
    }

    return result;
}

vertex *BddExporterFromOutput::makeVertex(gate *gate) {
    auto it = this->gateVertMap->find(gate->name);
    if (it != this->gateVertMap->end()) {
        return it->second;
    }

    list<vertex *> subVs;
    for (auto subGate : gate->subGates) {
        auto sv = makeVertex(subGate);
        subVs.push_back(sv);
    }

    auto newVertex = performOperation(gate, subVs);
    this->gateVertMap->insert(make_pair(gate->name, newVertex));

    return newVertex;
}

vertex *BddExporterFromOutput::performOperation(gate *gate, list<vertex *> subgs) {
    switch (gate->type) {
        case NOT:
            if (subgs.size() != 1) throw logic_error("expected only one arg");
            return this->manager->Negate(subgs.front());

        case INPUT:
            return this->manager->CreateVertex(gate->name);

        case DFF:
            return this->manager->CreateVertex(gate->name);

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
