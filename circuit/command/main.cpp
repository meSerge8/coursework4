#include "circuit.h"
#include "dnf.h"
string benchPath = "../benchmarks/",
       filename = "S27.BEN";

int main()
{

    // circuit one;
    // one.ImportBenchmark(benchPath + filename);
    // auto b = one.ExportBDD();
    // b.ExportGV("test832");

    cout << "hello world" << endl;

    dnf d(3);
    conj c(3, 1);

    d.AddConjunction(c);
    
    cout << c << endl;
    cout << d << endl;
    // one.PrintGates();
    // one.ExportCircuit("S27_circuit.txt");
    // cout << endl
}
