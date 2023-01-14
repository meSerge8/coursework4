#pragma once

#include <algorithm>
#include <queue>
#include <vector>

#include "Circuit.h"
#include "Gate.h"
#include "bdd.h"
#include "dnf.h"

typedef int DnfExporterType;
const DnfExporterType DNF_FROM_BDD = 0;
const DnfExporterType DNF_FROM_INPUT = 1;

class IDnfExporter {
   public:
    virtual vector<dnf> Export() = 0;
};

class DnfExporterFromBDD : public IDnfExporter {
   private:
    bdd *b;
    vector<variable *> variables;
    int varNum;
    vector<string> names;

    vector<vertex *> vertices;
    vector<int> inDegrees;
    queue<vertex *> q;
    vector<dnf> dnfs;

   public:
    DnfExporterFromBDD(bdd *);
    ~DnfExporterFromBDD();
    vector<dnf> Export();

   private:
    dnf buildRootDNF(vertex *);
    void addVertexRecursive(vertex *);
    void sortTopological();
    dnf buildTerminal(vertex *);
    dnf buildNonTerminal(vertex *);
    dnf findDnfByVertex(vertex *);
};

class DnfExporterFromInput : public IDnfExporter {
   private:
    Circuit *c;
    vector<Gate *> allSubgates;
    vector<dnf> dnfs;

   public:
    DnfExporterFromInput(Circuit *);
    vector<dnf> Export();

   private:
    vector<string> buildNames();
    dnf buildDNF(Gate *);
    dnf buildInputDNF(Gate *);
    vector<dnf> getSubDnfs(Gate *);
    dnf apply(dnf &, dnf &, GateType);
};

bool containsVertex(vector<vertex *> *, vertex *);