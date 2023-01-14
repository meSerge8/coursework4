#pragma once

#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <string>

#include "Gate.h"
#include "Circuit.h"

using namespace std;

class Importer {
   private:
    vector<Gate *>
        gates,
        inGates,
        outGates;

   public:
    Circuit Import(string);

   private:
    void processLine(string);
    void addInput(string);
    void addOutput(string);
    void addGate(smatch);
    void addDFF(string, string);

    void addSubGates(Gate *, string);
    GateType getType(string);
};