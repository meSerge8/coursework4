#include "conj.h"

// conjunction conjunction::AND(const conjunction &conj)
// {
//     if (constanta != nullptr)
//         return {*constanta == 1 ? conj : *this};

//     if (conj.constanta != nullptr)
//         return {*conj.constanta == 1 ? *this : conj};

//     int size = varVect.size(), z;
//     conjunction res(size);

//     for (int i; i < size; i++)
//     {
//         z = varVect[i] | conj.varVect[i];

//         if (z == 0b11)
//             return {size, 0};

//         res[i] = var(z);
//     }

//     return res;
// }

// vector<conjunction> conjunction::Negate()
// {
//     size_t size = this->size();
//     vector<conjunction> res(size);

//     for (auto i = 0; i < size; i++)
//     {
//         var v = var(varVect[i] xor 0b11);

//         if (v == 0b11)
//             continue;

//         conjunction conj(size);
//         conj[i] = v;
//         res.push_back(conj);
//     }

//     return res;
// }

// bool conjunction::operator==(const conjunction &conj)
// {
//     if ((constanta == nullptr) != (conj.constanta == nullptr))
//         return false;

//     if (IsConstant())
//         return conj.constanta == nullptr ? false : true;

//     if (varVect != conj.varVect)
//         return false;

//     return true;
// }

// var &conjunction::operator[](size_t i)
// {
//     return varVect[i];
// }

// conjunction conjunction::Reduce(const conjunction &conj)
// {
//     return conj;
// }