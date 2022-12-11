#pragma once

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>

#include "variable.h"
#include "vertex.h"

using namespace std;

class bdd_manager {
    list<variable *> vars;
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

    vertex *AND(list<vertex *> vertexList);
    vertex *OR(list<vertex *> vertexList);
    vertex *NAND(list<vertex *> vertexList);
    vertex *NOR(list<vertex *> vertexList);
    vertex *XOR(list<vertex *> vertexList);
    vertex *NXOR(list<vertex *> vertexList);

    vertex *Negate(vertex *rootVertex);

    vertex *Reduce(vertex *rootVertex);

    list<variable *> GetVariables();
    vector<variable *> GetVariablesNonTerm();
    variable *GetOneVariable();
    variable *GetZeroVariable();

    void PrintVariables();

    void ExportPNG(list<string> *outputGatesNames,
                   list<vertex *> *vertexList,
                   string filename);

   private:
    // Create
    void UpdateTerminals();

    // Apply
    vertex *Apply_bin(vertex *one, vertex *two, bool (*func)(bool, bool));
    vertex *Apply_bin_core(vertex *one, vertex *two, bool (*func)(bool, bool));

    // Apply multiple times
    vertex *Apply(list<vertex *> vertexList, bool (*func)(bool, bool));

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
    string BindOuts(list<string> *outs, list<vertex *> *vs);
    void DrawVertexsRecursive(vertex *, ofstream *, bool m);
};

// Support
list<vertex *> BuildVertexList(vertex *);
void BuildVertexList_core(vertex *, list<vertex *> *, bool);