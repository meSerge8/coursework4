#include "circuit.h"
#include "dnf.h"
string benchPath = "../benchmarks/",
       filename = "S27.BEN";

int main() {
    circuit one;
    one.ImportBenchmark(benchPath + filename);
    auto x = one.GetBddExporter(FROM_INPUT);
    bdd b = x->Export();
    b.ExportGV(filename);

    // list<dnf> ds = one.ExportDNF();
    // cout << "Convert to DNF" << endl
    //      << ds << endl;

    // bdd b = one.ExportBDD();
    // b.ExportGV(filename);

    // auto d = b.ExportDNF();
    // cout << d << endl;
}
