#include "dnf.h"

dnf::dnf(int variableNumber, bool constant) {
    varNum = variableNumber;
    cs.push_back({varNum, constant});
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
