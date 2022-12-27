#pragma once

#include <iostream>
#include <vector>

#include "bdd_manager.h"
#include "dnf_from_bdd.h"

using namespace std;

class bdd {
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

    list<dnf_from_bdd> ExportDNF();

    bdd_manager *GetManager();
    bool AddRoot(vertex *root, string name);
    vector<vertex *> GetRoots();

   private:
    string BindOuts();
    void DrawVertexsRecursive(vertex *v, ofstream &dotGV, bool m);

    dnf_from_bdd BuildDNF(vertex *root);
    void BuildDNF_Core(vertex *, dnf_from_bdd &, conjunction &);
    vector<string> GetVarNames(list<variable *>);
};

void ClearMark(vertex *);
