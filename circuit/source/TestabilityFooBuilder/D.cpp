
#include "TestabilityFooBuilder.h"

dnf TestabilityFooBuilder::GetD1() {
    vertex
        *B = buildB(),
        *C1 = buildC1(),
        *C0 = this->manager->Negate(C1),
        *D1 = this->manager->AND_bin(B, C0);

    DnfExporterFromBDD exp(&this->b,this->inGates);
    return exp.ExportVertex(D1);
}

dnf TestabilityFooBuilder::GetD0() {
    vertex
        *B = buildB(),
        *C1 = buildC1(),
        *D0 = this->manager->AND_bin(B, C1);

    DnfExporterFromBDD exp(&this->b,this->inGates);
    return exp.ExportVertex(D0);
}
