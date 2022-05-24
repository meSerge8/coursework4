#pragma once

#include <iostream>
#include "bdd_manager.h"
#include <vector>
// #include "dnf.h"

using namespace std;

class bdd
{
private:
    list<vertex *> roots;
    list<string> rootNames;
    bdd_manager bdd_mng;

public:
    // constructors
    bdd();
    bdd(list<vertex *> roots);
    bdd(list<vertex *> roots, list<string> rootNames);
    ~bdd();

    // print
    friend ostream &operator<<(ostream &, bdd &);

    // export dot
    void ExportGV(string filename);

    // export dnf
    // list<dnf> ExportDNF();

    // support
    bdd_manager *GetManager();
    bool AddRoot(vertex *root, string name);

private:
    // export png
    string BindOuts();
    void DrawVertexsRecursive(vertex *v, ofstream &dotGV, bool m);

    // export dnf
    // dnf BuildDNF(vertex *root);
    // void BuildDNF_Core(vertex *, dnf &, conjunction &);
    vector<string> GetVarNames(list<variable *>);
};

// support
void ClearMark(vertex *);
