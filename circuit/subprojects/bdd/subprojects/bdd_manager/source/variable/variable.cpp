#include "variable.h"

ostream &operator<<(ostream &r, variable &var)
{
    r << InfoVariable(var) << endl;
    return r;
}

string InfoVariable(variable v)
{
    return "variable: " + v.value + " (" + to_string(v.index) + ")";
}