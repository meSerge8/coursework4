#include "TestabilityFooBuilder.h"

vertex *TestabilityFooBuilder::buildC1() {
    vector<vertex *> phi;
    vertex *C1;

    for (Gate *g : this->gates) {
        vertex *v = buildVertex(g, &phi);
        if (g == this->pole) {
            C1 = v;
            break;
        }
        phi.push_back(v);
    }

    for (auto ph : phi) {
        this->manager->Utilize(ph);
    }

    return C1;
}
