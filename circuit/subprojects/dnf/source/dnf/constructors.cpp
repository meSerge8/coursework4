#include "dnf.h"

dnf::dnf(int variableNumber, bool constant) {
    this->varNum = variableNumber;
    this->cs = {{this->varNum, constant}};
}

dnf::dnf(int variableNumber, vector<string> variableNames, bool constant)
    : dnf(variableNumber, constant) {
    SetNames(variableNames);
}

dnf::dnf(int variableNumber, vector<conj> conjs) {
    varNum = variableNumber;
    cs = conjs;
}

dnf::dnf(const dnf &orig) {
    varNum = orig.varNum;
    cs = orig.cs;
    names = orig.names;
}

dnf::~dnf() {}
