#include "bdd.h"

// list<dnf> bdd::ExportDNF()
// {
//     list<dnf> dnf_res;
//     for (auto root : roots)
//     {
//         auto d = BuildDNF(root);
//         dnf_res.push_back(d);
//     }

//     return dnf_res;
// }

// dnf bdd::BuildDNF(vertex *root)
// {
//     auto vars = bdd_mng.GetVariables();
//     int capacity = vars.size() - 2;

//     dnf dnf_res(capacity);
//     dnf_res.ImportNames(GetVarNames(vars));

//     conjunction cnj;
//     BuildDNF_Core(root, dnf_res, cnj);

//     return dnf_res;
// }

// void bdd::BuildDNF_Core(vertex *v, dnf &d, conjunction &cnj)
// {
//     u_int idx = v->GetVariable()->index;

//     while (cnj.size() < idx)
//         cnj.push_back(non);

//     if (v->IsTerminal())
//     {
//         string val = v->GetVariable()->value;
//         if (val == "1")
//         {
//             d.AddConjunction(cnj);
//         }
//     }
//     else
//     {
//         conjunction cnjLow(cnj), cnjHigh(cnj);
//         cnjLow.push_back(neg);
//         cnjHigh.push_back(pos);
//         BuildDNF_Core(v->GetLow(), d, cnjLow);
//         BuildDNF_Core(v->GetHigh(), d, cnjHigh);
//     }
// }

vector<string> bdd::GetVarNames(list<variable *> vs)
{
    vector<string> res;

    for (auto v : vs)
    {
        if (v->index == vs.size() - 2)
            break;
        res.push_back(v->value);
    }

    return res;
}
