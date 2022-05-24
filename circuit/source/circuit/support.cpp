#include "circuit.h"

gate *circuit::Find(list<gate *> gs, string name)
{
    for (auto i : gs)
        if (i->name == name)
            return i;

    return nullptr;
}
