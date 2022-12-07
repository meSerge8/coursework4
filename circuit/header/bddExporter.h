#pragma once
#include <algorithm>
#include <queue>
#include <vector>

#include "bdd.h"
#include "gate.h"

typedef int BddExporterType;
const BddExporterType FROM_OUTPUT = 0;
const BddExporterType FROM_INPUT = 1;

class IBddExporter {
   public:
    virtual bdd Export() = 0;
};

class BddExporterFromOutput : public IBddExporter {
   private:
    list<gate *> outGates;
    bdd_manager *manager;
    map<string, vertex *> *gateVertMap;

   public:
    BddExporterFromOutput(list<gate *> outGates);
    bdd Export();

   private:
    vertex *makeVertex(gate *);
    vertex *performOperation(gate *, list<vertex *>);
};

class BddExporterFromInput : public IBddExporter {
   private:
    vector<gate *> gates;
    bdd_manager *manager;
    vector<vertex *> vertices;

   public:
    BddExporterFromInput(list<gate *> gates);
    bdd Export();

    vector<gate *> sortTopological();
    vector<int> initInDegrees();
    queue<int> initQueue(vector<int>);
    list<vertex *> getSubvertices(gate *);
    vertex *buildVertex(gate *);
    vector<gate *> getAllSubgates();
};