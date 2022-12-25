#include "dnf.h"

bool dnf::glue2() {
    while (true) {
        vector<conj> newCS;
        newCS.reserve(this->cs.size());
        bool worked = false;

        for (auto i = this->cs.begin(); i != this->cs.end(); i++) {
            bool glued = false;

            for (auto j = next(i); j != this->cs.end(); j++) {
                conj c = tryGlue2(i, j);
                if (!c.IsConstant()) {
                    newCS.push_back(c);
                    this->cs.erase(j);
                    glued = true;
                    worked = true;
                    break;
                }

                if (c.GetConstant()) {
                    this->cs = {c};
                    return true;
                }
            }

            if (!glued) {
                newCS.push_back(*i);
            }
        }

        if (!worked) {
            return false;
        }

        this->cs = newCS;
    }
}

conj dnf::tryGlue2(vector<conj>::iterator x, vector<conj>::iterator y) {
    int idx = -1;

    for (size_t i = 0; i < this->varNum; i++) {
        int xorRes = x->vs[i] xor y->vs[i];

        if ((xorRes == 0b01) or (xorRes == 0b10)) {
            return {this->varNum, false};
        }

        if (xorRes == 0b11) {
            if (idx != -1) {
                return {this->varNum, false};
            }
            idx = i;
        }
    }

    if (idx == -1) {
        return {this->varNum, false};
    }

    conj res(*x);
    res.Set(idx, non, true);
    return res;
}