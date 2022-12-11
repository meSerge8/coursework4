#include "bddExporter.h"

BddExporterFromInput::BddExporterFromInput(list<gate *> gates) {
    for (gate *i : gates) {
        this->gates.push_back(i);
    }
}

bdd *BddExporterFromInput::Export() {
    bdd *result = new bdd();
    this->manager = result->GetManager();
    this->gates = sortTopological();
    auto allSubgates = getAllSubgates();

    for (gate *g : this->gates) {
        auto v = buildVertex(g);
        this->vertices.push_back(v);
        if (find(allSubgates.begin(), allSubgates.end(), g) == allSubgates.end()) {
            result->AddRoot(v, g->name);
        }
    }

    return result;
}

// Kahn’s algorithm for Topological Sorting
vector<gate *> BddExporterFromInput::sortTopological() {
    vector<int> in_degrees = initInDegrees();
    queue<int> q = initQueue(in_degrees);

    int countVisited = 0;
    vector<gate *> result;

    while (!q.empty()) {
        countVisited++;
        int frontIdx = q.front();
        q.pop();
        auto frontGate = this->gates[frontIdx];
        result.push_back(frontGate);

        for (size_t i = 0; i < this->gates.size(); i++) {
            auto gBegin = this->gates[i]->subGates.begin();
            auto gEnd = this->gates[i]->subGates.end();

            if (find(gBegin, gEnd, frontGate) == gEnd) {
                continue;
            }

            in_degrees[i]--;
            if (in_degrees[i] != 0) {
                continue;
            }

            q.push(i);
        }
    }

    if (this->gates.size() != countVisited) {
        throw logic_error("Sorting failed: there is a cycle in graph");
    }

    return result;
}

vector<gate *> BddExporterFromInput::getAllSubgates() {
    vector<gate *> result;

    for (auto g : this->gates) {
        for (auto subGate : g->subGates) {
            if (find(result.begin(), result.end(), subGate) == result.end()) {
                result.push_back(subGate);
            }
        }
    }

    return result;
}

vector<int> BddExporterFromInput::initInDegrees() {
    size_t len = this->gates.size();
    vector<int> in_degrees(len, 0);

    for (size_t i = 0; i < len; i++) {
        in_degrees[i] = this->gates[i]->subGates.size();
    }

    return in_degrees;
}

queue<int> BddExporterFromInput::initQueue(vector<int> in_degrees) {
    queue<int> q;
    for (int i = 0; i < this->gates.size(); i++) {
        if (in_degrees[i] == 0) {
            q.push(i);
        }
    }
    return q;
}

vertex *BddExporterFromInput::buildVertex(gate *g) {
    auto subvertices = getSubvertices(g);

    switch (g->type) {
        case NOT:
            if (subvertices.size() != 1) {
                throw logic_error("expected only one arg");
            }
            return this->manager->Negate(subvertices.front());
        case INPUT:
            return this->manager->CreateVertex(g->name);
        case DFF:
            return this->manager->CreateVertex(g->name);
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

list<vertex *> BddExporterFromInput::getSubvertices(gate *g) {
    list<vertex *> result;
    auto itrBegin = this->gates.begin();
    auto itrEnd = this->gates.end();

    for (gate *subGate : g->subGates) {
        auto itr = find(itrBegin, itrEnd, subGate);
        if (itr == itrEnd) {
            throw logic_error("subGate not found");
        }

        int i = itr - itrBegin;
        result.push_back(this->vertices[i]);
    }

    return result;
}