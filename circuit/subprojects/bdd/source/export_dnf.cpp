#include "bdd.h"

list<dnf_from_bdd> bdd::ExportDNF() {
    list<dnf_from_bdd> dnf_res;
    for (auto root : roots) {
        auto d = BuildDNF(root);
        dnf_res.push_back(d);
    }

    return dnf_res;
}

dnf_from_bdd bdd::BuildDNF(vertex *root) {
    auto vars = bdd_mng.GetVariables();
    int capacity = vars.size() - 2;

    dnf_from_bdd dnf_res(capacity);
    dnf_res.ImportNames(GetVarNames(vars));

    conjunction cnj;
    BuildDNF_Core(root, dnf_res, cnj);

    return dnf_res;
}

void bdd::BuildDNF_Core(vertex *v, dnf_from_bdd &d, conjunction &cnj) {
    u_int idx = v->GetVariable()->index;

    while (cnj.size() < idx)
        cnj.push_back(none);

    if (v->IsTerminal()) {
        string val = v->GetVariable()->value;
        if (val == "1") {
            d.AddConjunction(cnj);
        }
    } else {
        conjunction cnjLow(cnj), cnjHigh(cnj);
        cnjLow.push_back(negative);
        cnjHigh.push_back(positive);
        BuildDNF_Core(v->GetLow(), d, cnjLow);
        BuildDNF_Core(v->GetHigh(), d, cnjHigh);
    }
}

vector<string> bdd::GetVarNames(list<variable *> vs) {
    vector<string> res;

    for (auto v : vs) {
        if (v->index == vs.size() - 2)
            break;
        res.push_back(v->value);
    }

    return res;
}
