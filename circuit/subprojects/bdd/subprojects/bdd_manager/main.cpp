#include <iostream>

#include "bdd_manager.h"

int main()
{
    bdd_manager man;
    auto v1 = man.CreateVertex("G1");
    auto v2 = man.CreateVertex("G2");
    auto v3 = man.AND_bin(v1, v2);

    man.Utilize(v1);
    man.Utilize(v2);

    cout << *v3 << endl;
    cout << "hello" << endl;
}