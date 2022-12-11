#include "bdd_manager.h"

vertex *bdd_manager::Apply(list<vertex *> vs, bool (*oper)(bool, bool)) {
    if (vs.empty())
        throw logic_error("No gates for multi operation");

    if (vs.size() == 1)
        return vs.front();

    auto itr = vs.begin();

    vertex *one = *itr,
           *two = *(++itr),
           *res = Apply_bin(one, two, oper),
           *buf;

    for (itr++; itr != vs.end(); itr++) {
        buf = res;
        res = Apply_bin(res, *itr, oper);
        Utilize(buf);
    }

    return res;
}