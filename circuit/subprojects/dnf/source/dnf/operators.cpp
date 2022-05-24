#include "dnf.h"

// dnf dnf::AND(const dnf &y)
// {
//     dnf res(varNum);

//     for (auto conjX : conjuctions)
//         for (auto conjY : y.conjuctions)
//             res.AddConjunction(conjX.AND(conjY));

//     res.Reduce();
//     return res;
// }

// dnf dnf::NAND(const dnf &y)
// {
//     // auto negX = x.negative;
//     // auto negY = this->negative;

//     // return negY->OR(*negX);
//     return y;
// }

// dnf dnf::OR(const dnf &x)
// {
//     // dnf x(2);
//     return x;
// }

// dnf dnf::NOR(const dnf &x)
// {
//     // auto negX = x.negative;
//     // auto negY = this->negative;
//     // auto res = negY->AND(*negX);
//     // return res;
//     return x;
// }

// dnf dnf::XOR(const dnf &x)
// {
//     // dnf x(2);
//     return x;
// }

// dnf dnf::NXOR(const dnf &x)
// {
//     // dnf x(2);
//     return x;
// }

// dnf dnf::NEG()
// {
//     dnf x(2);
//     return x;
// }