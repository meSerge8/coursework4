#include "circuit.h"
#include "dnf.h"
string benchPath = "../benchmarks/",
       filename = "S27.BEN";

int main()
{
    circuit one;
    one.ImportBenchmark(benchPath + filename);

    list<dnf> ds = one.ExportDNF();
    cout << "Convert to DNF" << endl
         << ds << endl;

    bdd b = one.ExportBDD();
    auto d = b.ExportDNF();
    cout << d << endl;
    b.ExportGV(filename);
}
