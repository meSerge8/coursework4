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
   public:
    bool isConstanta,
        constanta;

    vector<var> vs;

    conj();
    conj(vector<var>, bool);
    conj(size_t size, bool constanta);
    conj(const conj &);

    bool GetConstant();
    void SetConstant(bool c);
    bool IsConstant();

    conj operator*(const conj &);
    vector<conj> Negate();
    bool operator==(const conj &);
    size_t Size();
    friend ostream &operator<<(ostream &, conj &);

    void Set(int idx, var v, bool c);
    var Get(int idx);

    friend bool operator==(const conj &x, const conj &y);
};

bool operator==(const conj &x, const conj &y);