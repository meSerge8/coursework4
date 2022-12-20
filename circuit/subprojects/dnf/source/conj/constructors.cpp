#include "conj.h"

conj::conj() {
    isConstanta = false;
    constanta = false;
}

conj::conj(vector<var> initVs, bool cons) {
    this->vs = initVs;
    for (var v : this->vs) {
        if (v != non) {
            this->isConstanta = false;
            this->constanta = false;
            return;
        }
    }

    this->isConstanta = true;
    this->constanta = cons;
}

conj::conj(size_t size, bool cons) : vs(size, non) {
    if (size == 0)
        throw logic_error("size must not be zero");
    isConstanta = true;
    constanta = cons;
}

conj::conj(const conj &copy) {
    vs = copy.vs;
    isConstanta = copy.isConstanta;
    constanta = copy.constanta;
}
