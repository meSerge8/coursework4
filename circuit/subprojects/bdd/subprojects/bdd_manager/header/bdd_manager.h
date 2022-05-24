#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

#include "vertex.h"
#include "variable.h"

using namespace std;

class bdd_manager
{
private:
    list<variable *> vars; // add deleter to destructor (done)
    variable *zeroVar, *oneVar;

public:
    // Constructors
    bdd_manager();
    ~bdd_manager();

    // Create
    variable *CreateVar(string variableName);
    vertex *CreateVertex(string vertexName);
    vertex *CreateVertex(variable *variableReference);
    vertex *CreateZero();
    vertex *CreateOne();
    void Utilize(vertex *delme);

    // Operators
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

    // Negate
    vertex *Negate(vertex *rootVertex);

    // Reduce
    vertex *Reduce(vertex *rootVertex); // hide

    // Support
    list<variable *> GetVariables();

    void PrintVariables();

    // Export as PNG via graphviz   // need to be moved to bdd class!
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