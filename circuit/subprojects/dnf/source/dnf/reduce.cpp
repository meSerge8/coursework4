#include "dnf.h"

// void dnf::Reduce()
// {
//     for (auto itr = conjuctions.begin(); itr != conjuctions.end(); itr++)
//     {
//         for (auto jtr = next(itr, 1); jtr != conjuctions.end(); jtr++)
//         {
//             EraceIfDuplicate(itr, jtr);
//         }
//     }
// }

// void dnf::EraceIfDuplicate(list<conjunction>::iterator original,
//                            list<conjunction>::iterator duplicate)
// {
//     if (!(*original == *duplicate))
//         duplicate = conjuctions.erase(duplicate);
// }