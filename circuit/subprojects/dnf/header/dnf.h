#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <list>
#include <memory>

#include "conj.h"

using namespace std;

class dnf
{
    vector<conj> cs;
    u_int varNum;

    vector<string> names;

public:
    // Constructors
    dnf(int variableNumber, bool constant = false); // 1
    dnf(int variableNumber, vector<string> variableNames, bool constant = false);
    dnf(int variableNumber, vector<conj> cs);
    dnf(const dnf &);
    ~dnf(); // 1

    // Operators
    dnf AND(const dnf &);
    dnf NAND(const dnf &);
    dnf OR(const dnf &);
    dnf NOR(const dnf &);
    dnf XOR(const dnf &);
    dnf NXOR(const dnf &);
    dnf NEG();

    // Operations
    int GetVarNum(); // 1
    bool GetConstant();
    void SetConstant(bool c);
    bool IsConstant();

    void AddConjunction(conj);           // 1
    vector<conj> GetConjunctions();      // 1
    void SetNames(vector<string> names); // 1

    // Reduce
    dnf Reduce();
    vector<conj> dnf::shrinkConstants();
    bool absorb(vector<conj> *);
    bool glue(vector<conj> *);

    // Print
    friend ostream &operator<<(ostream &, dnf &); // 1

private:
    // Operations
    void Simplify();
    // Print
    string PrintConjunction(conj); // 1
};

// Print
ostream &operator<<(ostream &, list<dnf> &);