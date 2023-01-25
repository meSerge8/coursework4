#include "DnfExporter.h"

DnfExporterFromBDD::DnfExporterFromBDD(bdd* b, vector<Gate*> inGates) {
    this->b = b;
    this->manager = this->b->GetManager();
    this->names = GetNames(inGates);
    this->varNum = this->names.size();
}

vector<dnf> DnfExporterFromBDD::Export() {
    vector<dnf> result;

    for (vertex* root : this->b->GetRoots()) {
        dnf d = buildRootDNF(root);
        d.SetNames(this->names);
        result.push_back(d);
    }

    return result;
}

dnf DnfExporterFromBDD::ExportVertex(vertex* v) {
    dnf d = buildRootDNF(v);
    d.SetNames(this->names);
    return d;
}

dnf DnfExporterFromBDD::buildRootDNF(vertex* root) {
    this->vertices = {};
    this->inDegrees = {};
    this->q = {};
    this->dnfs = {};

    addVertexRecursive(root);
    sortTopological();

    for (vertex* v : this->vertices) {
        if (v->IsTerminal()) {
            this->dnfs.push_back(buildTerminal(v));
        } else {
            this->dnfs.push_back(buildNonTerminal(v));
        }
    }

    return this->dnfs.back();
}

void DnfExporterFromBDD::addVertexRecursive(vertex* v) {
    if (containsVertex(&this->vertices, v)) {
        return;
    }

    this->vertices.push_back(v);

    if (v->IsTerminal()) {
        this->inDegrees.push_back(0);
        this->q.push(v);
    } else {
        this->inDegrees.push_back(2);
        addVertexRecursive(v->GetHigh());
        addVertexRecursive(v->GetLow());
    }
}

// Kahn’s algorithm for Topological Sorting
void DnfExporterFromBDD::sortTopological() {
    vector<vertex*> sorted;
    int countVisited = 0;

    while (!this->q.empty()) {
        countVisited++;
        vertex* v = q.front();
        q.pop();
        sorted.push_back(v);

        for (size_t i = 0; i < this->vertices.size(); i++) {
            auto highV = this->vertices[i]->GetHigh();
            auto lowV = this->vertices[i]->GetLow();

            if ((v != highV) && (v != lowV)) {
                continue;
            }

            this->inDegrees[i]--;

            if (this->inDegrees[i] == 0) {
                q.push(this->vertices[i]);
            }
        }
    }

    if (this->vertices.size() != countVisited) {
        throw logic_error("Sorting failed: there is a cycle in graph");
    }

    this->vertices = sorted;
}

dnf DnfExporterFromBDD::buildTerminal(vertex* v) {
    dnf d(this->varNum, true);

    if (v->GetVariable() == this->manager->GetOneVariable()) {
        d.SetConstant(true);
    } else {
        d.SetConstant(false);
    }

    return d;
}

dnf DnfExporterFromBDD::buildNonTerminal(vertex* v) {
    auto f = find(this->names.begin(), this->names.end(), v->GetVariable()->value);
    int i = f - this->names.begin();

    conj cPos(this->varNum, false);
    conj cNeg(this->varNum, false);

    cPos.Set(i, pos, false);
    cNeg.Set(i, neg, false);

    dnf dPos(this->varNum, {cPos});
    dnf dNeg(this->varNum, {cNeg});

    auto dHigh = findDnfByVertex(v->GetHigh());
    auto dLow = findDnfByVertex(v->GetLow());

    auto dPosPart = dPos.AND(dHigh);
    auto dNegPart = dNeg.AND(dLow);

    dnf res = dNegPart.OR(dPosPart);
    return res;
}

dnf DnfExporterFromBDD::findDnfByVertex(vertex* v) {
    auto begin = this->vertices.begin();
    auto end = this->vertices.end();

    auto itr = find(begin, end, v);
    if (itr == end) {
        throw logic_error("Vertex not found");
    }

    int index = itr - begin;

    return this->dnfs[index];
}

bool containsVertex(vector<vertex*>* gs, vertex* g) {
    return find(gs->begin(), gs->end(), g) != gs->end();
};