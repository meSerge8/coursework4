#include "conjunction.h"

conjunction::conjunction(int size) : varVect(size)
{
    for (var &v : varVect)
        v = non;
}

conjunction::conjunction(int size, bool constanta) : conjunction(size)
{
    this->constanta = new bool(constanta);
}

conjunction::conjunction(initializer_list<var> l) : varVect(l){};

conjunction::conjunction(const conjunction &copy) : varVect(copy.varVect)
{
    constanta = (copy.constanta == nullptr) ? nullptr : new bool(*copy.constanta);
}

conjunction::~conjunction()
{
    if (constanta != nullptr)
        delete constanta;
}
