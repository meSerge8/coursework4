#include "dnf_from_bdd.h"

void dnf_from_bdd::AddConjunction(conjunction c) {
    if (c.size() != variableNumber)
        throw logic_error("Wrong number of variables");

    conjuctions.push_back(c);
}
