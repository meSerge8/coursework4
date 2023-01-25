#include <filesystem>
#include <iostream>
#include <string>

#include "BddExporter.h"
#include "Circuit.h"
#include "DnfExporter.h"
#include "Importer.h"
#include "PermissibleSetBuilder.h"
#include "Timer.h"

using namespace std;
namespace fs = filesystem;

string GetName(string);
bool Skip(string);
double Test_BDD(Circuit *, string);
double Test_DNF_from_BDD(Circuit *);
double Test_DNF(Circuit *);
double Test_Acceptable(Circuit *);

const string benchmarkPath = "../benchmarks/",
             dotDir = "dot/";

const vector<string> avoid{};

int main() {
    cout << "name\tcount\tinputs\toutputs\tBDD\tDNF1\tDNF2" << endl;

    for (const auto &entry : fs::directory_iterator(benchmarkPath)) {
        string filePath = entry.path();
        if (Skip(filePath)) {
            cout << GetName(filePath) << "\t\t\t\tskip" << endl;
            continue;
        }

        cout << GetName(filePath) << "\t";
        cout << flush;

        Importer imp;
        Circuit c = imp.Import(filePath);

        cout << c.CountGates() << "\t";
        cout << flush;

        cout << c.CountInputs() << "\t";
        cout << flush;

        cout << c.CountOutputs() << "\t";
        cout << flush;

        printf("%.4f\t", Test_BDD(&c, GetName(filePath)));
        cout << flush;

        printf("%.4f\t", Test_DNF_from_BDD(&c));
        cout << flush;

        printf("%.4f\t", Test_DNF(&c));
        cout << flush;

        // printf("%.4f\t", Test_Acceptable(&c));
        // cout << flush;

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
    return find(avoid.begin(), avoid.end(), filePath) != avoid.end();
}

double Test_BDD(Circuit *c, string name) {
    BddExporterFromInput bddExporter;
    Timer Timer;
    Timer.Start();
    bdd *b = bddExporter.Export(c);
    auto finish = Timer.Finish();

    b->ExportGV(name);
    return finish;
}

double Test_DNF_from_BDD(Circuit *c) {
    BddExporterFromInput bddExporter;
    bdd *b = bddExporter.Export(c);
    DnfExporterFromBDD dnfExporter(b, c->GetInputs());
    Timer Timer;
    Timer.Start();
    dnfExporter.Export();
    return Timer.Finish();
}

double Test_DNF(Circuit *c) {
    DnfExporterFromInput dnfExporter(c);
    Timer Timer;
    Timer.Start();
    dnfExporter.Export();
    return Timer.Finish();
}

double Test_Acceptable(Circuit *c) {
    DnfExporterFromInput dnfExporter(c);
    vector<dnf> dnfs = dnfExporter.Export();
    Timer Timer;
    Timer.Start();
    for (dnf d : dnfs) {
        // d.ShrinkVariables();
        // AcceptableFooBuilder b(d);
        // b.BuildAcceptableFoo();
    }
    return Timer.Finish();
}