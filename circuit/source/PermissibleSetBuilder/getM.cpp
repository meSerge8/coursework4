#include "PermissibleSetBuilder.h"

vector<unsigned long>* GetM(dnf d) {
    if (d.IsConstant()) {
        if (d.GetConstant() == 0) {
            return new vector<unsigned long>();
        } else {
            throw Build_M_for_1_exception();
        }
    }

    vector<unsigned long>* res = new vector<unsigned long>;
    for (conj& c : d.GetConjunctions()) {
        auto vs_ = c.vs;
        buildLines(vs_.begin(), &vs_, 0, res);
    }
    return res;
}

void buildLines(vector<var>::iterator i, vector<var>* vs, unsigned long narost, vector<unsigned long>* res) {
    while (true) {
        if (i >= vs->end()) {
            res->push_back(narost);
            return;
        }

        if (*i == non) {
            break;
        }

        int y = (*i - 1);
        if (y != 0) {
            unsigned long x = 1 << (i - vs->begin());
            narost = narost | x;
        }

        i++;
    }

    long one = 1 << (i - vs->begin());
    long posNarost = narost | one;
    i++;
    buildLines(i, vs, narost, res);
    buildLines(i, vs, posNarost, res);
}