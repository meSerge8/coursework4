#include "Circuit.h"

// IDnfExporter *Circuit::GetDnfExporter(DnfExporterType type) {
//     switch (type) {
//         case DNF_FROM_BDD: {
//             auto exporter = GetBddExporter(FROM_INPUT);
//             return new DnfExporterFromBDD(exporter);
//         }
//         case DNF_FROM_INPUT: {
//             return new DnfExporterFromUnput(GetGates());
//         }
//         default:
//             throw logic_error("exporter not found");
//     }
// }