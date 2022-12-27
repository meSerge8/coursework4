#include <filesystem>
#include <iostream>
#include <string>

#include "AcceptableFooBuilder.h"
#include "circuit.h"
#include "timer.h"

using namespace std;
namespace fs = filesystem;

string GetName(string);
bool Skip(string);
double Test_BDD(circuit *);
double Test_DNF_from_BDD(circuit *);
double Test_DNF(circuit *);
double Test_Acceptable(circuit *);

const string benchmarkPath = "../benchmarks/",
             dotDir = "dot/";

const vector<string> avoid{};

int main() {
    cout << "name\tcount\tBDD\tDNF1\tDNF2" << endl;

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

        cout << c.CountGates() << "\t";
        cout << flush;

        printf("%.4f\t", Test_BDD(&c));
        cout << flush;

        printf("%.4f\t", Test_DNF_from_BDD(&c));
        cout << flush;

        printf("%.4f\t", Test_DNF(&c));
        cout << flush;

        printf("%.4f\t", Test_Acceptable(&c));
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

double Test_Acceptable(circuit *c) {
    timer timer;
    timer.Start();
    for (dnf d : c->GetDnfExporter(DNF_FROM_INPUT)->Export()) {
        d.ShrinkVariables();
        AcceptableFooBuilder b(d);
        b.BuildAcceptableFoo();
    }

    return timer.Finish();
}