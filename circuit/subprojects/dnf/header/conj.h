#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;

enum var
{
    non,
    neg,
    pos,
};

class conj
{
    bool *constanta = nullptr;
    vector<var> varVect;

public:
    conj(int size);
    conj(int size, bool constanta);
    conj(const conj &);
    conj(initializer_list<var> l) { vector<var> varVect(l); };
    ~conj();

    bool *GetConstant();
    void SetConstant(bool c);
    bool IsConstant();

    vector<var> GetVectorCopy();
    conj AND(const conj &);
    vector<conj> Negate();
    var &operator[](size_t);
    bool operator==(const conj &);
    size_t size();
    conj Reduce(const conj &);
};
