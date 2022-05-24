#include "bdd_manager.h"

void bdd_manager::TraverseSample(vertex *v, bool m)
{
    bool vMark = v->GetMark();

    if (vMark == m)
        return;

    v->SetMark(m);

    if (v->IsTerminal())
        return;

    TraverseSample(v->GetLow(), m);
    TraverseSample(v->GetHigh(), m);

    //action
}

void bdd_manager::Traverse(vertex *v, void (*foo)(vertex *))
{
    Traverse_core(v, foo, 1);
}

void bdd_manager::Traverse_core(vertex *v, void (*foo)(vertex *), bool m)
{
    bool vMark = v->GetMark();

    if (vMark == m)
        return;

    v->SetMark(m);

    if (v->IsTerminal())
        return;

    Traverse_core(v->GetLow(), foo, m);
    Traverse_core(v->GetHigh(), foo, m);
    foo(v);
}

void bdd_manager::ClearMark(vertex *v)
{
    if (v->GetMark() == 0)
        return;

    v->SwitchMark();
    if (v->IsTerminal())
        return;

    ClearMark(v->GetLow());
    ClearMark(v->GetHigh());
}