#include "PermissibleSetBuilder.h"

tuple<dnf, dnf> PermissibleSetBuilder::build_D1_D0() {
    vector<dnf> dnfs_0, dnfs_1;
    buildDNFs_0_and_1(&dnfs_0, &dnfs_1);

    dnf B = buildB(&dnfs_0, &dnfs_1),
        C1 = buildDNF(this->pole, &dnfs_0),
        C0 = C1.NEG(),
        D0 = B.AND(C1),
        D1 = B.AND(C0);

    return {D1, D0};
}

void PermissibleSetBuilder::buildDNFs_0_and_1(vector<dnf>* dnfs_0, vector<dnf>* dnfs_1) {
    int inputsCount = this->inGates.size();

    for (Gate* g : this->gates) {
        dnf dnf_0 = (g == this->pole) ? dnf{inputsCount, false} : buildDNF(g, dnfs_0);
        dnf dnf_1 = (g == this->pole) ? dnf{inputsCount, true} : buildDNF(g, dnfs_1);

        dnfs_0->push_back(dnf_0);
        dnfs_1->push_back(dnf_1);
    }
}

dnf PermissibleSetBuilder::buildB(vector<dnf>* dnfs_0, vector<dnf>* dnfs_1) {
    dnf B(this->inGates.size(), false);

    for (int i = 0; i < this->gates.size(); i++) {
        if (contains(&this->outGates, this->gates[i])) {
            dnf Bi = dnfs_0->at(i).XOR(dnfs_1->at(i));
            B = B.OR(Bi);
        }
    }

    return B;
}

dnf PermissibleSetBuilder::buildDNF(Gate* g, vector<dnf>* dnfs) {
    if (g->GetType() == INPUT) {
        return buildInputDNF(g);
    }

    auto predDNFs = getPredecessorsDNF(g, dnfs);

    if (g->GetType() == NOT) {
        return predDNFs.front().NEG();
    }

    auto first = predDNFs.begin();
    dnf res = *first;
    for (auto i = next(first); i != predDNFs.end(); i++) {
        res = apply(res, *i, g->GetType());
    }

    return res;
}

dnf PermissibleSetBuilder::buildInputDNF(Gate* g) {
    int i = 0;
    for (Gate* inGate : this->inGates) {
        if (inGate == g)
            break;

        i++;
    }

    conj c(this->inGates.size(), false);
    c.Set(i, pos, false);

    return {
        int(this->inGates.size()),
        {c},
    };
}

vector<dnf> PermissibleSetBuilder::getPredecessorsDNF(Gate* g, vector<dnf>* dnfs) {
    vector<dnf> predDNFs;

    for (Gate* subGate : g->GetPredecessors()) {
        predDNFs.push_back(getGateDNF(subGate, dnfs));
    }

    return predDNFs;
}

dnf PermissibleSetBuilder::apply(dnf& x, dnf& y, GateType type) {
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

dnf PermissibleSetBuilder::getGateDNF(Gate* g, vector<dnf>* dnfs) {
    auto begin = this->gates.begin();
    auto end = this->gates.end();

    auto i = find(begin, end, g);
    if (i == end) {
        throw logic_error("subGate not found");
    }

    return dnfs->at(i - begin);
}
