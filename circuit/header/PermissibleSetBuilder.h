#pragma once

#include <algorithm>
#include <cmath>
#include <list>
#include <queue>
#include <tuple>
#include <vector>

#include "Circuit.h"
#include "DnfExporter.h"
#include "Gate.h"
#include "bdd.h"
#include "dnf.h"

using namespace std;

class PermissibleSetBuilder {
   private:
    vector<Gate *>
        inGates,
        essentialGates;

    vector<unsigned long>
        *M0, *M1,
        table;

    vector<vector<Gate *>> permissibleGates;

   public:
    ~PermissibleSetBuilder();
    void BuildSets(dnf M0, dnf M1, vector<Gate *> inGates);
    vector<vector<Gate *>> GetSets();
    vector<Gate *> GetMinSet();

   private:
    void buildTable();
    void buildPermissibleSets(vector<Gate *> inGates);
    bool checkMask(unsigned long mask);
    void addPermissibleSet(unsigned long, vector<unsigned long> *);
    void constructSets();

    // essentials
    bool doStuffEssentials();
    vector<unsigned long> findEssentials();
    bool checkEssentialSet(unsigned long);
    void reduceEssentials(vector<unsigned long>);
    vector<Gate *> getUnessentialGates();
};

vector<unsigned long> *GetM(dnf);
void buildLines(vector<var>::iterator i, vector<var> *, unsigned long narost, vector<unsigned long> *res);
inline void reduceEssential(vector<unsigned long>::iterator, unsigned long);
vector<Gate *> exportSet(unsigned long, vector<Gate *>);
int Weight64(unsigned long);
unsigned long combineMasks(vector<unsigned long>);

class Build_M_for_1_exception : public exception {
   public:
    virtual const char *what() const throw() {
        return "tried to build M for constanta 1";
    }
};