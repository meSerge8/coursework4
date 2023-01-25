#include "PermissibleSetBuilder.h"

void PermissibleSetBuilder::BuildSets(dnf D0, dnf D1, vector<Gate*> inGates) {
    this->inGates = inGates;
    this->M0 = GetM(D0);
    this->M1 = GetM(D1);

    bool areEssentialsPermissible = doStuffEssentials();
    if (areEssentialsPermissible) {
        this->permissibleGates.push_back(this->essentialGates);
        return;
    }

    buildTable();
    if (this->table.size() == 0) {
        throw logic_error("empty table. Please check essential vars");
    }
    constructSets();
}

void PermissibleSetBuilder::buildTable() {
    this->table = {};

    if (M0->size() == 0) {
        this->table = *M1;
        return;
    }

    if (M1->size() == 0) {
        this->table = *M0;
        return;
    }

    for (auto i0 = M0->begin(); i0 != M0->end(); i0++) {
        for (auto i1 = M1->begin(); i1 != M1->end(); i1++) {
            unsigned long line = *i0 ^ *i1;
            if (line == 0) {
                continue;
            }
            auto beg = this->table.cbegin();
            auto end = this->table.cend();
            if (find(beg, end, line) == end) {
                this->table.push_back(line);
            }
        }
    }
}

void PermissibleSetBuilder::constructSets() {
    auto unessentials = getUnessentialGates();
    vector<unsigned long> sets;
    unsigned long setNumMax = pow(2, unessentials.size());

    for (int mask = 0; mask < setNumMax; mask++) {
        if (checkMask(mask)) {
            addPermissibleSet(mask, &sets);
        }
    }

    for (unsigned long set : sets) {
        auto permissibleGates = exportSet(set, unessentials);
        for (auto eg : this->essentialGates) {
            permissibleGates.push_back(eg);
        }
        this->permissibleGates.push_back(permissibleGates);
    }
}

bool PermissibleSetBuilder::checkMask(unsigned long mask) {
    for (unsigned long line : this->table) {
        if ((line & mask) == 0) {
            return false;
        }
    }
    return true;
}

void PermissibleSetBuilder::addPermissibleSet(unsigned long set, vector<unsigned long>* sets) {
    auto i = sets->begin();
    while (i != sets->end()) {
        auto x = *i & set;
        if (x == *i) {
            return;
        } else if (x == set) {
            i = sets->erase(i);
        } else {
            i++;
        }
    }
    sets->push_back(set);
}