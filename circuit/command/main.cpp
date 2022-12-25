#include "AcceptableFooBuilder.h"
#include "circuit.h"
#include "dnf.h"

string benchPath = "../benchmarks/",
       filename = "S27.BEN";

int main() {
    circuit one;
    one.ImportBenchmark(benchPath + filename);

    auto bddExp = one.GetBddExporter(FROM_INPUT);
    auto b = bddExp->Export();
    b->ExportGV(filename);

    auto dnfExp = one.GetDnfExporter(DNF_FROM_INPUT);
    auto ds = dnfExp->Export();

    for (dnf d : ds) {
        d.ShrinkVariables();
        cout << d << endl;

        AcceptableFooBuilder b(d);
        auto xs = b.BuildAcceptableFoo();

        cout << "BEFOR: ";
        for (auto n : d.GetNames()) {
            cout << n << "\t";
        }
        cout << endl;

        cout << "AFTER: ";
        for (auto x : xs) {
            cout << x << "\t";
        }
        cout << endl
             << "=========================" << endl;
    }
}
