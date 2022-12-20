#include "conj.h"

conj conj::operator*(const conj &c) {
    if (this->isConstanta) {
        return this->constanta ? c : *this;
    }

    if (c.isConstanta) {
        return c.constanta ? *this : c;
    }

    vector<var> vars(vs.size());

    for (int i = 0; i < vs.size(); i++) {
        int z = vs[i] | c.vs[i];

        if (z == 0b11)
            return {vs.size(), 0};

        vars[i] = var(z);
    }

    return {vars, false};
}

vector<conj> conj::Negate() {
    if (this->isConstanta) {
        return {{vs.size(), not this->constanta}};
    }

    vector<conj> res;

    for (size_t i = 0; i < vs.size(); i++) {
        int v = vs[i] xor 0b11;

        if (v == 0b11)
            continue;

        vector<var> vars(vs.size(), non);
        vars[i] = var(v);

        res.push_back({vars, false});
    }

    return res;
}

bool conj::operator==(const conj &c) {
    if (isConstanta != c.isConstanta)
        return false;

    if (isConstanta)
        return constanta == c.constanta;

    return vs == c.vs;
}

bool operator==(const conj &x, const conj &y) {
    if (x.isConstanta != y.isConstanta)
        return false;

    if (x.isConstanta)
        return x.constanta == y.constanta;

    return x.vs == y.vs;
}

void conj::Set(int idx, var v, bool c) {
    vs[idx] = v;

    if (v != non) {
        isConstanta = false;
        return;
    }

    for (var vr : vs)
        if (vr != non)
            return;

    isConstanta = true;
    constanta = c;
}

var conj::Get(int idx) {
    return vs[idx];
}