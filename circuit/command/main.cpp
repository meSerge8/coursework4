#include "circuit.h"
#include "dnf.h"
string benchPath = "../benchmarks/",
       filename = "S298.BEN";

int main() {
    circuit one;
    one.ImportBenchmark(benchPath + filename);

    auto bddExp = one.GetBddExporter(FROM_INPUT);
    auto b = bddExp->Export();

    b->ExportGV(filename);

    auto dnfExp = one.GetDnfExporter(DNF_FROM_INPUT);
    auto ds = dnfExp->Export();
    for (auto d : ds) {
        cout << d << endl;
    }
}
