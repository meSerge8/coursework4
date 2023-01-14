#include "DnfExporter.h"

DnfExporterFromInput::DnfExporterFromInput(Circuit *c) {
    this->c = c;
}

vector<dnf> DnfExporterFromInput::Export() {
    vector<string> names = GetNames(this->c->GetInputs());
    vector<dnf> result;

    for (Gate *g : this->c->GetGates()) {
        dnf d = buildDNF(g);
        d.SetNames(names);
        this->dnfs.push_back(d);

        auto outs = this->c->GetOutputs();
        if (contains(&outs, g)) {
            result.push_back(d);
        }
    }

    return result;
}

dnf DnfExporterFromInput::buildDNF(Gate *g) {
    if (g->GetType() == INPUT)
        return buildInputDNF(g);

    auto subDnfs = getSubDnfs(g);

    if (g->GetType() == NOT) {
        return subDnfs.front().NEG();
    }

    auto first = subDnfs.begin();
    dnf res = *first;
    for (auto itr = next(first); itr != subDnfs.end(); itr++) {
        res = apply(res, *itr, g->GetType());
    }

    return res;
}

dnf DnfExporterFromInput::buildInputDNF(Gate *g) {
    int i = 0;
    for (Gate *inGate : this->c->GetInputs()) {
        if (inGate == g)
            break;

        i++;
    }

    conj c(this->c->CountInputs(), false);
    c.Set(i, pos, false);

    return {
        int(this->c->CountInputs()),
        {c},
    };
}

vector<dnf> DnfExporterFromInput::getSubDnfs(Gate *g) {
    vector<dnf> result;
    auto gs = this->c->GetGates();
    auto itrBegin = gs.begin();
    auto itrEnd = gs.end();

    for (Gate *subGate : g->GetPredecessors()) {
        auto itr = find(itrBegin, itrEnd, subGate);
        if (itr == itrEnd) {
            throw logic_error("subGate not found");
        }

        int i = itr - itrBegin;
        result.push_back(this->dnfs[i]);
    }

    return result;
}

dnf DnfExporterFromInput::apply(dnf &x, dnf &y, GateType type) {
    switch (type) {
        case AND:
            return x.AND(y);

        case OR:
            return x.OR(y);

        case NAND:
            return x.NAND(y);

        case NOR:
            return x.NOR(y);

        case XOR:
            return x.XOR(y);

        case NXOR:
            return x.NXOR(y);

        default:
            throw logic_error("Can't deduce what to do");
    }
}
