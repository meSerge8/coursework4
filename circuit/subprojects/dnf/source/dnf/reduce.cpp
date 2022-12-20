// #include "dnf.h"

// void dnf::Reduce() {
//     while (true) {
//         if (cs.size() == 1)
//             return;

//         if (cs.size() == 0) {
//             cs = {{varNum, false}};
//             return;
//         }

//         if (shrinkConstants())
//             continue;

//         if (absorb())
//             continue;

//         if (glue())
//             continue;

//         break;
//     }
// }

// bool dnf::shrinkConstants() {
//     for (auto itr = cs.begin(); itr != cs.end(); itr++) {
//         bool isC = itr->IsConstant();
//         if (isC == false)
//             continue;

//         if (itr->GetConstant() == true) {
//             cs = {{varNum, true}};
//             return true;
//         } else {
//             cs.erase(itr);
//             return true;
//         }
//     }

//     return false;
// }

// bool dnf::absorb() {
//     for (auto itr1 = cs.begin(); itr1 != cs.end(); itr1++) {
//         for (auto itr2 = next(itr1, 1); itr2 != cs.end(); itr2++) {
//             if (itr1->Size() != itr2->Size())
//                 throw logic_error("cant process. Size must be equal");

//             int size = itr1->Size();
//             conj common(size);

//             for (int i = 0; i < size; i++)
//                 if (itr1->Get(i) == itr2->Get(i))
//                     common.Set(i, itr1->Get(i));

//             if (common.IsConstant())
//                 continue;

//             if (common == *itr1)
//                 itr2 = cs.erase(itr2);
//             else if (common == *itr2)
//                 itr1 = cs.erase(itr1);
//             else
//                 continue;

//             return true;
//         }
//     }

//     return false;
// }

// bool dnf::glue() {
//     for (auto itr1 = cs.begin(); itr1 != cs.end(); itr1++) {
//         for (auto itr2 = next(itr1, 1); itr2 != cs.end(); itr2++) {
//             if (itr1->Size() != itr2->Size())
//                 throw logic_error("cant process. Size must be equal");

//             for (int i = 0; i < itr1->Size(); i++) {
//                 if ((itr1->Get(i) xor itr2->Get(i)) != 0b11)
//                     continue;

//                 conj new1(*itr1),
//                     new2(*itr2);

//                 new1.Set(i, non);
//                 new2.Set(i, non);

//                 auto it = find(cs.begin(), cs.end(), new1 * new2);
//                 if (it == cs.end())
//                     continue;

//                 cs.erase(it);
//                 return true;
//             }
//         }
//     }

//     return false;
// }
