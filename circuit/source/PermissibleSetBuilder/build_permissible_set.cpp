#include "PermissibleSetBuilder.h"

vector<string> PermissibleSetBuilder::buildPermissibleSet(dnf D1, dnf D0) {
    if (D1.IsConstant() or D0.IsConstant()) {
        return {};
    }
    auto m1 = getM(D1);
    auto m0 = getM(D0);

    buildTable(m1, m0);
    return zacrevskyMethod();
}

vector<vector<bool>> PermissibleSetBuilder::getM(dnf d) {
    vector<vector<bool>> res;
    for (conj& c : d.GetConjunctions()) {
        buildLines(c.vs.begin(), c.vs.end(), {}, &res);
    }
    return res;
}

void PermissibleSetBuilder::buildTable(vector<vector<bool>> m1, vector<vector<bool>> m0) {
    this->table.reserve(m1.size() * m0.size());
    for (auto m1_val : m1) {
        for (auto m0_val : m0) {
            int len = m1_val.size();
            vector<bool> line(len);

            for (size_t i = 0; i < len; i++) {
                line[i] = m1_val[i] xor m0_val[i];
            }

            if (not containsVec(&this->table, line)) {
                this->table.push_back(line);
            }
        }
    }
}

vector<string> PermissibleSetBuilder::zacrevskyMethod() {
    auto names = GetNames(this->inGates);
    vector<string> res;
    while (this->table.size()) {
        vector<bool> minLine = findMinLine();
        int maxColumn = findMaxColumn(minLine);
        res.push_back(names[maxColumn]);
        names.erase(names.begin() + maxColumn);
        removeCovered(maxColumn);
    }
    return res;
}

vector<bool> PermissibleSetBuilder::findMinLine() {
    vector<std::vector<bool>>::iterator minItr = this->table.begin();
    int minCount = 99999999;

    for (auto i = this->table.begin(); i != this->table.end(); i++) {
        int count = 0;

        for (bool x : *i) {
            if (x) {
                count++;
            }
        };

        if (count < minCount) {
            minItr = i;
            minCount = count;
        }
    }

    return *minItr;
}

int PermissibleSetBuilder::findMaxColumn(vector<bool> x) {
    vector<int> counter(x.size());

    for (auto i = this->table.begin(); i != this->table.end(); i++) {
        int idx = 0;
        for (auto j = i->begin(); j != i->end(); j++) {
            if (*j) {
                counter[idx]++;
            }
            idx++;
        }
    }

    int max_i = 0;
    int max_value = 0;
    for (size_t i = 0; i < counter.size(); i++) {
        if (counter[i] > max_value) {
            max_i = i;
            max_value = counter[i];
        }
    }

    return max_i;
}

void PermissibleSetBuilder::removeCovered(int maxColumn) {
    vector<vector<bool>> res;
    res.reserve(this->table.size());

    for (auto i = this->table.begin(); i < this->table.end(); i++) {
        if (!(*i)[maxColumn]) {
            i->erase(i->begin() + maxColumn);
            res.push_back(*i);
        }
    }
    this->table = res;
}

void PermissibleSetBuilder::buildLines(vector<var>::iterator i, vector<var>::iterator end, vector<bool> narost, vector<vector<bool>>* res) {
    while (true) {
        if (i == end) {
            if (not containsVec(res, narost)) {
                res->push_back(narost);
            }
            return;
        }

        if (*i == non) {
            break;
        }

        narost.push_back(bool(*i - 1));
        i++;
    }

    i++;
    vector<bool> negNarost = narost;
    vector<bool> posNarost = narost;
    negNarost.push_back(false);
    posNarost.push_back(true);

    buildLines(i, end, negNarost, res);
    buildLines(i, end, posNarost, res);
}