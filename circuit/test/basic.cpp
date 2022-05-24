#include "circuit.h"

string benchPath = "../benchmarks/",
       filename = "S27.BEN";

int main(const int argc, const char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    string filename(argv[1]);

    circuit c;
    c.ImportBenchmark(benchPath + filename);

    auto b = c.ExportBDD();
    b.ExportGV("test_basic");

    // auto d = b.ExportDNF();
    // cout << d << endl;

    c.ExportCircuit(filename + "circuit.txt");
}