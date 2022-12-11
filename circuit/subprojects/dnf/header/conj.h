#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

enum var {
    non,
    neg,
    pos,
};

class conj {
    bool isConstanta,
        constanta;
    vector<var> vs;

   public:
    conj();
    conj(vector<var>);
    conj(int size, bool constanta = 0);
    conj(const conj &);

    bool GetConstant();
    void SetConstant(bool c);
    bool IsConstant();

    conj operator*(const conj &);
    vector<conj> Negate();
    bool operator==(const conj &);
    size_t Size();
    friend ostream &operator<<(ostream &, conj &);

    void Set(int idx, var v);
    var Get(int idx);
};
