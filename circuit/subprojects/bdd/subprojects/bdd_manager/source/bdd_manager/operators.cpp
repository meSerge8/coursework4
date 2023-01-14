#include "bdd_manager.h"

bool and_bool(bool x, bool y) { return x & y; };
bool or_bool(bool x, bool y) { return x | y; };
bool nand_bool(bool x, bool y) { return not(x & y); };
bool nor_bool(bool x, bool y) { return not(x | y); };
bool xor_bool(bool x, bool y) { return x xor y; };
bool nxor_bool(bool x, bool y) { return not(x xor y); };

vertex *bdd_manager::AND_bin(vertex *one, vertex *two) {
    return Apply_bin(one, two, and_bool);
}

vertex *bdd_manager::OR_bin(vertex *one, vertex *two) {
    return Apply_bin(one, two, or_bool);
}

vertex *bdd_manager::NAND_bin(vertex *one, vertex *two) {
    return Apply_bin(one, two, nand_bool);
}

vertex *bdd_manager::NOR_bin(vertex *one, vertex *two) {
    return Apply_bin(one, two, nor_bool);
}

vertex *bdd_manager::XOR_bin(vertex *one, vertex *two) {
    return Apply_bin(one, two, xor_bool);
}

vertex *bdd_manager::NXOR_bin(vertex *one, vertex *two) {
    return Apply_bin(one, two, nxor_bool);
}

// ---------------------------------

vertex *bdd_manager::AND(vector<vertex *> vs) {
    return Apply(vs, and_bool);
}

vertex *bdd_manager::OR(vector<vertex *> vs) {
    return Apply(vs, or_bool);
}

vertex *bdd_manager::NAND(vector<vertex *> vs) {
    return Apply(vs, nand_bool);
}

vertex *bdd_manager::NOR(vector<vertex *> vs) {
    return Apply(vs, nor_bool);
}

vertex *bdd_manager::XOR(vector<vertex *> vs) {
    return Apply(vs, xor_bool);
}

vertex *bdd_manager::NXOR(vector<vertex *> vs) {
    return Apply(vs, nxor_bool);
}
