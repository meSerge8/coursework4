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

class conjunction
{
    bool *constanta = nullptr;
    vector<var> varVect;

public:
    conjunction(int size);
    conjunction(int size, bool constanta);
    conjunction(const conjunction &);
    conjunction(initializer_list<var> l) { vector<var> varVect(l); };
    ~conjunction();

    bool *GetConstant();
    void SetConstant(bool c);
    bool IsConstant();

    vector<var> GetVectorCopy();
    conjunction AND(const conjunction &);
    vector<conjunction> Negate();
    var &operator[](size_t);
    bool operator==(const conjunction &);
    size_t size();
    conjunction Reduce(const conjunction &);
};
