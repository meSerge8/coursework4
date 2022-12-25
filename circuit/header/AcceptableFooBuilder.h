#pragma once

#include <algorithm>
#include <vector>

#include "dnf.h"

class AcceptableFooBuilder {
   private:
    dnf odnf;
    vector<vector<bool>> table;

   public:
    AcceptableFooBuilder(dnf odnf);
    vector<string> BuildAcceptableFoo();

   private:
    vector<vector<bool>> getM(dnf d);
    void buildTable(vector<vector<bool>> m1, vector<vector<bool>> m0);
    vector<string> zacrevskyMethod();
    vector<bool> findMinLine();
    int findMaxColumn(vector<bool> x);
    void removeCovered(int maxColumn);
    void buildLines(vector<var>::iterator i, vector<var>::iterator end, vector<bool> narost, vector<vector<bool>>* res);
};
