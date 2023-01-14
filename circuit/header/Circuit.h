#pragma once

#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <string>

#include "Gate.h"

using namespace std;

class Circuit {
    vector<Gate *>
        gates,
        inGates,
        outGates;

   public:
    Circuit(
        vector<Gate *> gates,
        vector<Gate *> inGates,
        vector<Gate *> outGates);
    ~Circuit();

    vector<Gate *> GetGates();
    vector<Gate *> GetInputs();
    vector<Gate *> GetOutputs();

    int CountGates();
    int CountInputs();
    int CountOutputs();

    friend ostream &operator<<(ostream &, Circuit &);
};