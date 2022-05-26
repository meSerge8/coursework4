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

    dnf d1(3, true);
    dnf d2(3, false);

    cout << d1.GetConstant() << endl;
    cout << d2.GetConstant() << endl;

    // conj c1({pos, pos, neg});
    // conj c11(3, true);
    // conj c2({pos, non, neg});

    // d1.AddConjunction(c1);
    // d1.AddConjunction(c11);
    // d1.AddConjunction(c2);

    // cout << d1 << endl;
    // exit(0);

    // dnf d3 = d1.NEG();
    // cout << d1 << endl;
    // cout << d2 << endl;
    // cout << d3 << endl;
    // cout << d << endl;
    // one.PrintGates();
    // one.ExportCircuit("S27_circuit.txt");
    // cout << endl
}
