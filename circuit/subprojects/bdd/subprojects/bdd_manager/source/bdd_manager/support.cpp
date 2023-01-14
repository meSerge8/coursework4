#include "bdd_manager.h"

vector<variable *> bdd_manager::GetVariables() {
    vector<variable *> res = vars;
    res.push_back(zeroVar);
    res.push_back(oneVar);
    return res;
}

vector<variable *> bdd_manager::GetVariablesNonTerm() {
    vector<variable *> result;
    for (variable *v : this->vars) {
        result.push_back(v);
    }
    return result;
}

variable *bdd_manager::GetOneVariable() {
    return this->oneVar;
}

variable *bdd_manager::GetZeroVariable() {
    return this->zeroVar;
}

list<vertex *> BuildVertexList(vertex *rootVert) {
    list<vertex *> res;
    bool m = rootVert->GetMark();
    BuildVertexList_core(rootVert, &res, not m);
    return res;
}

void BuildVertexList_core(vertex *v, list<vertex *> *vl, bool m) {
    bool vMark = v->GetMark();

    if (vMark == m)
        return;
    v->SetMark(m);

    vl->push_back(v);

    if (v->IsTerminal())
        return;

    BuildVertexList_core(v->GetLow(), vl, m);
    BuildVertexList_core(v->GetHigh(), vl, m);
}