#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <list>

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
    vector<var> vs;

public:
    conj();                         // 1
    conj(vector<var>);              // 1
    conj(int size);                 // 1
    conj(int size, bool constanta); // 1

    conj(const conj &);
    ~conj();
    // conj(initializer_list<var> l) { vector<var> vs(l); };

    bool *GetConstant();      // 1
    void SetConstant(bool c); // 1
    bool IsConstant();        // 1

    conj operator*(const conj &);                  // 1
    vector<conj> Negate();                         // 1
    bool operator==(const conj &);                 // 1
    size_t Size();                                 // 1
    friend ostream &operator<<(ostream &, conj &); // 1
    vector<var> GetVectorCopy();                   // 1

    void Set(int idx, var v);
    var Get(int idx);
    // conj Reduce(const conj &);
};