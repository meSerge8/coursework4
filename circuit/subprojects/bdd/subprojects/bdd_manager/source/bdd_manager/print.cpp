#include "bdd_manager.h"

void bdd_manager::PrintVariables() {
    for (auto v : vars) {
        cout << *v << endl;
    }
}