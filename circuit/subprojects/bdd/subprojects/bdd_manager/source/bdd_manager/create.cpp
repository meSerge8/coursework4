#include "bdd_manager.h"

variable *bdd_manager::CreateVar(string name)
{
    for (variable *vrb : GetVariables())
        if (vrb->value == name)
            return vrb;

    u_int32_t idx = vars.size();
    auto newVariable = new variable{name, idx};
    vars.push_back(newVariable);
    UpdateTerminals();
    return newVariable;
}

vertex *bdd_manager::CreateVertex(string name)
{
    for (variable *vrb : GetVariables())
        if (vrb->value == name)
            return CreateVertex(vrb);
    return CreateVertex(CreateVar(name));
}

vertex *bdd_manager::CreateVertex(variable *vrb)
{
    return new non_term_vertex(vrb, CreateZero(), CreateOne());
}

vertex *bdd_manager::CreateZero() { return new term_vertex(zeroVar, 0); }
vertex *bdd_manager::CreateOne() { return new term_vertex(oneVar, 1); }

void bdd_manager::Utilize(vertex *vtx)
{
    auto utilize = [](vertex *x)
    { delete x; };
    Traverse(vtx, utilize);
}

void bdd_manager::UpdateTerminals()
{
    oneVar->index = zeroVar->index = vars.size();
}
