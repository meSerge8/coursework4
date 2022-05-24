#include "bdd_manager.h"

list<variable *> bdd_manager::GetVariables()
{
    list<variable *> res = vars;
    res.push_back(zeroVar);
    res.push_back(oneVar);
    return res;
}


list<vertex *> BuildVertexList(vertex *rootVert)
{
    list<vertex *> res;
    bool m = rootVert->GetMark();
    BuildVertexList_core(rootVert, &res, not m);
    return res;
}

void BuildVertexList_core(vertex *v, list<vertex *> *vl, bool m)
{
    bool vMark = v->GetMark();

    if (vMark == m)
        return;
    v->SetMark(m);

    vl->push_back(v);

    if (v->IsTerminal())
        return;

    BuildVertexList_core(v->GetLow(), vl, m);
    BuildVertexList_core(v->GetHigh(), vl, m);
}