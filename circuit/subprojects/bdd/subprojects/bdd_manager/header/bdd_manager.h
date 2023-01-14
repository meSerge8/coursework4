#pragma once

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "variable.h"
#include "vertex.h"

using namespace std;

class bdd_manager {
    vector<variable *> vars;
    variable *zeroVar, *oneVar;

   public:
    bdd_manager();
    ~bdd_manager();

    variable *CreateVar(string variableName);
    vertex *CreateVertex(string vertexName);
    vertex *CreateVertex(variable *variableReference);
    vertex *CreateZero();
    vertex *CreateOne();
    void Utilize(vertex *delme);

    vertex *AND_bin(vertex *one, vertex *two);
    vertex *OR_bin(vertex *one, vertex *two);
    vertex *NAND_bin(vertex *one, vertex *two);
    vertex *NOR_bin(vertex *one, vertex *two);
    vertex *XOR_bin(vertex *one, vertex *two);
    vertex *NXOR_bin(vertex *one, vertex *two);

    vertex *AND(vector<vertex *> vertexList);
    vertex *OR(vector<vertex *> vertexList);
    vertex *NAND(vector<vertex *> vertexList);
    vertex *NOR(vector<vertex *> vertexList);
    vertex *XOR(vector<vertex *> vertexList);
    vertex *NXOR(vector<vertex *> vertexList);

    vertex *Negate(vertex *rootVertex);

    vertex *Reduce(vertex *rootVertex);

    vector<variable *> GetVariables();
    vector<variable *> GetVariablesNonTerm();
    variable *GetOneVariable();
    variable *GetZeroVariable();

    void PrintVariables();

    void ExportPNG(vector<string> *outputGatesNames,
                   vector<vertex *> *vertexList,
                   string filename);

   private:
    // Create
    void UpdateTerminals();

    // Apply
    vertex *Apply_bin(vertex *one, vertex *two, bool (*func)(bool, bool));
    vertex *Apply_bin_core(vertex *one, vertex *two, bool (*func)(bool, bool));

    // Apply multiple times
    vertex *Apply(vector<vertex *> vertexList, bool (*func)(bool, bool));

    // Negate
    vertex *Negate_core(vertex *, map<u_int32_t, vertex *> &, bool);

    // Traverse
    void TraverseSample(vertex *, bool mark);
    void Traverse(vertex *, void (*func)(vertex *));
    void Traverse_core(vertex *, void (*func)(vertex *), bool);
    void ClearMark(vertex *);

    // Reduce
    map<variable *, list<vertex *> *> BuildVertexMap(vertex *);

    void EraseRedundant(list<vertex *> *);
    void AssignId(list<vertex *> *, map<uint, vertex *> *);
    void AddVertex(vertex *, map<uint, vertex *> *);
    vertex *BuildRightVertex(vertex *, map<uint, vertex *> *);
    void EraseDuplicates(list<vertex *>::iterator, list<vertex *> *);
    vertex *GetRightRoot(vertex *, map<uint, vertex *> *);
    void DeleteVertexMap(map<variable *, list<vertex *> *> *);

    // Export as PNG via graphviz
    string BindOuts(vector<string> *outs, vector<vertex *> *vs);
    void DrawVertexsRecursive(vertex *, ofstream *, bool m);
};

// Support
list<vertex *> BuildVertexList(vertex *);
void BuildVertexList_core(vertex *, list<vertex *> *, bool);