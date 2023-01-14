#include "Gate.h"

string Gate::GetName() {
    return this->name;
}

GateType Gate::GetType() {
    return this->type;
}

void Gate::SetType(GateType t) {
    this->type = t;
}

vector<Gate *> Gate::GetPredecessors() {
    return this->predecessors;
}

vector<Gate *> Gate::GetSuccessors() {
    return this->successors;
}

void Gate::AddPredecessor(Gate *g) {
    if (not contains(&this->predecessors, g)) {
        this->predecessors.push_back(g);
    }
}

void Gate::AddSuccessors(Gate *g) {
    if (not contains(&this->successors, g)) {
        this->successors.push_back(g);
    }
}

int Gate::CountPredecessors() {
    return this->predecessors.size();
}

int Gate::CountSuccessors() {
    return this->successors.size();
}

Gate *FindByName(vector<Gate *> gates, string gateName) {
    for (Gate *g : gates) {
        if (g->GetName() == gateName) {
            return g;
        }
    }
    return nullptr;
}

vector<string> GetNames(vector<Gate *> gs) {
    vector<string> names;
    for (auto g : gs) {
        names.push_back(g->GetName());
    }
    return names;
}

bool contains(vector<Gate *> *gs, Gate *g) {
    return find(gs->begin(), gs->end(), g) != gs->end();
};