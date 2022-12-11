#include "bdd_manager.h"

u_int32_t uniqId;
u_int32_t GetUniqId() { return uniqId++; }

vertex *bdd_manager::Negate(vertex *rootVtx) {
    map<u_int32_t, vertex *> vtxMap;
    auto foo = [](vertex *x) -> void { x->SetId(0); };
    Traverse(rootVtx, foo);

    uniqId = 0;
    bool m = rootVtx->GetMark();
    return Negate_core(rootVtx, vtxMap, not m);
}

vertex *bdd_manager::Negate_core(vertex *v, map<u_int32_t, vertex *> &mv, bool m) {
    bool vMark = v->GetMark();
    if (vMark == m)

        return mv.at(v->GetId());

    v->SetMark(m);

    auto myId = GetUniqId();
    v->SetId(myId);

    vertex *cv;

    if (v->IsTerminal()) {
        auto newVar = v->GetVariable() == zeroVar ? oneVar : zeroVar;
        cv = new term_vertex(newVar);
    } else {
        vertex *low = Negate_core(v->GetLow(), mv, m);
        vertex *high = Negate_core(v->GetHigh(), mv, m);
        cv = new non_term_vertex(v->GetVariable(), low, high);
    }
    mv.emplace(myId, cv);
    return cv;
}
