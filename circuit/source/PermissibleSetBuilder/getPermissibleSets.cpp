#include "PermissibleSetBuilder.h"

vector<vector<Gate *>> PermissibleSetBuilder::GetSets() {
    if (this->permissibleGates.size() == 0) {
        // throw logic_error("permissible sets are empty");
        return {};
    }
    return this->permissibleGates;
}

vector<Gate *> PermissibleSetBuilder::GetMinSet() {
    vector<std::vector<Gate *>>::iterator minI;
    int minCount = 99999999;

    if (this->permissibleGates.size() == 0) {
        return {};
    }

    for (auto i = this->permissibleGates.begin(); i != this->permissibleGates.end(); i++) {
        if (i->size() < minCount) {
            minCount = i->size();
            minI = i;
        }
    }

    return *minI;
}

vector<Gate *> exportSet(unsigned long set, vector<Gate *> gates) {
    vector<Gate *> res;
    for (int i = 0; i < gates.size(); i++) {
        unsigned long y = set & (1 << i);
        if (y != 0) {
            res.push_back(gates.at(i));
        }
    }
    return res;
}