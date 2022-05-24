#include "bdd_manager.h"

bdd_manager::bdd_manager()
{
    zeroVar = new variable{"0", 0};
    oneVar = new variable{"1", 0};
}

bdd_manager::~bdd_manager()
{
    for (auto var : GetVariables())
        delete var;
}