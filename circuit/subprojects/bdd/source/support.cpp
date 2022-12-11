#include "bdd.h"

void ClearMark(vertex *v) {
    if (v->GetMark() == 0)
        return;

    v->SwitchMark();
    if (v->IsTerminal())
        return;

    ClearMark(v->GetLow());
    ClearMark(v->GetHigh());
}

bdd_manager *bdd::GetManager() {
    return &bdd_mng;
}

bool bdd::AddRoot(vertex *root, string name) {
    roots.push_back(root);
    rootNames.push_back(name);
    return true;
}

vector<vertex *> bdd::GetRoots() {
    vector<vertex *> result;

    for (vertex *root : this->roots) {
        result.push_back(root);
    }

    return result;
}
