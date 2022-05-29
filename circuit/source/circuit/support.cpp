#include "circuit.h"

gate *circuit::Find(list<gate *> gs, string name)
{
    for (auto i : gs)
        if (i->name == name)
            return i;

    return nullptr;
}

void circuit::buildInputGates()
{
    for (auto gate : gates)
        if (gate->type == INPUT)
            inputs.push_back(gate);
}