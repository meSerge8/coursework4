#pragma once

#include <iostream>
#include <tuple>
#include <vector>

#include "Circuit.h"
#include "DnfExporter.h"
#include "Gate.h"
#include "bdd.h"

using namespace std;

class TestabilityFooBuilder {
   private:
    Circuit* c;
    Gate* pole;
    vector<Gate*>
        gates,
        inGates,
        outGates;

    bdd b;
    bdd_manager* manager;

    dnf* B = nullptr;

   public:
    TestabilityFooBuilder(Gate* pole, Circuit* circuit);
    ~TestabilityFooBuilder();

    dnf GetB();
    dnf GetD0();
    dnf GetD1();

    vector<Gate*> GetInputs();
    int CountInputs();

   private:
    // isolate
    void isolateSv();
    void isolateOutGates(Gate*, vector<Gate*>*);
    void isolateGates(Gate*);

    // build vertex
    vertex* buildVertex(Gate*, vector<vertex*>*);
    vector<vertex*> getSubvertices(Gate*, vector<vertex*>*);

    // build B
    vertex* buildB();

    // build C1
    vertex* buildC1();

    // build D0 D1
    void checkD_0_1();
    void buildD_0_1();
};
