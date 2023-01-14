#pragma once
#include <algorithm>
#include <queue>
#include <vector>

#include "Circuit.h"

#include "Gate.h"
#include "bdd.h"

typedef int BddExporterType;
const BddExporterType FROM_OUTPUT = 0;
const BddExporterType FROM_INPUT = 1;

class IBddExporter {
   public:
    virtual bdd *Export(Circuit *) = 0;
};

class BddExporterFromOutput : public IBddExporter {
   private:
    bdd_manager *manager;
    map<string, vertex *> *gateVertMap;

   public:
    bdd *Export(Circuit *);

   private:
    vertex *makeVertex(Gate *);
    vertex *performOperation(Gate *, vector<vertex *>);
};

class BddExporterFromInput : public IBddExporter {
   private:
    Circuit *c;
    bdd_manager *manager;
    vector<vertex *> vertices;

   public:
    bdd *Export(Circuit *);

   private:
    vector<int> initInDegrees();
    queue<int> initQueue(vector<int>);
    vector<vertex *> getSubvertices(Gate *);
    vertex *buildVertex(Gate *);
};