#include "dnfExporter.h"

DnfExporterFromUnput::DnfExporterFromUnput(vector<gate *> gates) {
    this->gates = gates;
    for (auto g : this->gates) {
        this->inputGates.push_back(g);
    }
}

vector<dnf> DnfExporterFromUnput::Export() {
    sortTopological();
    auto names = buildNames();
    vector<dnf> result;

    for (gate *g : this->gates) {
        dnf d = buildDNF(g);
        this->dnfs.push_back(d);
        if (find(allSubgates.begin(), allSubgates.end(), g) == allSubgates.end()) {
            d.SetNames(names);
            result.push_back(d);
        }
    }

    return result;
}

void DnfExporterFromUnput::sortTopological() {
    vector<int> in_degrees(this->gates.size(), 0);
    queue<gate *> q;

    for (size_t i = 0; i < this->gates.size(); i++) {
        auto in_degree = this->gates[i]->subGates.size();
        in_degrees[i] = in_degree;

        if (in_degree == 0) {
            q.push(this->gates[i]);
        }

        for (gate *subGate : this->gates[i]->subGates) {
            if (find(this->allSubgates.begin(), this->allSubgates.end(), subGate) == this->allSubgates.end()) {
                this->allSubgates.push_back(subGate);
            }
        }
    }

    int countVisited = 0;
    vector<gate *> sorted;

    while (!q.empty()) {
        countVisited++;
        gate *frontGate = q.front();
        q.pop();
        sorted.push_back(frontGate);

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

            q.push(this->gates[i]);
        }
    }

    if (this->gates.size() != countVisited) {
        throw logic_error("Sorting failed: there is a cycle in graph");
    }

    this->gates = sorted;
}

vector<string> DnfExporterFromUnput::buildNames() {
    vector<string> names;
    for (auto g : this->inputGates) {
        names.push_back(g->name);
    }
    return names;
}

dnf DnfExporterFromUnput::buildDNF(gate *g) {
    if (g->type == INPUT)
        return buildInputDNF(g);

    auto subDnfs = getSubDnfs(g);

    if (g->type == NOT) {
        return subDnfs.front().NEG();
    }

    auto first = subDnfs.begin();
    dnf res = *first;
    for (auto itr = next(first); itr != subDnfs.end(); itr++) {
        res = apply(res, *itr, g->type);
    }

    return res;
}

dnf DnfExporterFromUnput::buildInputDNF(gate *g) {
    int i = 0;
    for (gate *inGate : this->inputGates) {
        if (inGate == g)
            break;

        i++;
    }

    conj c(this->inputGates.size());
    c.Set(i, pos);

    return {this->inputGates.size(), {c}};
}

list<dnf> DnfExporterFromUnput::getSubDnfs(gate *g) {
    list<dnf> result;
    auto itrBegin = this->gates.begin();
    auto itrEnd = this->gates.end();

    for (gate *subGate : g->subGates) {
        auto itr = find(itrBegin, itrEnd, subGate);
        if (itr == itrEnd) {
            throw logic_error("subGate not found");
        }

        int i = itr - itrBegin;
        result.push_back(this->dnfs[i]);
    }

    return result;
}

dnf DnfExporterFromUnput::apply(dnf &x, dnf &y, gateType type) {
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
