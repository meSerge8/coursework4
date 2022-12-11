#include "bdd.h"

bdd::bdd() {}

bdd::bdd(list<vertex *> rs) {
    roots = rs;
}

bdd::bdd(list<vertex *> r, list<string> rn) : bdd(r) {
    if (r.size() != rn.size())
        throw logic_error("list should have the same size");
    rootNames = rn;
}

bdd::~bdd() {}