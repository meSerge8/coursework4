#pragma once

#include <iostream>
#include <string>
#include <list>

using namespace std;

enum gateType
{
    AND,   // 0
    OR,    // 1
    NOT,   // 2
    NAND,  // 3
    NOR,   // 4
    XOR,   // 5
    NXOR,  // 6
    DFF,   // 7
    INPUT, // 8
    NONE   // 9
};

struct gate
{
    string name;
    gateType type;
    list<gate *> subGates;
};

ostream &operator<<(ostream &, gate&);