#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>

using namespace std;

enum GateType {
    INPUT,
    NOT,
    AND,
    OR,
    NAND,
    NOR,
    XOR,
    NXOR
};

class Gate {
   private:
    string name;
    GateType type;
    vector<Gate *>
        predecessors,
        successors;

   public:
    Gate(string, GateType);

    string GetName();
    GateType GetType();
    void SetType(GateType);
    vector<Gate *> GetPredecessors();
    vector<Gate *> GetSuccessors();

    void AddPredecessor(Gate *);
    void AddSuccessors(Gate *);

    int CountPredecessors();
    int CountSuccessors();

    friend ostream &operator<<(ostream &, Gate &);
};

vector<Gate *> sortTopological(vector<Gate *>);
string printType(GateType);
Gate *FindByName(vector<Gate *>, string);
vector<string> GetNames(vector<Gate *>);
bool contains(vector<Gate *> *, Gate *);