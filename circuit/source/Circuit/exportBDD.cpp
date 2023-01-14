#include "Circuit.h"

// IBddExporter *Circuit::GetBddExporter(BddExporterType type) {
//     switch (type) {
//         case FROM_INPUT:
//             return new BddExporterFromInput(GetGates());

//         case FROM_OUTPUT:
//             return new BddExporterFromOutput(this->outGates);

//         default:
//             throw logic_error("exporter not found");
//     }
// }