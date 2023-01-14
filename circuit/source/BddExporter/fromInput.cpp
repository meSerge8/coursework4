#include "BddExporter.h"

bdd *BddExporterFromInput::Export(Circuit *c) {
    this->c = c;
    bdd *result = new bdd();
    this->manager = result->GetManager();

    for (Gate *g : this->c->GetGates()) {
        vertex *v = buildVertex(g);
        this->vertices.push_back(v);

        auto outs = c->GetOutputs();
        if (contains(&outs, g)) {
            result->AddRoot(v, g->GetName());
        }
    }

    return result;
}

vertex *BddExporterFromInput::buildVertex(Gate *g) {
    auto subvertices = getSubvertices(g);

    switch (g->GetType()) {
        case NOT:
            if (subvertices.size() != 1) {
                throw logic_error("expected only one arg");
            }
            return this->manager->Negate(subvertices.front());
        case INPUT:
            return this->manager->CreateVertex(g->GetName());
        case AND:
            return this->manager->AND(subvertices);
        case OR:
            return this->manager->OR(subvertices);
        case NAND:
            return this->manager->NAND(subvertices);
        case NOR:
            return this->manager->NOR(subvertices);
        case XOR:
            return this->manager->XOR(subvertices);
        case NXOR:
            return this->manager->NXOR(subvertices);
        default:
            throw logic_error("Can't deduce what to do");
    }
}

vector<vertex *> BddExporterFromInput::getSubvertices(Gate *g) {
    vector<vertex *> result;
    auto gs = this->c->GetGates();
    auto itrBegin = gs.begin();
    auto itrEnd = gs.end();

    for (Gate *subGate : g->GetPredecessors()) {
        auto itr = find(itrBegin, itrEnd, subGate);
        if (itr == itrEnd) {
            throw logic_error("subGate not found");
        }

        int i = itr - itrBegin;
        result.push_back(this->vertices[i]);
    }

    return result;
}