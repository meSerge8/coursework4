#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <list>
#include <memory>
#include <algorithm>

#include "conj.h"

using namespace std;

class dnf
{
    vector<conj> cs;
    u_int varNum;
    vector<string> names;

public:
    // Constructors
    dnf(int variableNumber, bool constant = false); 
    dnf(int variableNumber, vector<string> variableNames, bool constant = false);
    dnf(int variableNumber, vector<conj> cs);
    dnf(const dnf &);
    ~dnf(); 

    // Operators
    dnf AND(const dnf &);
    dnf OR(const dnf &);
    dnf NAND(const dnf &);
    dnf NOR(const dnf &);
    dnf XOR(const dnf &);
    dnf NXOR(const dnf &);
    dnf NEG();

    // Operations
    int GetVarNum(); 
    bool GetConstant();
    void SetConstant(bool c);
    bool IsConstant();

    void AddConjunction(conj);           
    vector<conj> GetConjunctions();      
    void SetNames(vector<string> names); 

    // Reduce
    void Reduce();

    // Print
    friend ostream &operator<<(ostream &, dnf &); 

private:
    // Reduce
    bool shrinkConstants();
    bool absorb();
    bool glue();

    // Print
    string PrintConjunction(conj); 
};

// Print
ostream &operator<<(ostream &, list<dnf> &);
