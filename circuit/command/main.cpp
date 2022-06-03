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
    b.ExportGV(filename);
}
