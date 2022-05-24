#include "circuit.h"
#include "dnf.h"
string benchPath = "../benchmarks/",
       filename = "S27.BEN";

int main()
{

    circuit one;
    one.ImportBenchmark(benchPath + filename);
    auto b = one.ExportBDD();
    b.ExportGV("test832");

    dnf *d;
    // auto d = b.ExportDNF();

    // cout << d << endl;

    // one.PrintGates();
    // one.ExportCircuit("S27_circuit.txt");
    // cout << endl
}
