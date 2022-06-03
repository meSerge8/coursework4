#pragma once

#include <iostream>
#include <string>
#include <list>

using namespace std;

enum gateType
{
    AND,
    OR,
    NOT,
    NAND,
    NOR,
    XOR,
    NXOR,
    DFF,
    INPUT,
    NONE
};

struct gate
{
    string name;
    gateType type;
    list<gate *> subGates;
};

ostream &operator<<(ostream &, gate &);