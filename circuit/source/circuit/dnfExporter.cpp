#include "circuit.h"

IDnfExporter *circuit::GetDnfExporter(DnfExporterType type) {
    switch (type) {
        case FROM_BDD: {
            auto exporter = GetBddExporter(FROM_INPUT);
            return new DnfExporterFromBDD(exporter);
        }

        default:
            throw logic_error("exporter not found");
    }
}