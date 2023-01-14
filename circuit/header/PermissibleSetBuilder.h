#pragma once

#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

#include "Circuit.h"
#include "Gate.h"
#include "dnf.h"

class PermissibleSetBuilder {
   private:
    Circuit *c;
    vector<Gate *>
        gates,
        inGates,
        outGates;
    Gate *pole;
    vector<vector<bool>> table;

   public:
    PermissibleSetBuilder(Circuit *);
    vector<string> DoMagic(string gateName);

   private:
    // main
    void findPole(string gateName);
    void isolateSv();
    void isolateGates(Gate *);
    void isolateOutGates(Gate *, vector<Gate *> *);

    // build_D1_D0
    tuple<dnf, dnf> build_D1_D0();
    void buildDNFs_0_and_1(vector<dnf> *dnfs_0, vector<dnf> *dnfs_1);
    dnf buildB(vector<dnf> *dnfs_0, vector<dnf> *dnfs_1);
    dnf buildDNF(Gate *, vector<dnf> *);
    dnf buildInputDNF(Gate *);
    vector<dnf> getPredecessorsDNF(Gate *, vector<dnf> *);
    dnf apply(dnf &, dnf &, GateType);
    dnf getGateDNF(Gate *, vector<dnf> *);

    // build_permissible_set
    vector<string> buildPermissibleSet(dnf D1, dnf D0);
    vector<vector<bool>> getM(dnf d);
    void buildTable(vector<vector<bool>> m1, vector<vector<bool>> m0);
    vector<string> zacrevskyMethod();
    vector<bool> findMinLine();
    int findMaxColumn(vector<bool> x);
    void removeCovered(int maxColumn);
    void buildLines(vector<var>::iterator i, vector<var>::iterator end, vector<bool> narost, vector<vector<bool>> *res);
};

bool containsVec(vector<vector<bool>> *, vector<bool>);