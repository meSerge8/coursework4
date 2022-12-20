#include "circuit.h"

list<dnf> circuit::ExportDNF() {
    buildInputGates();
    list<dnf> dnfs;

    vector<string> names;
    for (gate *g : inputs)
        names.push_back(g->name);

    for (gate *outGate : outputs) {
        dnf res = BuildDNF(outGate);
        res.SetNames(names);
        dnfs.push_back(res);
    }
    return dnfs;
}

dnf circuit::BuildDNF(gate *g) {
    if (g->type == INPUT)
        return BuildInputDNF(g);

    if (g->type == NOT) {
        gate *subGate = g->subGates.front();
        return BuildDNF(subGate).NEG();
    }

    auto first = g->subGates.begin();
    dnf res = BuildDNF(*first);
    for (auto itr = next(first); itr != g->subGates.end(); itr++) {
        dnf sub = BuildDNF(*itr);
        res = apply(res, sub, g->type);
    }

    return res;
}

dnf circuit::BuildInputDNF(gate *g) {
    int i = 0;
    for (gate *inGate : inputs) {
        if (inGate == g)
            break;

        i++;
    }

    conj c(inputs.size());
    c.Set(i, pos, false);

    return {inputs.size(), {c}};
}

dnf circuit::apply(dnf &x, dnf &y, gateType type) {
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