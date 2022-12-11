#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "conj.h"

using namespace std;

class dnf {
    vector<conj> cs;
    u_int varNum;
    vector<string> names;

   public:
    dnf(int variableNumber, bool constant = false);
    dnf(int variableNumber, vector<string> variableNames, bool constant = false);
    dnf(int variableNumber, vector<conj> cs);
    dnf(const dnf &);
    ~dnf();
    dnf AND(const dnf &);
    dnf OR(const dnf &);
    dnf NAND(const dnf &);
    dnf NOR(const dnf &);
    dnf XOR(const dnf &);
    dnf NXOR(const dnf &);
    dnf NEG();
    int GetVarNum();
    bool GetConstant();
    void SetConstant(bool c);
    bool IsConstant();
    void AddConjunction(conj);
    vector<conj> GetConjunctions();
    void SetNames(vector<string> names);
    void Reduce();
    friend ostream &operator<<(ostream &, dnf &);

   private:
    bool shrinkConstants();
    bool absorb();
    bool glue();
    string PrintConjunction(conj);
};

// Print
ostream &operator<<(ostream &, list<dnf> &);
