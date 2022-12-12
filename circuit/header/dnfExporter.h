#pragma once

#include <algorithm>
#include <queue>
#include <vector>

#include "bdd.h"
#include "bddExporter.h"
#include "dnf.h"
#include "gate.h"

typedef int DnfExporterType;
const DnfExporterType FROM_BDD = 0;
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
    DnfExporterFromBDD(IBddExporter *bddExporter);
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

class DnfExporterFromUnput : public IDnfExporter {
   private:
    vector<gate *> gates;
    vector<gate *> inputGates;
    vector<gate *> allSubgates;
    vector<dnf> dnfs;

   public:
    DnfExporterFromUnput(vector<gate *>);
    vector<dnf> Export();

   private:
    void sortTopological();
    vector<string> buildNames();
    dnf buildDNF(gate *);
    dnf buildInputDNF(gate *);
    list<dnf> getSubDnfs(gate *);
    dnf apply(dnf &, dnf &, gateType);
};
