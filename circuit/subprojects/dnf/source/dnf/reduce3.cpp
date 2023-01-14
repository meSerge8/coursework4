#include "dnf.h"

void dnf::ObviousReduce() {
    if (removeConstants()) {
        return;
    }

    if (IsConstant()) {
        return;
    }
}

void dnf::Reduce() {
    ObviousReduce();

    if (glue2()) {
        return;
    }

    absorb();
}

bool dnf::removeConstants() {
    vector<conj> cs;
    cs.reserve(this->cs.size());

    for (conj& c : this->cs) {
        if (!c.IsConstant()) {
            auto it = find(cs.begin(), cs.end(), c);
            if (it == cs.end()) {
                cs.push_back(c);
            }
            continue;
        }

        if (c.GetConstant()) {
            this->cs = {c};
            return true;
        }
    }

    this->cs = cs;
    if (this->cs.size() == 0) {
        this->cs.push_back({this->varNum, 0});
    }
    return false;
}

bool dnf::glue() {
    vector<conj> appendCs;

    for (auto i = this->cs.begin() + 1; true; i++) {
        if (i == this->cs.end()) {
            if (appendCs.size() == 0) {
                break;
            }

            i = this->cs.insert(this->cs.end(), appendCs.begin(), appendCs.end());
            appendCs.clear();
        }

        // cout << (i - this->cs.begin()) << " " << this->cs.size() << endl;

        for (auto j = this->cs.begin(); j != i; j++) {
            conj c = tryGlue(i, j);
            if (c.IsConstant()) {
                if (c.GetConstant()) {
                    this->cs = {c};
                    return true;
                } else {
                    continue;
                }
            }

            auto it = find(appendCs.begin(), appendCs.end(), c);
            if (it != appendCs.end()) {
                continue;
            }

            it = find(this->cs.begin(), this->cs.end(), c);
            if (it != this->cs.end()) {
                continue;
            }

            appendCs.push_back(c);
        }
    }
    return false;
}

conj dnf::tryGlue(vector<conj>::iterator x, vector<conj>::iterator y) {
    bool hasReversed = false;
    int idx;

    for (size_t i = 0; i < this->varNum; i++) {
        if ((x->vs[i] xor y->vs[i]) != 0b11) {
            continue;
        }

        if (hasReversed) {
            return {this->varNum, 0};
        }

        hasReversed = true;
        idx = i;
    }

    if (!hasReversed) {
        return {this->varNum, 0};
    }

    conj cx(*x), cy(*y);

    cx.Set(idx, non, true);
    cy.Set(idx, non, true);

    return cx * cy;
}

void dnf::absorb() {
    vector<conj> res;

    while (!this->cs.empty()) {
        vector<conj> notAbsorbed;
        auto absorber = this->cs.begin();

        for (auto i = this->cs.begin(); i != this->cs.end(); i++) {
            int x = tryAbsorb(absorber, i);

            if (x == 0) {
                notAbsorbed.push_back(*i);
            }

            if (x == -1) {
                absorber = i;
                notAbsorbed = {};
                i = this->cs.begin();
            }
        }

        res.push_back(*absorber);
        this->cs = notAbsorbed;
    }

    this->cs = res;
}

int dnf::tryAbsorb(vector<conj>::iterator x, vector<conj>::iterator y) {
    int res = 0;

    for (size_t i = 0; i < this->varNum; i++) {
        var xi = x->vs[i];
        int xr = xi xor y->vs[i];

        if (xr == 0b11) {
            return 0;
        };

        if (xr == 0b00) {
            continue;
        }

        if (res) {
            if ((xi == non) xor (res == 1)) {
                return 0;
            }
        }

        res = xi ? -1 : 1;
    }

    return res ? res : 1;
}
