#pragma once

#include <iostream>
#include <string>

using namespace std;

struct variable {
    string value;
    u_int32_t index;
};

ostream &operator<<(ostream &, variable &);
string InfoVariable(variable);