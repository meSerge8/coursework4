#include "circuit.h"

IBddExporter *circuit::GetBddExporter(BddExporterType type) {
    switch (type) {
        case FROM_INPUT:
            return new BddExporterFromInput(this->gates);

        case FROM_OUTPUT:
            return new BddExporterFromOutput(this->outputs);

        default:
            throw logic_error("exporter not found");
    }
}