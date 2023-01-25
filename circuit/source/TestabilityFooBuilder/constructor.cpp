#include "TestabilityFooBuilder.h"

TestabilityFooBuilder::TestabilityFooBuilder(Gate *pole, Circuit *circuit) {
    auto gs = circuit->GetGates();
    if (not contains(&gs, pole)) {
        throw logic_error("pole not found in circuit gates");
    }

    this->pole = pole;
    this->c = circuit;

    isolateSv();
    this->manager = this->b.GetManager();
}

TestabilityFooBuilder::~TestabilityFooBuilder() {
    if (this->B != nullptr) {
        delete B;
    }
}