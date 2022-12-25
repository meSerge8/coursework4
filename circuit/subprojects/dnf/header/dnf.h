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
    dnf(int variableNumber, bool constant);
    dnf(int variableNumber, vector<string> variableNames, bool constant);
    dnf(int variableNumber, vector<conj> cs);
    dnf(const dnf &);
    ~dnf();

    dnf and_basic(const dnf &);
    dnf or_basic(const dnf &);
    dnf neg_basic();

    dnf AND(const dnf &);
    dnf OR(const dnf &);
    dnf NAND(dnf &);
    dnf NOR(dnf &);
    dnf XOR(const dnf &);
    dnf NXOR(const dnf &);
    dnf NEG();
    void Reduce();

    int GetVarNum();
    bool GetConstant();
    void SetConstant(bool c);
    bool IsConstant();

    void AddConjunction(conj);
    vector<conj> GetConjunctions();

    void SetNames(vector<string> names);
    vector<string> GetNames();

    void ShrinkVariables();

    friend ostream &operator<<(ostream &, dnf &);

   private:
    bool removeConstants();
    bool glue();
    conj tryGlue(vector<conj>::iterator, vector<conj>::iterator);
    void absorb();
    int tryAbsorb(vector<conj>::iterator, vector<conj>::iterator);

    bool glue2();
    conj tryGlue2(vector<conj>::iterator, vector<conj>::iterator);

    string PrintConjunction(conj);
};

// Print
ostream &operator<<(ostream &, list<dnf> &);

conj buildReducedConj(vector<conj>::iterator, vector<conj>::iterator);
