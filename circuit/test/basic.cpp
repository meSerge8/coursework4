#include "circuit.h"

string benchPath = "../benchmarks/";

int main(const int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    string filename(argv[1]);
    circuit c;

    c.ImportBenchmark(benchPath + filename);

    auto bddExp = c.GetBddExporter(FROM_INPUT);
    bdd *b = bddExp->Export();
    b->ExportGV("test_basic");

    auto d = c.ExportDNF();
    cout << d << endl;
}