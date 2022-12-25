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

// dnf dnf::NEG() {
//     // cout << "NEG" << endl;
//     return neg_basic();
// }

// dnf dnf::AND(const dnf &x) {
//     // cout << "AND" << endl;
//     dnf res = and_basic(x);
//     res.Reduce();
//     return res;
// }

// dnf dnf::OR(const dnf &x) {
//     // cout << "OR" << endl;
//     dnf res = or_basic(x);
//     res.Reduce();
//     return res;
// }

// dnf dnf::NAND(dnf &x) {
//     // cout << "NAND" << endl;
//     // dnf a = neg_basic();
//     // dnf b = x;
//     // b = b.neg_basic();
//     // dnf res = a.or_basic(b);
//     // res.Reduce();
//     // return res;

//     // cout << "NAND" << endl;
//     dnf res = and_basic(x);
//     res.Reduce();
//     res = res.neg_basic();
//     // res.Reduce();
//     return res;
// }

// dnf dnf::NOR(dnf &x) {
//     // cout << "NOR" << endl;
//     // dnf a = neg_basic();
//     // dnf b = x;
//     // b = b.neg_basic();
//     // dnf res = a.and_basic(b);
//     // res.Reduce();
//     // return res;

//     // cout << "NOR" << endl;
//     dnf res = or_basic(x);
//     res.Reduce();
//     // cout << res << endl;
//     res = res.neg_basic();
//     // res.Reduce();
//     return res;
// }

// dnf dnf::XOR(const dnf &x) {
//     // cout << "XOR" << endl;
//     dnf res = and_basic(x).neg_basic().and_basic(or_basic(x));
//     res.Reduce();
//     return res;
// }

// dnf dnf::NXOR(const dnf &x) {
//     // cout << "NXOR" << endl;
//     dnf res = and_basic(x).or_basic(or_basic(x).neg_basic());
//     res.Reduce();
//     return res;
// }
