#include "BddExporter.h"
#include "Circuit.h"
#include "DnfExporter.h"
#include "Importer.h"
#include "PermissibleSetBuilder.h"
#include "TestabilityFooBuilder.h"
#include "dnf.h"

string benchPath = "../benchmarks/",
       filename = "S27.BEN",
       poleName = "G70";

int main() {
    // Importer imp;
    // Circuit c = imp.Import(benchPath + filename);

    dnf D1(3,
           {
               {{pos, neg, non}, false},
               {{neg, pos, neg}, false},
           });

    dnf D0(3,
           {
               {{pos, pos, pos}, false},
           });

    dnf res = D1.XOR(D0);

    cout << res << endl;
}
