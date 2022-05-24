#include "bdd_manager.h"

vertex *bdd_manager::Apply_bin(vertex *v1, vertex *v2, bool (*oper)(bool, bool))
{

    vertex *x = Apply_bin_core(v1, v2, oper),
           *y = Reduce(x);
    Utilize(x);
    return y;
}

vertex *bdd_manager::Apply_bin_core(vertex *v1, vertex *v2, bool (*oper)(bool, bool))
{
    if (v1->IsTerminal() and v2->IsTerminal())
    {
        bool vb1 = stoi(v1->GetVariable()->value);
        bool vb2 = stoi(v2->GetVariable()->value);
        return oper(vb1, vb2) == 1 ? CreateOne() : CreateZero();
    }

    variable *var1 = v1->GetVariable(),
             *var2 = v2->GetVariable(),
             *varNew = var1->index < var2->index ? var1 : var2;

    vertex *vlow1, *vhigh1, *vlow2, *vhigh2;

    if (var1 == varNew)
    {
        vlow1 = v1->GetLow();
        vhigh1 = v1->GetHigh();
    }
    else
    {
        vlow1 = v1;
        vhigh1 = v1;
    }

    if (var2 == varNew)
    {
        vlow2 = v2->GetLow();
        vhigh2 = v2->GetHigh();
    }
    else
    {
        vlow2 = v2;
        vhigh2 = v2;
    }

    auto lowNew = Apply_bin_core(vlow1, vlow2, oper);
    auto highNew = Apply_bin_core(vhigh1, vhigh2, oper);

    return new non_term_vertex(varNew, lowNew, highNew);
}