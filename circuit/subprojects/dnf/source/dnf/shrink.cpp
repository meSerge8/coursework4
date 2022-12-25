#include "dnf.h"

void dnf::ShrinkVariables() {
    if (this->names.empty()) {
        throw logic_error("names expected");
    }
    vector<bool> exist(this->names.size(), false);
    for (conj c : this->cs) {
        int i = 0;
        for (var v : c.vs) {
            if (v != non) {
                exist[i] = true;
            }
            i++;
        }
    }

    vector<string> shrinkedNames;
    for (size_t i = 0; i < exist.size(); i++) {
        if (exist[i]) {
            shrinkedNames.push_back(this->names[i]);
        }
    }
    this->names = shrinkedNames;

    for (auto itrCS = this->cs.begin(); itrCS != this->cs.end(); itrCS++) {
        int i = 0;
        vector<var> newVs;
        for (auto jtr = itrCS->vs.begin(); jtr < itrCS->vs.end(); jtr++) {
            if (exist[i]) {
                newVs.push_back(*jtr);
            }
            i++;
        }
        itrCS->vs = newVs;
    }

    varNum = this->names.size();
}
