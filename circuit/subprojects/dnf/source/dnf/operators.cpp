#include "dnf.h"

dnf dnf::and_basic(const dnf &d) {
    dnf res(this->varNum, false);
    for (conj cx : this->cs) {
        for (conj cy : d.cs) {
            res.AddConjunction(cx * cy);
        }
    }

    return res;
}

dnf dnf::or_basic(const dnf &x) {
    dnf res(*this);

    for (auto &c : x.cs) {
        res.AddConjunction(c);
    }

    return res;
}

dnf dnf::neg_basic() {
    dnf res(varNum, true);

    for (conj c : this->cs) {
        auto negs = c.Negate();
        dnf neg(varNum, negs);
        res = res.and_basic(neg);
        res.Reduce();
    }

    return res;
}

dnf dnf::NEG() {
    return neg_basic();
}

dnf dnf::AND(const dnf &x) {
    dnf res = and_basic(x);
    res.Reduce();
    return res;
}

dnf dnf::OR(const dnf &x) {
    dnf res = or_basic(x);
    res.Reduce();
    return res;
}

dnf dnf::NAND(dnf &x) {
    dnf res = and_basic(x);
    res.Reduce();
    return res.neg_basic();
}

dnf dnf::NOR(dnf &x) {
    dnf res = or_basic(x);
    res.Reduce();
    return res.neg_basic();
}

dnf dnf::XOR(const dnf &x) {
    dnf y = x;
    dnf left = neg_basic().AND(y);
    dnf right = AND(y.neg_basic());
    return left.OR(right);
}

dnf dnf::NXOR(const dnf &x) {
    dnf y = x;
    dnf left = AND(y);
    dnf right = neg_basic().AND(y.neg_basic());
    return left.OR(right);
}
