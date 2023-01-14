#include "BddExporter.h"
#include "Circuit.h"
#include "DnfExporter.h"
#include "Importer.h"
#include "PermissibleSetBuilder.h"
#include "dnf.h"

string benchPath = "../benchmarks/",
       filename = "S27.BEN",
       poleName = "G9";

int main() {
    Importer imp;
    Circuit c = imp.Import(benchPath + filename);

    PermissibleSetBuilder psb(&c);

    auto ns = psb.DoMagic("G9");

    for (auto n : ns) {
        cout << n << endl;
    }

    // cout << c << endl;

    BddExporterFromInput expBdd;
    auto b = expBdd.Export(&c);
    b->ExportGV("S27");

    DnfExporterFromBDD expDnf(b);
    auto ds = expDnf.Export();
    cout << ds << endl;

    // DnfExporterFromInput exp(&c);
    // auto ds = exp.Export();
    // cout << ds << endl;
}
