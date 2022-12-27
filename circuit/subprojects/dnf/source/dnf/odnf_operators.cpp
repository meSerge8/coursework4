#include "dnf.h"

// dnf dnf::NEG() {
//     return neg_basic();
// }

// dnf dnf::AND(const dnf &y) {
//     dnf res = and_basic(y);
//     res.Reduce();
//     return res;
// }

// dnf dnf::OR(const dnf &y) {
//     dnf res = or_basic(NEG().and_basic(y));
//     res.Reduce();
//     return res;
// }

// dnf dnf::NAND(dnf &y) {
//     dnf res = and_basic(y.NEG()).or_basic(NEG());
//     res.Reduce();
//     return res;
// }

// dnf dnf::NOR(dnf &y) {
//     dnf res = NEG().and_basic(y.NEG());
//     res.Reduce();
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
