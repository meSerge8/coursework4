#include "dnf_from_bdd.h"


void dnf_from_bdd::ImportNames(vector<string> l)
{
    if (l.size() != variableNumber)
        throw logic_error("Wrong number of variables");
    
    names = l;
}
