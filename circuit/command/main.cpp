#include "circuit.h"
#include "dnf.h"
string benchPath = "../benchmarks/",
       filename = "S1488.BEN";

int main()
{

    circuit one;
    one.ImportBenchmark(benchPath + filename);

    auto ds = one.ExportDNF();

    cout << ds << endl;

    // auto b = one.ExportBDD();
    // b.ExportGV("test832");

    // one.PrintGates();
    // one.ExportCircuit("S27_circuit.txt");
    // cout << endl
}
