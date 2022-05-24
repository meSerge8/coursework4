#include "circuit.h"

circuit::circuit() {}

circuit::~circuit()
{
    for (auto itr : gates)
        delete itr;
}
