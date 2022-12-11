#pragma once

#include "bdd.h"
#include "bddExporter.h"
#include "dnf.h"
#include "gate.h"

typedef int DnfExporterType;
const DnfExporterType FROM_BDD = 0;

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