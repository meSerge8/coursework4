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
    bool *constanta = nullptr;
    list<conj> conjuctions;
    u_int varNum;

    vector<string> names;

public:
    // Constructors
    dnf(int variableNumber, bool constant = false);
    dnf(int variableNumber, vector<string> variableNames, bool constant = false);
    dnf(const dnf &);
    ~dnf();

    // Operators
    dnf AND(const dnf &);
    dnf NAND(const dnf &);
    dnf OR(const dnf &);
    dnf NOR(const dnf &);
    dnf XOR(const dnf &);
    dnf NXOR(const dnf &);
    dnf NEG();

    // Operations
    bool *GetConstant();
    void SetConstant(bool c);
    bool IsConstant();

    void AddConjunction(conj);
    list<conj> GetConjunctions();
    void SetNames(vector<string> names);

    // Reduce
    void Reduce();
    void EraceIfDuplicate(list<conj>::iterator original,
                          list<conj>::iterator duplicate);

    // Print
    friend ostream &operator<<(ostream &, dnf &);

private:
    // Operations
    void Simplify();
    // Print
    string PrintConjunction(conj);
};

// Print
ostream &operator<<(ostream &, list<dnf> &);