#include "PermissibleSetBuilder.h"

bool PermissibleSetBuilder::doStuffEssentials() {

    auto essentialMasks = findEssentials();
    if (essentialMasks.size() == 0) {
        return false;
    }

    unsigned long combinedMask = combineMasks(essentialMasks);
    this->essentialGates = exportSet(combinedMask, this->inGates);


    if (checkEssentialSet(combinedMask)) {
        return true;
    }

    reduceEssentials(essentialMasks);
    return false;
}

vector<unsigned long> PermissibleSetBuilder::findEssentials() {
    vector<unsigned long> masks;

    for (auto i0 = this->M0->begin(); i0 != this->M0->end(); i0++) {
        for (auto i1 = this->M1->begin(); i1 != this->M1->end(); i1++) {
            unsigned long line = *i0 ^ *i1;
            if (Weight64(line) != 1) {
                continue;
            }
            
            auto f = find(masks.begin(), masks.end(), line);
            if (f == masks.end()) {
                masks.push_back(line);
            }
        }
    }

    return masks;
}

bool PermissibleSetBuilder::checkEssentialSet(unsigned long combinedMask) {
    for (auto i0 = this->M0->begin(); i0 != this->M0->end(); i0++) {
        for (auto i1 = this->M1->begin(); i1 != this->M1->end(); i1++) {
            unsigned long line = *i0 ^ *i1;
            if ((line & combinedMask) == 0) {
                return false;
            }
        }
    }
    return true;
}

void PermissibleSetBuilder::reduceEssentials(vector<unsigned long> essentialMasks) {
    for (auto mask : essentialMasks) {
        for (auto& m : essentialMasks) {
            if (m > mask) {
                m >>= 1;
            }
        }

        for (auto i = this->M0->begin(); i != this->M0->end(); i++) {
            reduceEssential(i, mask);
        }

        for (auto i = this->M1->begin(); i != this->M1->end(); i++) {
            reduceEssential(i, mask);
        }
    }
}

vector<Gate*> PermissibleSetBuilder::getUnessentialGates() {
    vector<Gate*> unessentials;
    for (Gate* g : this->inGates) {
        auto f = find(this->essentialGates.begin(), this->essentialGates.end(), g);
        if (f == this->essentialGates.end()) {
            unessentials.push_back(g);
        }
    }
    return unessentials;
}

inline void reduceEssential(vector<unsigned long>::iterator i, unsigned long mask) {
    unsigned long
        element = *i,
        mask1 = mask - 1,
        buffer = element & mask1;

    element >>= 1;
    element &= ~mask1;
    element |= buffer;
    *i = element;
}

unsigned long combineMasks(vector<unsigned long> essentialMasks) {
    unsigned long combinedMask = 0;
    for (auto m : essentialMasks) {
        combinedMask |= m;
    }
    return combinedMask;
}

int Weight64(unsigned long x) {
    int weight;
    for (weight = 0; x != 0; weight++) {
        x &= x - 1;
    }
    return weight;
}
