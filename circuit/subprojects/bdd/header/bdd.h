#pragma once

#include <iostream>
#include "bdd_manager.h"
#include <vector>
// #include "dnf.h"

using namespace std;

class bdd
{
    list<vertex *> roots;
    list<string> rootNames;
    bdd_manager bdd_mng;

public:
    bdd();
    bdd(list<vertex *> roots);
    bdd(list<vertex *> roots, list<string> rootNames);
    ~bdd();

    friend ostream &operator<<(ostream &, bdd &);

    void ExportGV(string filename);

    bdd_manager *GetManager();
    bool AddRoot(vertex *root, string name);

private:
    string BindOuts();
    void DrawVertexsRecursive(vertex *v, ofstream &dotGV, bool m);
};

// support
void ClearMark(vertex *);
