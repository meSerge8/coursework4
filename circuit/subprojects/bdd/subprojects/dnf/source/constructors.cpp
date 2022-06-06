#include "dnf_from_bdd.h"

dnf_from_bdd::dnf_from_bdd(int varNum)
{
    variableNumber = varNum;
    for (u_int i = 0; i < variableNumber; i++)
        names.push_back("x" + to_string(i));
}

dnf_from_bdd::~dnf_from_bdd(){}
