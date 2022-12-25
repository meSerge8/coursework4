#include "AcceptableFooBuilder.h"

// for (auto n : this->odnf.GetNames()) {
//     cout << n << "\t";
// }
// cout << endl;

// for (auto x : res) {
//     for (var v : x) {
//         cout << v - 1 << "\t";
//     }
//     cout << endl;
// }

AcceptableFooBuilder::AcceptableFooBuilder(dnf odnf) : odnf(odnf) {
}

vector<string> AcceptableFooBuilder::BuildAcceptableFoo() {
    if (this->odnf.IsConstant()) {
        return {};
    }
    // cout << "getM1" << endl;
    auto m1 = getM(this->odnf);

    // cout << "negODNF" << endl;
    auto negODNF = this->odnf.NEG();

    // cout << "getM0" << endl;
    auto m0 = getM(negODNF);

    // cout << "buildTable"
    //  << " " << m1.size()
    //  << " " << m0.size() << endl;
    buildTable(m1, m0);

    // cout << "zacrevskyMethod"
    //  << " " << this->table.size() << endl;
    return zacrevskyMethod();
}

vector<vector<bool>> AcceptableFooBuilder::getM(dnf d) {
    vector<vector<bool>> res;
    for (conj& c : d.GetConjunctions()) {
        buildLines(c.vs.begin(), c.vs.end(), {}, &res);
    }
    return res;
}

void AcceptableFooBuilder::buildTable(vector<vector<bool>> m1, vector<vector<bool>> m0) {
    this->table.reserve(m1.size() * m0.size());
    for (auto m1_val : m1) {
        for (auto m0_val : m0) {
            int len = m1_val.size();
            vector<bool> line(len);

            for (size_t i = 0; i < len; i++) {
                line[i] = m1_val[i] xor m0_val[i];
            }

            auto it = find(this->table.begin(), this->table.end(), line);
            if (it == this->table.end()) {
                this->table.push_back(line);
            }
        }
    }
}

vector<string> AcceptableFooBuilder::zacrevskyMethod() {
    auto names = this->odnf.GetNames();
    vector<string> res;
    while (this->table.size()) {
        // cout << "findMinLine" << endl;
        vector<bool> minLine = findMinLine();

        // cout << "findMaxColumn" << endl;
        int maxColumn = findMaxColumn(minLine);

        res.push_back(names[maxColumn]);
        names.erase(names.begin() + maxColumn);

        // cout << "removeCovered" << endl;
        removeCovered(maxColumn);
    }
    return res;
}

vector<bool> AcceptableFooBuilder::findMinLine() {
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

int AcceptableFooBuilder::findMaxColumn(vector<bool> x) {
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

// void AcceptableFooBuilder::removeCovered(int maxColumn) {
//     for (auto i = this->table.begin(); i < this->table.end();) {
//         cout << i - this->table.begin() << endl;

//         if ((*i)[maxColumn]) {
//             i = this->table.erase(i);
//         } else {
//             i->erase(i->begin() + maxColumn);
//             i++;
//         }
//     }
// }

void AcceptableFooBuilder::removeCovered(int maxColumn) {
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

void AcceptableFooBuilder::buildLines(vector<var>::iterator i, vector<var>::iterator end, vector<bool> narost, vector<vector<bool>>* res) {
    while (true) {
        if (i == end) {
            auto it = find(res->begin(), res->end(), narost);
            if (it == res->end()) {
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