#include "TestabilityFooBuilder.h"

vertex *TestabilityFooBuilder::buildVertex(Gate *g, vector<vertex *> *vs) {
    vector<vertex *> subvertices = getSubvertices(g, vs);

    switch (g->GetType()) {
        case NOT:
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

vector<vertex *> TestabilityFooBuilder::getSubvertices(Gate *g, vector<vertex *> *vs) {
    vector<Gate *>::iterator
        beg = this->gates.begin(),
        end = this->gates.end();

    vector<vertex *> result;

    for (Gate *predGate : g->GetPredecessors()) {
        auto itr = find(beg, end, predGate);
        if (itr == end) {
            throw logic_error("predGate not found");
        }

        int i = itr - beg;
        result.push_back(vs->at(i));
    }

    return result;
}
