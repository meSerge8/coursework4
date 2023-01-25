#include "TestabilityFooBuilder.h"

dnf TestabilityFooBuilder::GetB() {
    auto b = buildB();
    DnfExporterFromBDD exp(&this->b, this->inGates);
    return exp.ExportVertex(b);
}

vertex *TestabilityFooBuilder::buildB() {
    vector<vertex *>
        phi_0,
        phi_1;

    for (Gate *g : this->gates) {
        vertex *v_0 = (g == this->pole) ? this->manager->CreateZero() : buildVertex(g, &phi_0),
               *v_1 = (g == this->pole) ? this->manager->CreateOne() : buildVertex(g, &phi_1);

        phi_0.push_back(v_0);
        phi_1.push_back(v_1);
    }

    vector<vertex *> bi;
    for (int i = 0; i < this->gates.size(); i++) {
        if (contains(&this->outGates, this->gates[i])) {
            bi.push_back(this->manager->XOR_bin(phi_0[i], phi_1[i]));
        }
    }

    auto B_bdd = this->manager->OR(bi);

    for (auto v : phi_0) {
        this->manager->Utilize(v);
    }

    for (auto v : phi_1) {
        this->manager->Utilize(v);
    }

    return B_bdd;
}
