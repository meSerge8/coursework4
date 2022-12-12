#include "circuit.h"

IDnfExporter *circuit::GetDnfExporter(DnfExporterType type) {
    switch (type) {
        case FROM_BDD: {
            auto exporter = GetBddExporter(FROM_INPUT);
            return new DnfExporterFromBDD(exporter);
        }
        case DNF_FROM_INPUT: {
            vector<gate *> gs;
            for (auto g : this->gates) {
                gs.push_back(g);
            }
            return new DnfExporterFromUnput(gs);
        }
        default:
            throw logic_error("exporter not found");
    }
}