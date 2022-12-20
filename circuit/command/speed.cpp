#include <filesystem>
#include <iostream>
#include <string>

#include "circuit.h"
#include "timer.h"

using namespace std;
namespace fs = filesystem;

string GetName(string);
bool Skip(string);
double Test_BDD(circuit *);
double Test_DNF_from_BDD(circuit *);
double Test_DNF(circuit *);

const string benchmarkPath = "../benchmarks/",
             dotDir = "dot/";

// S27     0.0005  done
// S820    0.0816  done
// S832    0.0880  done
// S510    0.0580  done
// S953    0.0891  done
// S298    0.0048  done
// S208X1  0.0057  done
// S344    0.0097  done
// S386    0.0108  done
// S526N   0.0133  done
// S526    0.0133  done
// S382    0.0103  done
const vector<string> avoid{"S820", "S832", "S510", "S953", "S344",  "S526N", "S526", "S382"};

int main() {
    cout << "name\tBDD\tDNF1\tDNF2" << endl;

    for (const auto &entry : fs::directory_iterator(benchmarkPath)) {
        string filePath = entry.path();
        if (Skip(filePath)) {
            cout << GetName(filePath) << "\t\t\t\tskip" << endl;
            continue;
        }

        circuit c;
        c.ImportBenchmark(filePath);

        cout << GetName(filePath) << "\t";
        cout << flush;

        printf("%.4f\t", Test_BDD(&c));
        cout << flush;

        printf("%.4f\t", Test_DNF_from_BDD(&c));
        cout << flush;

        // printf("%.4f\t", Test_DNF(&c));
        cout << flush;

        cout << endl;
    }
}

string GetName(string filePath) {
    auto pos = filePath.find(benchmarkPath) + benchmarkPath.size();
    auto name = filePath.substr(pos);
    name.resize(name.size() - 4);
    return name;
}

bool Skip(string filePath) {
    filePath = GetName(filePath);
    auto it = find(avoid.begin(), avoid.end(), filePath);
    return it != avoid.end();
}

double Test_BDD(circuit *c) {
    timer timer;
    timer.Start();
    c->GetBddExporter(FROM_INPUT)->Export();
    return timer.Finish();
}

double Test_DNF_from_BDD(circuit *c) {
    timer timer;
    timer.Start();
    c->GetDnfExporter(FROM_BDD)->Export();
    return timer.Finish();
}

double Test_DNF(circuit *c) {
    timer timer;
    timer.Start();
    c->GetDnfExporter(DNF_FROM_INPUT)->Export();
    return timer.Finish();
}
